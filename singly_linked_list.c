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
void sort_sll(struct node *head);
void merge_sll(struct node *head1,struct node *head2);
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
    sort_sll(head);
    display(head);
    merge_sll(head,head);
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
printf(" [%d  %s]  -->   ", temp -> PRN, temp -> name);

temp = temp -> next;
}
printf("NULL\n");
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
void sort_sll(struct node *head){
    
    int n=count_students(head);
    struct node *temp1, *curr, *prev;
    for(int i=0;i<n-1;i++) {
        prev=head;
        curr=head->next;
        for(int j=0;j<n-i-1;j++) {
            temp1=curr->next;
            if(curr->PRN > temp1->PRN) {
                curr->next=temp1->next;
                prev->next=temp1;
                temp1->next=curr;
                prev=curr;
                curr=curr->next;
        }
        else{
            prev=curr;
            curr=temp1;
        }
    }
}
}
void merge_sll(struct node *head1,struct node *head2){
    struct node *head3, *curr;
    struct node *temp1,*temp2, *temp3;
    head3=(struct node*)malloc(sizeof(struct node));
    if(head1->next->PRN <head2->next->PRN){
        head3=head1;}
        else{
            head3=head2;
    }
    temp1=head1->next;
    temp2=head2->next;
    temp3=head3;
    while(temp1!=NULL && temp2!=NULL){
        if(temp1->PRN <temp2->PRN){
            curr =(struct node*)malloc(sizeof(struct node));
            curr->PRN=temp1->PRN;
            temp2=temp1->next;
            temp3->next=curr;
            curr->next=NULL;
        }
        else{
            
            curr =(struct node*)malloc(sizeof(struct node));
            curr->PRN=temp2->PRN;
            temp2=temp2->next;
            temp3->next=curr;
            curr->next=NULL;
            temp3=temp3->next;
        }
    }
    while(temp1!=NULL){
        curr =(struct node*)malloc(sizeof(struct node));
        curr->PRN=temp1->PRN;
        temp1=temp1->next;
        temp3->next=curr;
        curr->next=NULL;
        temp3=temp3->next;
        
        
    }
}