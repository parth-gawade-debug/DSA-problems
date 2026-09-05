#include <stdio.h>
#include<math.h>
struct term {
    int coeff;
    int exp;
};
int main(){
    struct term p1[10], p2[10], sum[10], product[20];
    int i, j, k;
    int deg1, deg2;
    printf("Enter degree of first polynomial: ");
    scanf("%d", &deg1);
    printf("enter degree of second polynomial: ");
    scanf("%d", &deg2);
    accept(p1, deg1);
    accept(p2, deg2);
    printf("First polynomial: ");
    display(p1, deg1);
    printf("\nSecond polynomial: ");
    display(p2, deg2);
    add_poly(p1, p2, sum, deg1, deg2);
    printf("\nSum of polynomials: ");
    display(sum, deg1>deg2?deg1:deg2);
    multiply_poly(p1, p2, product, deg1, deg2);
    printf("\nProduct of polynomials: ");
    display(product, deg1+deg2);
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
void multiply_poly(struct term p1[], struct term p2[], struct term product[], int deg1, int deg2) {
    int i =deg1;
    int k=0;
    while(i>=0) {
        int j=deg2;
        while(j>=0) {
            int coeff = p1[i].coeff * p2[j].coeff;
            int exp = p1[i].exp + p2[j].exp;

            for (int m=0;m<k;m++) {
                if(exp==product[m].exp) {
                    product[m].coeff += coeff;
                    break;
                }
                if(m==k-1) {
                    product[k].coeff = coeff;
                    product[k].exp = exp;
                    k++;
            }
            j--;
            }
        }    

}
