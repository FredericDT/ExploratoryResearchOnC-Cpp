
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

namespace fdt {
    int intL(unsigned long i) {
        return i >= 10 ? intL(i / 10) + 1 : 1;
    }
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
    char * fdt_strcat(int src_c, char *h, const char *v, ...) {
        strcat(h, v);
        va_list valist;
        va_start(valist, src_c);
        //char *r;
        for (int i = 0; i < src_c; i++) {
            strcat(h, va_arg(valist, const char *));
        }
        va_end(valist);
        return h;
    }
}

// test case for fdt_strcat
int main() {
    char *a = (char *) malloc(sizeof(char) * 10000);

    char *r = fdt::fdt_strcat(3, a, "first ", "second ", "third ", "end.");
    printf("%s", a);
    free(a);

}
