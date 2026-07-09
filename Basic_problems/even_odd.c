#include <math.h>
#include <stdio.h>
#include <stdbool.h> // for using boolean datatype in c

bool isEven(int n)
{
    // taking bitwise and of n with 1 
    if ((n & 1) == 0)
        return true;
    else
        return false;
}

int main()
{
    int n = 14;
    if (isEven(n))
    {
        printf("true");
    }
    else
    {
        printf("false");
    }
    return 0;
}