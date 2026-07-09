#include <stdio.h>
int main()
{
    int n, sum = 0;
    printf("enter a number: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        sum = sum + i;
    }
    printf("sum of first %d natural numbers is %d", n, sum);
    return 0;
}
// here we can also use a formula method where we create a function and in the return section we could write the formula of n*(n+1)/2 to get the sum of natural numbers.
