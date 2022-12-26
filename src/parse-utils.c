#include <stdlib.h>
#include <string.h>
#include "parse-utils.h"

#include <stdio.h>

int is_whitespace(char c)
{
    return (c == CHAR_SPACE || c == CHAR_TAB) ? 1 : 0;
}

char *parse_header(char *buf)
{
    int length_without_terminating = strlen(buf);
    char *header = malloc(sizeof(*header) * length_without_terminating);
    // copying without \n, already null terminated because of calloc
    strncpy(header, buf, length_without_terminating - 1);
    header[length_without_terminating -1] = 0;

    return header;
}

void write_property(char *dst, property *prop)
{
    strncat(dst, "\t", strlen(prop->name));
    strncat(dst, prop->name, strlen(prop->name));
    strncat(dst, " ", 2);
    strncat(dst, "=", 2);
    strncat(dst, " ", 2);
    strncat(dst, prop->value, strlen(prop->value));
    strncat(dst, "\n", 2);
}

property *parse_property(char *buf)
{

    property *prop = malloc(sizeof prop);

    int skip = 0;
    while (is_whitespace(buf[skip]))
        skip++;

    int equals_pos = strchr(buf + skip, (int)CHAR_EQUALS) - buf - skip;
    prop->name = calloc(sizeof(char), equals_pos);
    strncpy(prop->name, buf + skip, equals_pos);

    if (is_whitespace(prop->name[equals_pos - 1]))
        prop->name[equals_pos - 1] = '\0';

    int value_start_idx = equals_pos + (is_whitespace(buf[equals_pos + 1 + skip]) ? 2 : 1);

    prop->value = calloc(sizeof(char), strlen(buf) + 1 - value_start_idx);
    strncpy(prop->value, buf + skip + value_start_idx, strlen(buf) - value_start_idx);
    prop->value[strlen(prop->value) - 1] = '\0';

    return prop;
}

LINE_TYPE get_line_type(const char *buf)
{
    switch (buf[0])
    {
    case CHAR_LEFT_SQUARE_BRACKET:
        return HEADER;

    case CHAR_TAB:
    case CHAR_SPACE:
        return PROPERTY;

    default:
        return OTHER;
    }
}
