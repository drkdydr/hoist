#ifndef HOIST_H
#define HOIST_H

#include <stdbool.h>

typedef struct {
      const char *shortOpt;
      const char *opt;
      const char *description;

      void *paramPtr;
      const char *paramName;

      // param name yoksa param yoktur fakat yine function atayabilirsin
} Option; // flag'ler ile command'ler aynıdır (command flag'in short ve normal argumanı birlikte bulundurmayan halidir.)

// new_arg("-h", "--help", "shows this help message", ptr, "HASHELP")
// new_arg("-h", "--help", "shows this help message", NULL, NULL)

// debug:
void paramCount();

// initializes library
void hoist(const char* programName, const char* description);
// sonraki sürümlerde belki renklendirme özelliği de getiririz.

// void init_opt(Option* fptr, const char *shortFlag, const char *flag, const char *description, void *ptr, const char* par_name);

// creates new option from scratch with no argument (existance of option is hold by boolean pointer)
void new_opt(const char *shortFlag, const char *flag, const char *description, bool *ptr);
// if par_name is NULL then pointer is bool pointer and holds "has found" information

// creates new option with one argument next to it
void new_opt_arged(const char *shortFlag, const char *flag, const char *description, char *ptr, const char* par_name);

// reads arguments and parse flags
void parse_args(int argc, char **argv);

// // adds parameter to existing flag
// void add_parameter(const char *shortArg, const char *arg, const char* argName, void *ptr, PTR_TYPE ptr_type);

#endif
