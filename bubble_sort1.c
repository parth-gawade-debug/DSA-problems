#include <stdio.h>

void bubble_sort(int arr[20], int n);

int main()
{
    int arr[20], n, i;

    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20) {
        printf("Invalid input. Please enter a number between 1 and 20.\n");
        return 1;
    }

    printf("Enter the elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    bubble_sort(arr, n);

    printf("Sorted array:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void bubble_sort(int arr[20], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
  