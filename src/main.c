#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 4096

#define CORRUPTED_GIT_CONFIG_MSG "Corrupted .git/config file\n"

#define TRUE 1
#define FALSE 0

struct user_info {
    const char* name;
    const char* email;
} typedef user_info;

void throw_err(const char *msg)
{
    puts(msg);
    exit(1);
}

int header_line(const char *buf)
{
    return (buf[0] == '[') ? 1 : 0;
}

int contains_header(const char *buf, const char *header_val)
{
    int closing_brace_idx = (int)(strchr(buf, (int)']') - buf);
    if (closing_brace_idx < 0)
    {
        throw_err(CORRUPTED_GIT_CONFIG_MSG);
    }
    char *header = calloc(sizeof(char), sizeof(closing_brace_idx + 2));
    strncpy(header, buf, closing_brace_idx + 1);
    header[closing_brace_idx + 1] = '\0';
    if (strcmp(header_val, header) == 0)
    {
        free(header);
        return 1;
    }
    free(header);
    return 0;
}

char* get_property(const char* buf) {
    
}

int main()
{
    FILE *cf = fopen(".git/config", "r");
    FILE *tf = fopen("tmp", "w");

    char *buf = calloc(sizeof(char), BUF_SIZE);

    user_info info;

    int user_found = 0;

    // writing file until [user] found
    while (fgets(buf, BUF_SIZE, cf))
    {
        if (!user_found && header_line(buf) && contains_header(buf, "[user]"))
        {

            user_found = 1;
            fgets(buf, BUF_SIZE, cf);

            int skip = 0;
            while (buf[skip] == ' ')
                skip++;

            printf("skip: %d\n", skip);
            printf("buf: %s", buf);
            int equals_pos = strchr(buf + skip, (int)'=') - buf - skip;
            printf("equals-pos: %d\n", equals_pos);
            char *property = calloc(sizeof(char), equals_pos);
            strncpy(property, buf + skip, equals_pos);

            if(property[equals_pos] == ' ')
                property[equals_pos] = '\0';

            printf("property: %s\n", property);
            free(property);
        }
        fputs((const char *)buf, tf);
    }

    return 0;
}