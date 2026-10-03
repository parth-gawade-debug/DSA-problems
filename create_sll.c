#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char name[20];
    int PRN;

    struct node *next;
};

void create_SLL(struct node *head);

int main()
{
    struct node *head;
    head = (struct node*)malloc(sizeof(struct node));
    head->next = NULL;

    create_SLL(head);

    return 0;
}

void create_SLL(struct node *head)
{
    struct node *ptr, *last;
    int n, i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    last = head;

    for(i = 0; i < n; i++)
    {
        ptr = (struct node*)malloc(sizeof(struct node));

        printf("Enter your PRN: ");
        scanf("%d", &ptr->PRN);

        printf("Enter your Name: ");
        scanf("%19s", ptr->name);

        last->next = ptr;
        ptr->next = NULL;
        last = ptr;
    }
}







