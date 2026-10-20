/*
 * Assignment: Polynomial Addition using a Circular Singly Linked List
 *             (terms entered one at a time)
 */
#include <stdio.h>
#include <stdlib.h>

#ifdef INTERACTIVE
#define PROMPT(...) printf(__VA_ARGS__)
#else
#define PROMPT(...)
#endif

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
    if (head == NULL || coef == 0) return;

    pnode *prev = head;
    pnode *curr = head->next;

    // Traverse to find position keeping descending exponent order
    while (curr != head && curr->exp > exp) {
        prev = curr;
        curr = curr->next;
    }

    // Combine terms if equal exponent exists
    if (curr != head && curr->exp == exp) {
        curr->coef += coef;
        // Remove node if coefficient becomes 0
        if (curr->coef == 0) {
            prev->next = curr->next;
            free(curr);
        }
    } else {
        // Insert new node in order
        pnode *newNode = (pnode *)malloc(sizeof(pnode));
        if (newNode != NULL) {
            newNode->coef = coef;
            newNode->exp = exp;
            newNode->next = curr;
            prev->next = newNode;
        }
    }
}

/* Read one polynomial: keep asking for terms until the answer is not 1. */
pnode *read_poly(void)
{
    pnode *head = new_poly();
    int ch, c, e;

    while (1) {
        PROMPT("Do you want to enter a term? (1 = yes, 0 = no): ");   // provided
        if (scanf("%d", &ch) != 1 || ch != 1)                         // provided
            break;                                                   // provided
        PROMPT("Enter coefficient and exponent: ");                   // provided
        if (scanf("%d %d", &c, &e) != 2)                             // provided
            break;                                                   // provided

        insert_term(head, c, e);
    }
    return head;
}

/* Return a NEW polynomial equal to h1 + h2. Do not modify h1 or h2. */
pnode *poly_add(pnode *h1, pnode *h2)
{
    pnode *sum = new_poly();

    if (h1 != NULL) {
        pnode *p1 = h1->next;
        while (p1 != h1) {
            insert_term(sum, p1->coef, p1->exp);
            p1 = p1->next;
        }
    }

    if (h2 != NULL) {
        pnode *p2 = h2->next;
        while (p2 != h2) {
            insert_term(sum, p2->coef, p2->exp);
            p2 = p2->next;
        }
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
    PROMPT("Enter the first polynomial\n");
    pnode *p1 = read_poly();
    PROMPT("Enter the second polynomial\n");
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
