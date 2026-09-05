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
void add_poly(struct term p1[],struct term p2[], struct term sum[],int deg1,int deg2) {
    int i=deg1;
    int j=deg2;
    int k=0;
    while(i>=0 && j>=0) {
        if (p1[i].exp == p2[j].exp) {
            sum[k].coeff = p1[i].coeff + p2[j].coeff;
            sum[k].exp = p1[i].exp;
            i--;
            j--;
            k++;
        }
        else if (p1[i].exp > p2[j].exp) {
            sum[k].coeff = p1[i].coeff;
            sum[k].exp = p1[i].exp;
            i--;
            k++;
        }
        else {
            sum[k].coeff = p2[j].coeff;
            sum[k].exp = p2[j].exp;
            j--;
            k++;
        }
    }
    while(i>=0) {
        sum[k].coeff = p1[i].coeff;
        sum[k].exp = p1[i].exp;
        i--;
        k++;
    }
    while(j>=0) {
        sum[k].coeff = p2[j].coeff;
        sum[k].exp = p2[j].exp;
        j--;
        k++;
    }    
}
void poly_eval(struct term p[],int deg) {
    int x;
    printf("Enter value of x: ");
    scanf("%d", &x);
    int result = 0;
    for(int i=0; i<=deg; i++) {
        result += p[i].coeff * pow(x, p[i].exp);
    }
    printf("polynomial evaluated at x=%d is %d\n", x, result);
}

