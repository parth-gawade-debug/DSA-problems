/*
 * Assignment: Polynomial Addition using a Circular Singly Linked List
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int coef;
    int exp;
    struct node *next;
} pnode;

/* Create an empty circular list (header node only) and return the header. */
pnode *new_poly(void)
{
    pnode *head = (pnode *)malloc(sizeof(pnode));
    if (head != NULL) {
        head->coef = 0;
        head->exp = -1;
        head->next = head;
    }
    return head;
}

/* Insert a term keeping the list in descending exponent order.
   Combine with an existing term of the same exponent; remove it if the
   resulting coefficient is 0. Ignore terms whose coefficient is 0. */
void insert_term(pnode *head, int coef, int exp)
{
    if (coef == 0) return;

    pnode *prev = head;
    pnode *curr = head->next;

    // Traverse until we find the position or an existing term with equal exponent
    while (curr != head && curr->exp > exp) {
        prev = curr;
        curr = curr->next;
    }

    // If a term with the same exponent already exists, combine them
    if (curr != head && curr->exp == exp) {
        curr->coef += coef;
        if (curr->coef == 0) {
            prev->next = curr->next;
            free(curr);
        }
    }
    // Otherwise, insert a new term node before curr
    else {
        pnode *newNode = (pnode *)malloc(sizeof(pnode));
        if (newNode != NULL) {
            newNode->coef = coef;
            newNode->exp = exp;
            newNode->next = curr;
            prev->next = newNode;
        }
    }
}

/* Read one polynomial from stdin in the format described above. */
pnode *read_poly(void)
{
    pnode *head = new_poly();
    int n, coef, exp;

    if (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            if (scanf("%d %d", &coef, &exp) == 2) {
                insert_term(head, coef, exp);
            }
        }
    }
    return head;
}

/* Return a NEW polynomial equal to h1 + h2. Do not modify h1 or h2. */
pnode *poly_add(pnode *h1, pnode *h2)
{
    pnode *sum = new_poly();

    pnode *p1 = h1->next;
    while (p1 != h1) {
        insert_term(sum, p1->coef, p1->exp);
        p1 = p1->next;
    }

    pnode *p2 = h2->next;
    while (p2 != h2) {
        insert_term(sum, p2->coef, p2->exp);
        p2 = p2->next;
    }

    return sum;
}

/* Release every node including the header. */
void free_poly(pnode *head)
{
    if (head == NULL) return;

    pnode *curr = head->next;
    while (curr != head) {
        pnode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(head);
}

/* ---------------- provided - do not modify ---------------- */
void print_poly(pnode *head)
{
    pnode *p = head->next;

    if (p == head) {
        printf("0\n");
        return;
    }
    while (p != head) {
        printf("%+dx^%d", p->coef, p->exp);
        p = p->next;
        if (p != head)
            printf(" ");
    }
    printf("\n");
}

int main(void)
{
    pnode *p1 = read_poly();
    pnode *p2 = read_poly();
    pnode *sum = poly_add(p1, p2);

    printf("P1 = ");  print_poly(p1);
    printf("P2 = ");  print_poly(p2);
    printf("SUM = "); print_poly(sum);

    free_poly(p1);
    free_poly(p2);
    free_poly(sum);
    return 0;
}
