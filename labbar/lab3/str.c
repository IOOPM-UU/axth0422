#include <stdio.h>

int string_length(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        i++;
    }

    return i;
}

void print(char *str)
{
    int len = string_length(str);

    for (int i = 0; i < len; i++)
    {
        putchar(str[i]);
    }
}

int main()
{
    print("Jaha!\n");
    printf("Length: %d\n", string_length("abc"));
}