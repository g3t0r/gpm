#ifndef PARSE_UTILS
#define PARSE_UTILS

#define CHAR_SPACE ' '
#define CHAR_TAB '\t'
#define CHAR_LEFT_SQUARE_BRACKET '['
#define CHAR_RIGHT_SQUARE_BRACKET ']'
#define CHAR_EQUALS '='

struct property
{
    char *name;
    char *value;
} typedef property;

enum LINE_TYPE
{
    HEADER,
    PROPERTY,
    OTHER
} typedef LINE_TYPE;

int is_whitespace(char c);

char *parse_header(char *buf);

void write_property(char* dst, property* prop);

LINE_TYPE get_line_type(const char *buf);

property *parse_property(char *buf);

#endif