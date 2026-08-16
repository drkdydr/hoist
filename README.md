# Hoist

C library for adding flags and arguments to your programs.

*Inspired by Python's* ***argparser*** *library*

***HOIST the colours high!!!***

### How to hoist

**hoist**: enter program name and description & it initializes library

**new_opt**: creates new option with no argument and holds found info in bool pointer

**new_opt_arged**: creates new option with one argument (I think one is enough) holds argument data in char pointer (if it can find)

**print_help()**: prints a help message from initialized options

**parse_args**: reads argv, parses arguments and sets results

**strike**: clears all data of hoist (opposite of word hoist I guess)


### Installation & Build

*make file will be added soon (I need to learn how to write makefiles first)    
Until I add you can install it in that way ( for linux ) :*    
    
    git clone https://github.com/drkdydr/hoist
    cd hoist
    mkdir build && cd build

    # compile & copy to needed places
    gcc -c -fPIC ../src/hoist.c -o hoist.o
    gcc -shared -Wl,-soname,libhoist.so.1 -o libhoist.so.1.0 hoist.o
    ln -sf libhoist.so.1.0 libhoist.so.1
    ln -sf libhoist.so.1 libhoist.so
    sudo cp ../src/hoist.h /usr/local/include/
    sudo cp -P libhoist.so* /usr/local/lib64/

    # load changes
    sudo ldconfig

    # check if os finds it
    ldconfig -p | grep hoist

if this does not work:

    # check if /usr/local/lib64/ is added to ldconfig's browse list
    cat /etc/ld.so.conf.d/*.conf

*if you can see /usr/local/lib64/ in output I do not know the problem ( you are on your own )*

if you cannot see : 

    echo "/usr/local/lib64" | sudo tee /etc/ld.so.conf.d/local-lib64.conf
    sudo ldconfig

***How you use it in your code:***

    gcc src/*.c -o test -lhoist

> *Note: I am a total newbie at this library stuff*
