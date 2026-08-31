#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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

void print_number(int number, int final)
{
    if (number % 5 == 0 && number % 3 == 0)
        {
            printf("Fizz Buzz");
        }
        else if (number % 5 == 0)
        {
            printf("Buzz");
        }
        else if (number % 3 == 0)
        {
            printf("Fizz");
        }
        else
        {
            printf("%d", number);
        }

        if (number != final)
        {
            printf(", ");
        }
}

int main(int argc, char *argv[])
{
    if (argc != 2 || !is_number(argv[1]) || atoi(argv[1]) < 1)
    {
        printf("Please enter valid arguments\n");
        return 1;
    }

    int max = atoi(argv[1]);

    for (int i = 1; i <= max; i++)
    {
        print_number(i, max);
    }

    printf("\n");

    return 0;
}