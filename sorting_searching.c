#include <stdio.h>
#include<string.h>


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
void binary_search(struct employee emp1[], int n);
void shell_sort(struct employee emp1[], int n);
int partition(struct employee emp1[], int low, int high);
void quick_sort(struct employee emp1[], int low, int high);
void combine(struct employee emp1[], int low, int mid, int high);
void merge_sort(struct employee emp1[], int low, int high);
void bucket_sort(struct employee emp1[], int n);
void radix_sort(struct employee emp1[], int n);
int main() {
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct employee emp[n];

    accept(emp, n);
    int choice;
    int running = 1;
    
     while (running) {
        printf("\n===== MENU =====\n");
        printf("1. Display Employee Details\n");
        printf("2. Bubble Sort (by Salary)\n");
        printf("3. Selection Sort (by ID)\n");
        printf("4. Insertion Sort (by Increment)\n");
        printf("5. Linear Search (by ID)\n");
        printf("6. Binary Search (by ID)\n");
        printf("7. Shell Sort (by ID)\n");
        printf("8. Quick Sort (by ID)\n");
        printf("9. Merge sort by salary\n");
        printf("10. Bucket Sort (by ID)\n");
        printf("11. Radix Sort (by ID)\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("\n--- Original Employee Details ---\n");
            display(emp, n);
            break;
        case 2:
            bubble_sort(emp, n);
            printf("\n--- Employee Details Sorted by Salary ---\n");
            display(emp, n);
            break;
        case 3:
            selection_sort(emp, n);
            printf("\n--- Employee Details Sorted by ID ---\n");
            display(emp, n);
            break;
        case 4:
            insertion_sort(emp, n);
            printf("\n--- Employee Details Sorted by Increment ---\n");
            display(emp, n);
            break;
        case 5:
            int target;
            printf("Enter employee ID to search: ");
            scanf("%d", &target);
            linear_search(emp, n, target);
            break;
        case 6:
            binary_search(emp, n);
            break;
        case 7:
            shell_sort(emp, n);
            printf("\n--- Employee Details Sorted by Shell Sort (emp_id) ---\n");
            display(emp, n);
            break;
        case 8:
            quick_sort(emp, 0, n - 1);
            printf("\n--- Employee Details Sorted by Quick Sort (emp_id) ---\n");
            display(emp, n);
            break;
        case 9:
            merge_sort(emp, 0, n - 1);
            printf("\n--- Employee Details Sorted by Merge Sort (salary) ---\n");
            display(emp, n);
            break;
        case 10:
            bucket_sort(emp, n);
            printf("\n--- Employee Details Sorted by Bucket Sort (emp_id) ---\n");
            display(emp, n);
            break;
        case 11:
            radix_sort(emp, n);
            printf("\n--- Employee Details Sorted by Radix Sort (emp_id) ---\n");
            display(emp, n);
            break;
        case 12:
            running = 0;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}
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
    for (i = 0; i < n; i++) {
        if (emp1[i].emp_id == target){
            printf("Target Data Found!!\n");
            break;
        }
    }
    if(i>=n){
        printf("Target Data Not Found!!\n");
    }
}
void binary_search(struct employee emp1[], int n) {
    int key, low = 0, high = n - 1, mid;
    printf("Enter the employee id to search: ");
    scanf("%d", &key);

    while (low <= high) {
        mid = (low + high) / 2;
        if (key == emp1[mid].emp_id) {
            printf("Employee id found at index %d\n", mid);
            return;
        } else if (key > emp1[mid].emp_id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    printf("Employee id not found\n");
}
void shell_sort(struct employee emp1[],int n){
    int gap,i,j;
    gap=n/2;
    int swapped;
    struct employee temp;
    do{
        swapped=0;
        do{
            for(i=0;i<n-gap;i++){
                if(emp1[i].emp_id>emp1[i+gap].emp_id){
                    temp=emp1[i];
                    emp1[i]=emp1[i+gap];
                    emp1[i+gap]=temp;
                    swapped=1;
                }
            }

        }
        while(swapped==1);
        gap=gap/2;
        
    }
    while(gap>0);
}
int partition(struct employee emp1[], int low, int high) {
    int pivot = emp1[low].emp_id;
    int i = low ;
    int j = high;
    while(i<j) {
        while(emp1[i].emp_id <= pivot && i < high) {
            i++;
        }
        while(emp1[j].emp_id > pivot && j>=low) {
            j--;
        }
        if(i<j) {
            struct employee temp = emp1[i];
            emp1[i] = emp1[j];
            emp1[j] = temp;
        }
        if(i>j) {
            struct employee temp = emp1[low];
            emp1[low] = emp1[j];
            emp1[j] = temp;
        }
        return j;
    }
}
void quick_sort(struct employee emp1[], int low, int high) {
    if(low < high) {
         int j = partition(emp1, low, high);
        quick_sort(emp1, low, j - 1);
        quick_sort(emp1, j + 1, high);
    }
}
void combine(struct employee emp1[],int low , int mid ,int high){
    int i=low;
    int j=mid+1;
    int temp[20];
    int k;
    while(i<=mid && j<=high){
        if(emp1[i].salary<emp1[j].salary){
            temp[k]=emp1[i].salary;
            i++;
            k++;
        }
        else{
            temp[k]=emp1[j].salary;
            j++;
            k++;
        }
    }
    while(i<=mid){
        temp[k]=emp1[i].salary;
        i++;
        k++;
    }
    while(j<=high){
        temp[k]=emp1[j].salary;
        j++;
        k++;
    }
    for(i=low;i<=high;i++){
        emp1[i].salary=temp[i];
    }
}
void merge_sort(struct employee emp1[], int low, int high) {
    if(low<high){
        int mid=(low+high)/2;
        merge_sort(emp1,low,mid);
        merge_sort(emp1,mid+1,high);
        combine(emp1,low,mid,high);
    }
}
void bucket_sort(struct employee emp1[],int n){
    int bucket[10];
    int k;
    for(int i=0;i<10;i++){
        bucket[i]=0;
    }
    for(int i=0;i<10;i++){
        bucket[emp1[i].emp_id]++;
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<bucket[i];j++){
            printf("%d ",i);
            bucket[k] =i;
            k++;
        }
    }
}
void radix_sort(struct employee emp1[],int n){
    int bucket[10][10];
    int bucket_count[10];
    int max = emp1[0].emp_id;
    for(int i=1;i<n;i++){
        if(emp1[i].emp_id>max){
            max=emp1[i].emp_id;
        }
        while(max>0){
            int digit=max%10;
            bucket[digit][bucket_count[digit]]=emp1[i].emp_id;
            bucket_count[digit]++;
            max/=10;
        }
        int div=1;
        for(int pass =0;pass<bucket_count;pass++){
            for (int i=0;i<10;i++){
                bucket_count[i]=0;
            }
            for(int i=0;i<n;i++){
                int digit=(emp1[i].emp_id/div)%10;
                bucket[digit][bucket_count[digit]]=emp1[i].emp_id;
                bucket_count[digit]++;
            }
            int k=0;
            for(int i=0;i<10;i++){
                for(int j=0;j<bucket_count[i];j++){
                    emp1[k].emp_id=bucket[i][j];
                    k++;
                }
            }
            div *= 10;
        }

    }
}