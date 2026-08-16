#include <stdio.h>
#include <hoist.h>

int main(int argc, char **argv){

      // no argument option result holders
      bool helpwanted = false;
      bool willClear = false;

      // arged option argument data holders
      char *filename;
      char *height_str;
      char *width_str;

      // initialize library
      hoist("test", "test program for library hoist");

      // add options (flag/command) with no arguments (takes bool argument to hold if flag is found)
      new_opt("-h", "--help", "prints this help message", &helpwanted); // flags
      new_opt(NULL, "clear", "starts clear function", &willClear); // also you can use it to add command

      // add options (flag/command) with one argument (I think one is enough) (set char* argument's address to option's argument address)
      new_opt_arged("-f", "--file", "FILE", "give me filename", &filename);
      new_opt_arged("-h", NULL, "HEIGHT", "sets height to HEIGHT", &height_str); // no type casting (and never will come) so you need to convert to wanted type
      new_opt_arged("-w", NULL, "WIDTH", "sets width to WIDTH", &width_str);

      // reads given arguments, parses options and sets results
      parse_args(argc, argv);

      if (helpwanted) print_help(); // built-in help function from initialized options

      // clears all data of hoist (do not add option or call print_help() after this)
      strike(); 
}
