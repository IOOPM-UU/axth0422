#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdbool.h>
extern char *strdup(const char *);

typedef union
{
    int int_value;
    float float_value;
    char *string_value;
} answer_t;

typedef bool check_func_t(char *);

typedef answer_t convert_func_t(char *);

bool not_empty(char *str);

bool is_number(char *str);

void clear_input_buffer();

int read_string(char *buf, int buf_siz);

answer_t ask_question(char *question, check_func_t *check, convert_func_t *convert);

int ask_question_int(char *question);

char *ask_question_string(char *question);

#endif  