#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

int unlink(char *fname) {
    if (strstr(fname, "PROTECT") != NULL) {
        return 1;
    }
    int (*unl)(char *fname) = dlsym(RTLD_NEXT, "unlink");
    return unl(fname);
}