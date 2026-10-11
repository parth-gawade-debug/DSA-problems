#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int PRN;
    char name[20];
    struct node *next;
};
void cll_create(struct node **head);
void display(struct node *head);

int main () {
    struct node *head = NULL; 
    cll_create(&head);
    display(head);
    
    return 0;
}
void cll_create(struct node **head) {
    struct node *last = NULL, *ptr;
    char ch;
    
    do {
        ptr = (struct node*)malloc(sizeof(struct node));
        if (ptr == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }
        printf("Enter PRN: ");
        scanf("%d", &ptr->PRN);
        printf("Enter the Name: ");
        scanf("%s", ptr->name);
        if (*head == NULL) {
            *head = ptr;
            ptr->next = *head;
        } else {
            last->next = ptr;
            ptr->next = *head;
        }
        last = ptr;
        printf("Do you want to continue (y/n): ");
        scanf(" %c", &ch); 
    } while(ch == 'y');
}
void display(struct node *head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    struct node *temp = head;
    do {
        printf("[%d , %s] --> ", temp->PRN, temp->name);
        temp = temp->next;
    } while (temp != head);
}

