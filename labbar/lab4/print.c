#include <stdio.h>

void print(char *str)
{
    for (; *str != '\0'; str++)
    {
        putchar(*str);
    }
}

int main(void)
{
    print("Jaha!\n");
    return 0;
}