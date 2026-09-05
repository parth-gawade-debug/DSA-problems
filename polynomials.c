#include <stdio.h>
struct term {
    int coeff;
    int exp;
};
int main(){
    struct term p1[10], p2[10], sum[10];
    int i, j, k;
    int deg1, deg2;
    printf("Enter degree of first polynomial: ");
    scanf("%d", &deg1);
    printf("enter degree of second polynomial: ");
    scanf("%d", &deg2);
    return 0;
}
void accept(struct term p[], int deg) {
    for(int i = 0; i <= deg; i++) {
        printf("Enter coefficient for x^%d: ", i);
        scanf("%d", &p[i].coeff);
        p[i].exp = i;
    }
}
void display(struct term p[], int deg) {
    for(int i = deg; i >= 0; i--) {
        printf("%dx^%d", p[i].coeff, p[i].exp);
    }
}
