//1st method using 3rd variable
#include <stdio.h>
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main() {
    int x, y;
    printf("Enter two numbers: ");
    scanf("%d %d", &x, &y);
    printf("Before swapping: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("After swapping: x = %d, y = %d\n", x, y);
    return 0;
}
//2nd method  without using 3rd variable
#include <stdio.h>

int main() {
    int a = 10, b = 20;

    // swap two numbers using arithmetic operators
    a = a + b;
    b = a - b;
    a = a - b;

    printf("%d %d\n", a, b);
    return 0;
}
//3rd method using bitwise XOR operator
#include <stdio.h>

int main() {
    int a = 10, b = 20;
    
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    
    printf("%d %d\n", a, b);
    return 0;
}