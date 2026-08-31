#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    int N = atoi(argv[1]);
    int limit = floor(sqrt(N)) + 1;

    for (int i = 2; i <= limit; i++)
    {
        for (int j = 2; j <= N; j++)
        {
            if (i*j == N)
            {
                printf("%d is not a prime number\n", N);
                return 0;
            }
        }
    }

    printf("%d is a prime number\n", N);

    return 0;
}