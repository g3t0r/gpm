#include "error-handling.h"
#include "stdio.h"
#include "stdlib.h"

void throw_err(const char *msg)
{
    puts(msg);
    exit(1);
}