#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "utils.h"

bool is_number(char *str)
{
    if (strlen(str) == 0 || (strlen(str) == 1 && str[0] == '-'))
    {
        return false;
    }

    if (!isdigit(str[0]) && str[0] != '-')
    {
        return false;
    }

    for (size_t i = 1; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}

bool not_empty(char *str)
{
    return strlen(str) > 0;
}

void clear_input_buffer()
{
    int c;

    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int read_string(char *buf, int buf_siz)
{
    int c;
    int i = 0;
    
    do
    {
        c = getchar();
        
        buf[i] = c;
        
        i++;
    } while (c != '\0' && c != '\n' && c != EOF && i < buf_siz);

    if (i == buf_siz && (c != '\0' && c != '\n' && c != EOF))
    {
        clear_input_buffer();
    }

    buf[i - 1] = '\0';

    return i - 1;
}

answer_t ask_question(char *question, check_func_t *check, convert_func_t *convert)
{
    int buf_siz = 255;
    char buf[buf_siz];
    
    do
    {
        printf("%s\n", question);
        read_string(buf, buf_siz);
    } while (!check(buf));

    return convert(buf);
}

int ask_question_int(char *question)
{
    return ask_question(question, is_number, (convert_func_t *)atoi).int_value;
}

char *ask_question_string(char *question)
{
    return ask_question(question, not_empty, (convert_func_t *) strdup).string_value;
}
