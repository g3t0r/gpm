#include "profile-reader.h"
#include "error-handling.h"
#include "errno.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

const char *get_gpm_dir_path() {
    char* str = calloc(sizeof(char), 256);
    strcat(str, getenv("HOME"));
    strcat(str, "/.gpm");

    return str;
}

FILE *get_gpm_dir()
{
    const char *path = get_gpm_dir_path();
    FILE* f = fopen(path, "r+");
    free((char *)path);
    return f;
}

void init_gpm_dir()
{
    const char *path = get_gpm_dir_path();
    printf("Trying to create: %s\n", path);
    if(mkdir(path, 0700)) {
        perror(strerror(errno));
        throw_err("Error while initializing dir");
    }
    free((char *)path);
}

int main()
{

    init_gpm_dir();

    return 0;
}