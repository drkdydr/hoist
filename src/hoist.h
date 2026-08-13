#ifndef HOIST_H
#define HOIST_H

#include <stdbool.h>

typedef enum {
      INTEGER,
      LONG,
      FLOAT,
      DOUBLE,

      // check library included
      BOOLEAN, 
      STRING,

      FUNCTION, // assuming its void function with no arguments
      // NULL
} PTR_TYPE;

typedef struct {
      const char *shortFlag;
      const char *flag;
      const char *description;
      void *result;

      const char* paramName;
      void *paramPtr; // ((void (*)()) paramPtr)() this is how void function with no arguments is called from void pointer
      PTR_TYPE paramType;
      // param name yoksa param yoktur fakat yine function atayabilirsin
} Flag;

typedef struct {
      const char *command;
      const char *description;

      bool *result; // variable that will hold if command is selected
} Command;

// new_arg("-h", "--help", "shows this help message", boolptr, BOOL)
// new_arg("-h", "--help", "shows this help message", funcptr, FUNCTION)
// new_arg("-h", "--help", "shows this help message", NULL, NULL)



// initializes library
void hoist(const char* programName, const char* description);
// sonraki sürümlerde belki renklendirme özelliği de getiririz.

void init_flag(Flag* fptr, const char *shortFlag, const char *flag, const char *description, void *ptr, PTR_TYPE ptr_type, const char* par_name);

// creates new flag from scratch (with one argument if you want)
void new_flag(const char *shortFlag, const char *flag, const char *description, void *ptr, PTR_TYPE ptr_type, const char* par_name);

void init_command(Command* cptr, const char *command_str, const char * description, bool* res_ptr);

// creates new command
void new_command(const char *command_str, const char* description, bool *res_ptr);

// reads arguments and parse flags
void parse_args(int argc, char **argv);

// // adds parameter to existing flag
// void add_parameter(const char *shortArg, const char *arg, const char* argName, void *ptr, PTR_TYPE ptr_type);

#endif
