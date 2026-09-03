#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char *strdup(const char *);

typedef union
{
    int int_value;
    float float_value;
    char *string_value;
} answer_t;

typedef bool check_func_t(char *);

typedef answer_t convert_func_t(char *);

answer_t ask_question(char *question, check_func_t *check, convert_func_t *convert)
{
    int buf_siz = 255;
    char buf[buf_siz];
    char *answer;
    
    do
    {
        printf("%s\n", question);
        read_string(buf, buf_siz);
    } while (!check(buf));

    return convert(answer);
}

int ask_question_int(char *question)
{
    return ask_question(question, is_number, (convert_func_t *)atoi).int_value;
}

bool not_empty(char *str)
{
    return strlen(str) > 0;
}

char *ask_question_string(char *question)
{
    return ask_question(question, not_empty, (convert_func_t *) strdup).string_value;
}

int main(void)
{
    return 0;
}