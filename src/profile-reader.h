#ifndef PROFILE_READER
#define PROFILE_READER

#include "sys/stat.h"
#include "sys/types.h"
#include "stdio.h"

#define MSG_GPM_UNINITIALIZED "gpm dir not uninitialized"


struct profile_list
{
    int size;
    char *profiles;
} typedef profile_list;

struct profile
{
    char *profile_name;
    char *author_name;
    char *author_email;

} typedef profile;

FILE *get_gpm_dir();
void init_gpm_dir();
profile_list get_profiles(const FILE *const gpm_dir);

#endif