#include <stdio.h>
#include <string.h>

#define MAXS 100

struct student {
    int roll;
    char name[30];
    int marks;
};

void read_students(struct student s[], int n)
{
    for (int i = 0; i < n; i++) scanf("%d %29s %d", &s[i].roll, s[i].name, &s[i].marks);
}

/* given: one student per line: roll name marks */
void print_students(struct student s[], int n)
{
    for (int i = 0; i < n; i++) printf("%d %s %d\n", s[i].roll, s[i].name, s[i].marks);
}

/* Index of the first student called name, or -1; comparisons (strcmp calls) in *cmp. */
int linear_search(struct student s[], int n, const char *name, int *cmp)
{
    *cmp = 0;
    for (int i = 0; i < n; i++) {
        (*cmp)++;
        if (strcmp(s[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

/* 1 if s is in ascending order of roll number, else 0. */
int sorted_by_roll(struct student s[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        if (s[i].roll > s[i + 1].roll) {
            return 0;
        }
    }
    return 1;
}

/* Binary search by roll (s sorted by roll); loop iterations in *cmp. mid = (low + high) / 2. */
int binary_search(struct student s[], int n, int roll, int *cmp)
{
    *cmp = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        (*cmp)++;
        int mid = (low + high) / 2;
        if (s[mid].roll == roll) {
            return mid;
        } else if (s[mid].roll < roll) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

/* Insertion sort by roll number, ascending. */
void insertion_sort_roll(struct student s[], int n)
{
    for (int i = 1; i < n; i++) {
        struct student key = s[i];
        int j = i - 1;
        while (j >= 0 && s[j].roll > key.roll) {
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = key;
    }
}

/* Selection sort by marks, highest first (the FIRST highest when equal; always swap into place). */
void selection_sort_marks(struct student s[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (s[j].marks > s[max_idx].marks) {
                max_idx = j;
            }
        }
        struct student temp = s[i];
        s[i] = s[max_idx];
        s[max_idx] = temp;
    }
}

/* Shell sort by name, ascending; gaps n/2, n/4, …, 1. */
void shell_sort_name(struct student s[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            struct student temp = s[i];
            int j = i;
            while (j >= gap && strcmp(s[j - gap].name, temp.name) > 0) {
                s[j] = s[j - gap];
                j -= gap;
            }
            s[j] = temp;
        }
    }
}

/* ---------------------------------------------------------------- do not change below */
int main(void)
{
    int n, cmp, roll;
    char cmd[4], name[30];
    struct student s[MAXS];
    if (scanf("%d", &n) != 1) return 0;
    read_students(s, n);
    while (scanf("%3s", cmd) == 1) {
        if (cmd[0] == 'P') {
            printf("Students:\n");
            print_students(s, n);
        } else if (cmd[0] == 'L' && scanf("%29s", name) == 1) {
            int i = linear_search(s, n, name, &cmp);
            if (i >= 0) printf("Linear search %s: found roll %d, marks %d (%d comparisons)\n", name, s[i].roll, s[i].marks, cmp);
            else printf("Linear search %s: not found (%d comparisons)\n", name, cmp);
        } else if (cmd[0] == 'B' && scanf("%d", &roll) == 1) {
            if (!sorted_by_roll(s, n)) {
                printf("Binary search %d: the list is not sorted by roll number (use I first)\n", roll);
                continue;
            }
            int i = binary_search(s, n, roll, &cmp);
            if (i >= 0) printf("Binary search %d: found %s at index %d (%d comparisons)\n", roll, s[i].name, i, cmp);
            else printf("Binary search %d: not found (%d comparisons)\n", roll, cmp);
        } else if (cmd[0] == 'I') {
            insertion_sort_roll(s, n);
            printf("Sorted by roll number (insertion sort):\n");
            print_students(s, n);
        } else if (cmd[0] == 'S') {
            selection_sort_marks(s, n);
            printf("Sorted by marks, highest first (selection sort):\n");
            print_students(s, n);
        } else if (cmd[0] == 'H') {
            shell_sort_name(s, n);
            printf("Sorted by name (Shell sort):\n");
            print_students(s, n);
        }
    }
    return 0;
}
