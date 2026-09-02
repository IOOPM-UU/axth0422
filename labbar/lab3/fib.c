#include <stdio.h>
#include <stdlib.h>


int fib_helper(int pf, int ppf, int num)
{
    if (num == 0)
    {
        return pf;
    }

    return fib_helper(pf + ppf, pf, num - 1);
}


int fib(int num)
{
    if (num < 0)
    {
        return -1;
    }

    if (num == 0)
    {
        return 0;
    }

    int ppf = 0;
    int pf  = 1;

    return fib_helper(pf, ppf, num - 1);
}


int main()
{
    printf("%d\n", fib(1));
}