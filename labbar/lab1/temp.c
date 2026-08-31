#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_number(char *str)
{
    if (strlen(str) == 0)
    {
        return false;
    }

    if (strlen(str) == 1 && str[0] == '-')
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

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Please provide 1 CLI argument\n");
        return 1;
    }

    if (is_number(argv[1]))
    {
        printf("%s is a number\n", argv[1]);
    }
    else
    {
        printf("%s is not a number\n", argv[1]);
    }

    return 0;

}