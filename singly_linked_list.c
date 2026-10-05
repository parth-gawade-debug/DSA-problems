#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    int PRN;
    char name[20];
    struct node *next;
};
void create_SLL(struct node *head);
void display(struct node *head);
void add_in_btw_position(struct node * head);
void del_any_position(struct node * head);
int count_students(struct node *head);
void reverse(struct node *head);
int main()
{
    struct node *head;
    head = (struct node *)malloc(sizeof(struct node));
    head -> next = NULL;
    create_SLL(head);
    display(head);
    printf("\nNumber of students = %d\n", count_students(head));
    add_in_btw_position(head);
    display(head);
    printf("\nNumber of students = %d\n", count_students(head));
    del_any_position(head);
    display(head);
    printf("\nNumber of students = %d\n", count_students(head));
    reverse(head);
    display(head);

}
void create_SLL(struct node *head)
{
    struct node *ptr, *last;
    last = head; char ch;
    do
    {
        ptr = (struct node *)malloc(sizeof(struct node));
        printf("Enter PRN :\n");
        scanf("%d", &ptr -> PRN);
        printf("Enter the Name \n");
        scanf("%s", ptr -> name);
        last -> next = ptr;
        ptr -> next = NULL;
        last = ptr;
        printf("Do you want to continue y/n \n");
        scanf(" %c", &ch);
    }
    while(ch== 'y');
}
void display(struct node *head)
{
struct node *temp;
temp =head -> next;
while(temp != NULL)
{
printf(" [%d ,    ", temp -> PRN);
printf("%s]  -->   ", temp -> name);
temp = temp -> next;
}
printf(" -> NULL\n");
}

void add_in_btw_position(struct node * head)
{
struct node * ptr, *temp;
int pos;
ptr=(struct node*)malloc(sizeof(struct node));
printf("Enter PRN :\n");
scanf("%d", &ptr -> PRN);
printf("Enter Name :\n");
scanf("%s", ptr->name);
printf("Enter position where to add new node :\n");
scanf("%d",&pos);
int count=1;
temp=head;
while(temp != NULL && count != pos)
{
temp = temp-> next;
count ++;
}
ptr -> next = temp -> next;
temp -> next = ptr;
}
void del_any_position(struct node * head)
{
struct node * temp, *prev;
int pos;
int count=1;
printf("Enter position of node to be deleted\n");
scanf("%d", &pos);
temp= head->next;
prev=head;
while (temp != NULL)
{
if(pos == count)
{
prev -> next = temp -> next;
temp -> next = NULL;
free(temp);
break;
}
else {
prev = temp;
temp=temp -> next;
count ++;
}
}
}
int count_students(struct node *head)
{
    struct node *temp;
    int count = 0;
    temp = head->next;
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}
void reverse(struct node *head)
{
    struct node *p, *q, *r;
    p=NULL;
    q=head->next;
    while(q != NULL)
    {
        r=q->next;
        q->next=p;
        p=q;
        q=r;
    }
    head->next=p;
}

