#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return 1;
    }
    else
    {
        int total = 0;
    
        for (int i = 1; i < atoi(argv[1]) + 1; i++)
        {
            for (int j = 1; j <= (i * atoi(argv[2])); j++)
            {
                printf("*");
                total++;
            }
            printf("\n");
        }
    
        printf("Totalt: %d\n", total);
    }
}