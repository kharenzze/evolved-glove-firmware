/**
* Created by Pablo Ráez @kharenzze
* Util functions
**/

namespace EGUtils {
    inline void clearscreen(void) {
        printf("\033[2J\033[1;1H");
    }
}