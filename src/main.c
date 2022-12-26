#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "parse-utils.h"

#define BUF_SIZE 4096
#define MSG_CORRUPTED_GIT_CONFIG "Corrupted .git/config file\n"
#define CHAR_SPACE ' '
#define CHAR_LEFT_SQUARE_BRACKET '['
#define CHAR_RIGHT_SQUARE_BRACKET ']'
#define CHAR_EQUALS '='

#define TRUE 1
#define FALSE 0

void throw_err(const char *msg)
{
    puts(msg);
    exit(1);
}

int header_line(const char *buf)
{
    return (buf[0] == CHAR_LEFT_SQUARE_BRACKET) ? 1 : 0;
}

int contains_header(const char *buf, const char *header_val)
{
    int closing_brace_idx = (int)(strchr(buf, (int)CHAR_RIGHT_SQUARE_BRACKET) - buf);
    if (closing_brace_idx < 0)
    {
        throw_err(MSG_CORRUPTED_GIT_CONFIG);
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

int main()
{
    FILE *cf = fopen(".git/config", "r");
    FILE *tf = fopen("tmp", "w");

    char *buf = calloc(sizeof(char), BUF_SIZE);

    int user_found = 0;
    char* fgets_result = fgets(buf, BUF_SIZE, cf);
    // writing file until [user] found
    while (fgets_result)
    {

        // switch(get_line_type(buf)) {
        //     case HEADER:
        //         printf("Header: %s", buf);
        //         break;
            
        //     case PROPERTY:
        //         printf("Property: %s", buf);
        //         break;

        //     case OTHER:
        //         printf("Other: %s", buf);
        // }




        if (!user_found && header_line(buf))
        {
            // user_found = 1;
            fgets(buf, BUF_SIZE, cf);
            property *prop = parse_property(buf);
            printf("%s:%s[NEXT]", prop->name, prop->value);
            free(prop->name);
            free(prop->value);
            fgets(buf, BUF_SIZE, cf);
            prop = parse_property(buf);
            printf("%s:%s[NEXT]", prop->name, prop->value);
        }
        fputs((const char *)buf, tf);

    fgets_result = fgets(buf, BUF_SIZE, cf);

    }

    return 0;
}