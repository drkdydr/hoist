#include "hoist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// TODO : command argument ayrımını iyi yap
// program adını çağırıldığı binary adından çıkarabilirsin (consider this)
// memory leak'i önlemek için pointer olan argümanları kullanmadan önce delete edebilirsin 
// help fonksiyonunda tab'ları düzelt
// add aphabetic sort for options

static Option** options;
static int opt_count;
static int opt_capacity;

static const char *programName;
static const char *program_description;

void print_help(){
      printf("usage: %s", programName);
      // if there are other flags different than help
      if (opt_count > 0) printf(" [OPTIONS]");
      printf("\n");
      printf("%s\n", program_description);

      if (opt_count > 0) printf("\noptions:\n");
      for (int i = 0; i < opt_count; i++){
            Option *curr = options[i];
            if (curr->opt && curr->shortOpt)
                  printf("  %s, %s %s\t%s\n", curr->shortOpt, curr->opt, curr->paramName ? curr->paramName : "", curr->description);
            else // one or less option str exists
                  printf("  %s %s\t%s\n", curr->shortOpt ? curr->shortOpt : (curr->opt ? curr->opt : ""), curr->paramName ? curr->paramName : "", curr->description);
      }
}

void hoist(const char *_programName, const char *_description){
      // initalize library
      opt_count = 0;
      opt_capacity = 0;

      programName = _programName;
      program_description = _description;

      // help flag is not built-in anymore
}

void init_opt(Option *fptr, const char *_shortArg, const char *_arg, const char *_description, void *_ptr, const char *_par_name){
      if (!fptr) return;

      fptr->shortOpt = _shortArg;
      fptr->opt = _arg;
      fptr->description = _description;
      fptr->paramPtr = _ptr;
      fptr->paramName = _par_name;
}

void new_opt(const char *shortOpt, const char *option, const char *description, bool *resptr){
      // allocate memory
      if (opt_count == opt_capacity){
            if (opt_count == 0){
                  options = (Option**)malloc(sizeof(Option*)); // room for one
                  opt_capacity = 1;
            }else {
                  options = (Option**)realloc(options, (opt_capacity * 2) * sizeof(Option*));
                  opt_capacity *= 2;
            }

            if (!options){
                  printf("Allocation failed.\n");
                  exit(1);
            }
      }
      
      // create & add new flag
      Option *f = (Option*)malloc(sizeof(Option));
      init_opt(f, shortOpt, option, description, resptr, NULL);
      options[opt_count++] = f;
}

void new_opt_arged(const char *shortOpt, const char *option, const char* par_name, const char *description, char **resptr){
      // allocate memory
      if (opt_count == opt_capacity){
            if (opt_count == 0){
                  options = (Option**)malloc(sizeof(Option*)); // room for one
                  opt_capacity = 1;
            }else {
                  options = (Option**)realloc(options, (opt_capacity * 2) * sizeof(Option*));
                  opt_capacity *= 2;
            }

            if (!options){
                  printf("Allocation failed.\n");
                  exit(1);
            }
      }
      
      // create & add new flag
      Option *f = (Option*)malloc(sizeof(Option));
      init_opt(f, shortOpt, option, description, resptr, par_name);
      options[opt_count++] = f;

}

void parse_args(int argc, char **argv){
      for (int i = 1; i < argc; i++){ // first argument is program name
            bool hasMatch = false;
            char *curr_arg = argv[i];

            // find matching option
            for (int j = 0; j < opt_count; j++){
                  Option* curr_opt_ptr = options[j];
                  // check match
                  if (strcmp(curr_arg, curr_opt_ptr->shortOpt ? curr_opt_ptr->shortOpt : "") == 0 ||
                              strcmp(curr_arg, curr_opt_ptr->opt ? curr_opt_ptr->opt : "") == 0) {
                        // has argument?
                        if (curr_opt_ptr->paramPtr){
                              if (curr_opt_ptr->paramName){ // if paramname given result is hold by char*
                                    // DIKKAT : bu büyük ihtimalle işe yaramayacak!!
                                    if (argc > (i + 1)){
                                          *(char**)(curr_opt_ptr->paramPtr) = argv[i+1];
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

            // print error if no matching flag/command
            if (!hasMatch){
                  printf("%s: invalid option -- '%s'\n", programName, curr_arg);
                  printf("Try '%s --help' for more information.\n", programName);
                  exit(1);
            }

      }
}

void strike(){
      // free all
      for (int i = 0; i < opt_count; i++){
            free(options[i]);
      }
      free(options);
}
