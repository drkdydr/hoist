#include "hoist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static Flag** flags;
static int flag_count;

static Command** commands;
static int command_count;

static const char *programName;
static const char *description;

void print_help(){
      printf("usage: %s", programName);
      // if there are other flags different than help
      if (flag_count > 1) printf(" [OPTIONS]");
      // if there are any commands
      if (command_count > 0) printf(" [COMMANDS]");
      printf("\n");
      printf("%s\n", description);

      if (command_count > 1) printf("\ncommands:\n");
      for (int i = 0; i < command_count; i++){
            Command *curr = commands[i];
            printf("  %s:\t%s\n", curr->command, curr->description);//  auth:          Authenticate gh and git with GitHub
      }

      if (flag_count > 0) printf("\noptions:\n");
      for (int i = 0; i < flag_count; i++){
            Flag *curr = flags[i];
            printf("  %s, %s %s\t%s\n", curr->shortFlag, curr->flag, curr->paramName, curr->description);
      }
}

void hoist(const char *_programName, const char *_description){
      // initalize library
      flag_count = 0;
      programName = _programName;
      description = _description;

      // include help flag
      void (*helpPtr) ();
      helpPtr = &print_help;
      new_flag("-h", "--help", "prints this help message", helpPtr, FUNCTION, NULL);
}

void init_flag(Flag *fptr, const char *_shortArg, const char *_arg, const char *_description, void *_ptr, PTR_TYPE _ptr_type, const char *_par_name){
      if (!fptr) return;

      fptr->shortFlag = _shortArg;
      fptr->flag = _arg;
      fptr->description = _description;
      fptr->paramPtr = _ptr;
      fptr->paramType = _ptr_type;
      fptr->paramName = _par_name;
}

void new_flag(const char *shortFlag, const char *flag, const char *description, void *paramPtr, PTR_TYPE paramTYPE, const char *paramName){
      // allocate memory
      if (flag_count == 0){
            flags = (Flag**)malloc((flag_count + 1) * sizeof(Flag*));
      }else {
            flags = (Flag**)realloc(flags, (flag_count + 1) * sizeof(Flag*));
      }

      if (flags == NULL){
            printf("Allocation failed.\n");
            exit(1);
      }
      
      // create & add new flag
      Flag *f = (Flag*)malloc(sizeof(Flag));
      init_flag(f, shortFlag, flag, description, paramPtr, paramTYPE, paramName);
      flags[flag_count++] = f;
}

void init_command(Command* cptr, const char *_command_str, const char * _description, bool* _res_ptr){
      if (!cptr) return;

      cptr->command = _command_str;
      cptr->description = _description;
      cptr->result = _res_ptr;
}

void new_command(const char *command_str, const char* description, bool *res_ptr){
      if (command_count == 0){
            commands = (Command**)malloc((command_count + 1) * sizeof(Command*));
      }else{
            commands = (Command**)realloc(commands, (command_count + 1) * sizeof(Command*));
      }

      if (commands == NULL){
            printf("Allocation failed.\n");
            exit(1);
      }

      Command *c = (Command*)malloc(sizeof(Command));
      init_command(c, command_str, description, res_ptr);
      commands[command_count++] = c;
}

void parse_args(int argc, char **argv){
      for (int i = 0; i < argc; i++){

      }

      // free all
      for (int i = 0; i < flag_count; i++){
            free(flags[i]);
      }
      free(flags);
}
