#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace fdt {
    int intL(unsigned long i) {
        return i >= 10 ? intL(i / 10) + 1 : 1;
    }

    // notify: you need to free the returned pointer to avoid a memory leak
    char * itos(unsigned long i) {
        int l = intL(i);
        char *r = (char *) malloc(sizeof(char) * l + 1);
        memset(r, 0, l + 1);
        for (int j = 0; j < l; ++j) {
            r[l - 1 - j] = '0' + i % 10;
            i /= 10;
        }
        return r;
    }
}
