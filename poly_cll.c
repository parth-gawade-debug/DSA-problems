#include <stdio.h>
#include <stdlib.h>

struct node
{
    int coe, exp;
    struct node *next;
};
void CLL_create(struct node *head, int deg);
void display(struct node *head);
void poly_add(struct node *head1, struct node *head2);
int main()
{
    struct node *head1, *head2;
    int deg;
    head1 = (struct node *)malloc(sizeof(struct node));
    head1->next = head1;
    head2 = (struct node *)malloc(sizeof(struct node));
    head2->next = head2;

    printf("Enter the degree of first polynomial: ");
    scanf("%d", &deg);
    CLL_create(head1, deg);

    printf("Enter the degree of second polynomial: ");
    scanf("%d", &deg);
    CLL_create(head2, deg);

    printf("\nFirst polynomial: ");
    display(head1);
    printf("Second polynomial: ");
    display(head2);
    printf("Sum of polynomials:\n");
    poly_add(head1, head2);
    return 0;
}
void CLL_create(struct node *head, int deg)
{
    struct node *last = head, *ptr;
    int i;
    for (i = deg; i >= 0; i--)
    {
        ptr = (struct node *)malloc(sizeof(struct node));
        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &ptr->coe, &ptr->exp);
        last->next = ptr;
        ptr->next = head;
        last = ptr;
    }
}
void display(struct node *head)
{
    struct node *temp = head->next;
    while (temp != head)
    {
        printf("%dx^%d", temp->coe, temp->exp);
        temp = temp->next;
        if (temp != head)
            printf(" + ");
    }
    printf("\n");
}
void poly_add(struct node *head1, struct node *head2)
{
    struct node *head3, *t1, *t2, *t3, *ptr;
    head3 = (struct node *)malloc(sizeof(struct node));
    head3->next = head3;
    t1 = head1->next;
    t2 = head2->next;
    t3 = head3;
    while (t1 != head1 || t2 != head2)
    {
        if (t1 == head1)
        {
            ptr = (struct node *)malloc(sizeof(struct node));
            ptr->coe = t2->coe;
            ptr->exp = t2->exp;
            t2 = t2->next;
        }
        else if (t2 == head2)
        {
            ptr = (struct node *)malloc(sizeof(struct node));
            ptr->coe = t1->coe;
            ptr->exp = t1->exp;
            t1 = t1->next;
        }
        else if (t1->exp == t2->exp)
        {
            ptr = (struct node *)malloc(sizeof(struct node));
            ptr->exp = t1->exp;
            ptr->coe = t1->coe + t2->coe;
            t1 = t1->next;
            t2 = t2->next;
        }
        else if (t1->exp > t2->exp)
        {
            ptr = (struct node *)malloc(sizeof(struct node));
            ptr->exp = t1->exp;
            ptr->coe = t1->coe;
            t1 = t1->next;
        }
        else
        {
            ptr = (struct node *)malloc(sizeof(struct node));
            ptr->exp = t2->exp;
            ptr->coe = t2->coe;
            t2 = t2->next;
        }
        t3->next = ptr;
        t3 = ptr;
        ptr->next = head3;
    }
    printf("Result: ");
    display(head3);
}
