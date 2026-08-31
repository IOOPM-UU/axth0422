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

int gcd(int a, int b)
{
    while (a != b)
    {
        if (a > b)
        {
            a -= b;
        }
        else
        {
            b -= a;
        }
    }

    return a;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Please enter 2 CLI arguments\n");
        return 1;
    }

    if (!is_number(argv[1]) || !is_number(argv[2]))
    {
        printf("Please enter numbers as arguments\n");
        return 1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    if (a < 0 || b < 0)
    {
        printf("Please enter positive numbers\n");
        return 1;
    }

    int g = gcd(a, b);

    printf("gcd(%d, %d) = %d\n", a, b, g);

    return 0;
}