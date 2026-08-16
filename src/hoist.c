#include "hoist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// TODO : command argument ayrımını iyi yap
// program adını çağırıldığı binary adından çıkarabilirsin (consider this)
// program arguman'ı variable'a atayamıyor.
// memory leak'i önlemek için pointer olan argümanları kullanmadan önce delete edebilirsin 

static Option** args;
static int arg_count;
static int arg_capacity;

static const char *programName;
static const char *description;

bool needHelp;

// debug:
void paramCount(){
      printf("argument count: %d\n",arg_count);
      printf("argument capacity: %d\n",arg_capacity);
}

static void print_help(){
      printf("usage: %s", programName);
      // if there are other flags different than help
      if (arg_count > 1) printf(" [OPTIONS]");
      printf("\n");
      printf("%s\n", description);

      if (arg_count > 0) printf("\noptions:\n");
      for (int i = 0; i < arg_count; i++){
            Option *curr = args[i];
            if (curr->opt && curr->shortOpt)
                  printf("  %s, %s %s\t%s\n", curr->shortOpt, curr->opt, curr->paramName ? curr->paramName : "", curr->description);
            else // one or less option str exists
                  printf("  %s %s\t%s\n", curr->shortOpt ? curr->shortOpt : (curr->opt ? curr->opt : ""), curr->paramName ? curr->paramName : "", curr->description);
      }
}

void hoist(const char *_programName, const char *_description){
      // initalize library
      arg_count = 0;
      arg_capacity = 0;

      programName = _programName;
      description = _description;

      // include help flag
      needHelp = false;
      new_opt("-h", "--help", "prints this help message", &needHelp);
}

void init_opt(Option *fptr, const char *_shortArg, const char *_arg, const char *_description, void *_ptr, const char *_par_name){
      if (!fptr) return;

      fptr->shortOpt = _shortArg;
      fptr->opt = _arg;
      fptr->description = _description;
      fptr->paramPtr = _ptr;
      fptr->paramName = _par_name;
}

void new_opt(const char *shortFlag, const char *flag, const char *description, bool *ptr){
      // allocate memory
      if (arg_count == arg_capacity){
            if (arg_count == 0){
                  args = (Option**)malloc(sizeof(Option*)); // room for one
                  arg_capacity = 1;
            }else {
                  args = (Option**)realloc(args, (arg_capacity * 2) * sizeof(Option*));
                  arg_capacity *= 2;
            }

            if (!args){
                  printf("Allocation failed.\n");
                  exit(1);
            }
      }
      
      // create & add new flag
      Option *f = (Option*)malloc(sizeof(Option));
      init_opt(f, shortFlag, flag, description, ptr, NULL);
      args[arg_count++] = f;
}

void new_opt_arged(const char *shortFlag, const char *flag, const char *description, char *paramPtr, const char* par_name){
      // allocate memory
      if (arg_count == arg_capacity){
            if (arg_count == 0){
                  args = (Option**)malloc(sizeof(Option*)); // room for one
                  arg_capacity = 1;
            }else {
                  args = (Option**)realloc(args, (arg_capacity * 2) * sizeof(Option*));
                  arg_capacity *= 2;
            }

            if (!args){
                  printf("Allocation failed.\n");
                  exit(1);
            }
      }
      
      // create & add new flag
      Option *f = (Option*)malloc(sizeof(Option));
      init_opt(f, shortFlag, flag, description, (void*)paramPtr, par_name);
      args[arg_count++] = f;

}

void parse_args(int argc, char **argv){
      for (int i = 1; i < argc; i++){ // first argument is program name
            bool hasMatch = false;
            char *curr_arg = argv[i];

            // first try flags
            for (int j = 0; j < arg_count; j++){
                  Option* curr_opt_ptr = args[j];
                  // check match
                  if (strcmp(curr_arg, curr_opt_ptr->shortOpt ? curr_opt_ptr->shortOpt : "") == 0 ||
                              strcmp(curr_arg, curr_opt_ptr->opt ? curr_opt_ptr->opt : "") == 0) {
                        // has argument?
                        if (curr_opt_ptr->paramPtr){
                              if (curr_opt_ptr->paramName){ // if paramname given result is hold by char*
                                    // DIKKAT : bu büyük ihtimalle işe yaramayacak!!
                                    printf("paramname exists: %s\n",curr_opt_ptr->paramName);
                                    if (argc > (i + 1)){
                                          curr_opt_ptr->paramPtr = argv[i+1];
                                          i++; // skip argument in next iteration
                                    }else{ // missing argument
                                          printf("%s: '%s' missing argument\n", programName, argv[i]);
                                    }
                              }else{ // if paramname not given existance of flag is hold by bool*
                                    *(bool*)(curr_opt_ptr->paramPtr) = true;
                              }
                        }
                        hasMatch = true;
                        break;
                  }
            }
            if (hasMatch) break;

            // print error if no matching flag/command
            printf("%s: invalid option -- '%s'\n", programName, curr_arg);
            printf("Try '%s --help' for more information.\n", programName);
            exit(1);
      }

      // run built-in functions
      if (needHelp) print_help();

      // free all
      for (int i = 0; i < arg_count; i++){
            free(args[i]);
      }
      free(args);
}
