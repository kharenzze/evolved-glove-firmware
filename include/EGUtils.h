/**
* Created by Pablo Ráez @kharenzze
* Util functions
**/

#include <stdio.h>
#include <stdexcept>

namespace EGUtils {
    inline void clearscreen(void) {
        printf("\033[2J\033[1;1H");
    }

    inline void error (std::string s) {
        throw std::runtime_error (s);
    }
}