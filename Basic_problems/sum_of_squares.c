#include<stdio.h>
#include<math.h>
int summation(int n){
    return ((n*(n+1)*(2*n +1))/6);

}
int main(){
    int n;
    printf("enter a number :");
    scanf("%d",&n);
    printf("the sum is %d",summation(n));
    return 0;
}