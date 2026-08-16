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

// initializes library (does not generate help option (you need to do that))
void hoist(const char* programName, const char* description);
// sonraki sürümlerde belki renklendirme özelliği de getiririz.

// creates new option from scratch with no argument (existance of option is hold by boolean pointer)
void new_opt(const char *shortOption, const char *option, const char *description, bool *resptr);
// if par_name is NULL then pointer is bool pointer and holds "has found" information

// creates new option with one argument next to it (holds argument in char* (no type casting))
void new_opt_arged(const char *shortOption, const char *option, const char* par_name, const char *description, char **resptr);

// prints help message with initialized options (you can assign to your help flags)
void print_help();

// reads arguments and parse flags
void parse_args(int argc, char **argv);

// ends hoist and clears frees all data (strike is opposite of hoist)
void strike();

#endif
