#include <stdio.h>


struct employee {
    int emp_id;
    char emp_name[20];
    int salary;
    int increment;
};


void accept(struct employee emp1[], int n);
void display(struct employee emp1[], int n);
void bubble_sort(struct employee emp1[], int n); 
void selection_sort(struct employee emp1[], int n);
void insertion_sort(struct employee emp1[], int n);
void linear_search(struct employee emp1[], int n, int target);

int main() {
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct employee emp[n];

    accept(emp, n);
    
    printf("\n--- Original Employee Details ---\n");
    display(emp, n);

    bubble_sort(emp, n);

    printf("\n--- Employee Details Sorted by Salary ---\n");
    display(emp, n); 
    
    selection_sort(emp, n);
    printf("\n--- Employee Details Sorted by id ---\n");
    display(emp,n);

    insertion_sort(emp, n);
    printf("\n--- Employee Details Sorted by increment ---\n");
    display(emp,n);

    linear_search(emp, n,3);
    

    return 0;
}


void accept(struct employee emp1[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Employee %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &emp1[i].emp_id);
        printf("Name: ");
        scanf("%s", emp1[i].emp_name);
        printf("Salary: ");
        scanf("%d", &emp1[i].salary);
        printf("increment: ");
        scanf("%d",&emp1[i].increment);
    }
}


void display(struct employee emp1[], int n) {
    for(int i = 0; i < n; i++) {
        printf("Employee ID: %d | Name: %s | Salary: %d | increment: %d\n", emp1[i].emp_id, emp1[i].emp_name, emp1[i].salary,emp1[i].increment);
    }
} 

void bubble_sort(struct employee emp1[], int n) {
    struct employee temp; 
    int i, j;
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(emp1[j].salary > emp1[j + 1].salary) {
               
                temp = emp1[j];
                emp1[j] = emp1[j + 1];
                emp1[j + 1] = temp;
     }
    }
  }
}
void selection_sort(struct employee emp1[], int n) {
    int i, j, pos;
    struct employee temp;

    for (i = 0; i < n - 1; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (emp1[j].emp_id < emp1[pos].emp_id) {
                pos = j;
            }
        }
        if (i != pos) {
            temp = emp1[i];
            emp1[i] = emp1[pos];
            emp1[pos] = temp;
        }
    }
}
void insertion_sort(struct employee emp1[],int n ) {
    int i,j;
    struct employee key;
    for (i=1;i<n;i++){
        key=emp1[i];
        j=i-1;
        while (j>=0 && emp1[j].increment>key.increment) {
            emp1[j+1]=emp1[j];
            j--;
        }
        emp1[j+1]=key;
    }
}
void linear_search(struct employee emp1[], int n, int target)
{int i;
    for (int i = 0; i < n; i++) {
        if (emp1[i].emp_id == target){
            printf("Target Data Found!!\n");
            break;
        }
    }
    if(i>=n){
        printf("Target Data Not Found!!\n");
    }
}
 