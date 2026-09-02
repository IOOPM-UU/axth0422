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

    for (int i = 1; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}

void clear_input_buffer()
{
    int c;

    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int ask_question_int(char *question)
{
    int result = 0;
    int conversions = 0;
    char str[255];

    do
    {
        printf("%s\n", question);
        conversions = scanf("%d", &result);

        sprintf(str, "%d", result);

        clear_input_buffer();

        putchar('\n');
    } while (conversions < 1 || !is_number(str));

    return result;
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

char *ask_question_string(char *question, char *buf, int buf_siz)
{
    int length;

    do
    {
        printf("%s\n", question);
        length = read_string(buf, buf_siz);
    } while (length == 0);

    return buf;
}
