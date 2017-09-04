/**
* Created by Pablo Ráez @kharenzze
* Util functions
**/

#include <stdio.h>
#include <stdexcept>
#include <EGConfig.h>

namespace EGUtils {
    inline void clearscreen(void) {
        printf("\033[2J\033[1;1H");
    }

    inline void error (std::string s) {
        throw std::runtime_error (s);
    }

    inline void appendFloatToPacketBuffer (float number, char* buffer, int* length) {
        char* numberAsBytes = (char*) &number;
        int bytesLength = sizeof(float);
        int newLength = *length + bytesLength;
        if (newLength >= BUFFER_LEN) {
            error("Exceed packet length");
        }
        int j = 0;
        for (int i = *length; i < newLength; i++) {
            buffer[i] = numberAsBytes[j];
            j++;
        }
        *length = newLength;
    }

    inline void appendDoubleToPacketBuffer (double number, char* buffer, int* length) {
        char* numberAsBytes = (char*) &number;
        int bytesLength = sizeof(double);
        int newLength = *length + bytesLength;
        if (newLength >= BUFFER_LEN) {
            error("Exceed packet length");
        }
        int j = 0;
        for (int i = *length; i < newLength; i++) {
            buffer[i] = numberAsBytes[j];
            j++;
        }
        *length = newLength;
    }

    inline void appendIntToPacketBuffer (int number, char* buffer, int* length) {
        char* numberAsBytes = (char*) &number;
        int bytesLength = sizeof(int);
        int newLength = *length + bytesLength;
        if (newLength >= BUFFER_LEN) {
            error("Exceed packet length");
        }
        int j = 0;
        for (int i = *length; i < newLength; i++) {
            buffer[i] = numberAsBytes[j];
            j++;
        }
        *length = newLength;
    }
}