#include <stdio.h>

// Function Declarations
void mat_accept(int mat[20][20], int r, int c);
void mat_display(int mat[20][20], int r, int c);
void mat_transpose(int original[20][20], int transposed[20][20], int r, int c);
void mat_multiply(int mat1[20][20], int mat2[20][20], int result[20][20], int r1, int c1, int c2);
void mat_add(int mat1[20][20], int mat2[20][20], int result[20][20], int r, int c);
void mat_subtract(int mat1[20][20], int mat2[20][20], int result[20][20], int r, int c);

int main()
{
    int mat1[20][20], mat2[20][20], result_mat[20][20];
    int transposed1[20][20], transposed2[20][20];
    int r1, c1, r2, c2;
    int choice;

    // --- Input Matrix 1 ---
    printf("Enter the no. of rows and columns in mat1: ");
    scanf("%d %d", &r1, &c1);
    mat_accept(mat1, r1, c1);
    printf("\nMatrix 1:\n");
    mat_display(mat1, r1, c1);

    // --- Input Matrix 2 ---
    printf("\nEnter the no. of rows and columns in mat2: ");
    scanf("%d %d", &r2, &c2);
    mat_accept(mat2, r2, c2);
    printf("\nMatrix 2:\n");
    mat_display(mat2, r2, c2);

    // --- Menu Driven Interface ---
    printf("\n--- MENU ---");
    printf("\n1 for Transpose");
    printf("\n2 for Multiplication");
    printf("\n3 for Addition");
    printf("\n4 for Subtraction");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            // Transpose operations
            mat_transpose(mat1, transposed1, r1, c1);
            mat_transpose(mat2, transposed2, r2, c2);
           
            printf("\nTransposed Matrix 1 (%dx%d):\n", c1, r1);
            mat_display(transposed1, c1, r1);
           
            printf("\nTransposed Matrix 2 (%dx%d):\n", c2, r2);
            mat_display(transposed2, c2, r2);
            break;

        case 2:
            // Multiplication rule: columns of mat1 == rows of mat2
            if (c1 != r2)
            {
                printf("\nMatrix Multiplication is not possible! (Columns of Matrix 1 must equal Rows of Matrix 2)\n");
            }
            else
            {
                mat_multiply(mat1, mat2, result_mat, r1, c1, c2);
                printf("\nResult of Matrix Multiplication (%dx%d):\n", r1, c2);
                mat_display(result_mat, r1, c2);
            }
            break;

        case 3:
            // Addition rule: dimensions must be identical
            if (r1 != r2 || c1 != c2)
            {
                printf("\nMatrix Addition is not possible! (Dimensions must be identical)\n");
            }
            else
            {
                mat_add(mat1, mat2, result_mat, r1, c1);
                printf("\nResult of Matrix Addition (%dx%d):\n", r1, c1);
                mat_display(result_mat, r1, c1);
            }
            break;

        case 4:
            // Subtraction rule: dimensions must be identical
            if (r1 != r2 || c1 != c2)
            {
                printf("\nMatrix Subtraction is not possible! (Dimensions must be identical)\n");
            }
            else
            {
                mat_subtract(mat1, mat2, result_mat, r1, c1);
                printf("\nResult of Matrix Subtraction (Matrix 1 - Matrix 2) (%dx%d):\n", r1, c1);
                mat_display(result_mat, r1, c1);
            }
            break;

        default:
            printf("\nInvalid choice configuration.\n");
    }

    return 0;
}

// Function Definitions

void mat_accept(int mat[20][20], int r, int c)
{
    int i, j;
    printf("Enter the elements (%dx%d):\n", r, c);
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }
}

void mat_display(int mat[20][20], int r, int c)
{
    int i, j;
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

void mat_transpose(int original[20][20], int transposed[20][20], int r, int c)
{
    int i, j;
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            transposed[j][i] = original[i][j];
        }
    }
}

void mat_multiply(int mat1[20][20], int mat2[20][20], int result[20][20], int r1, int c1, int c2)
{
    int i, j, k;
    for(i = 0; i < r1; i++)
    {
        for(j = 0; j < c2; j++)
        {
            result[i][j] = 0;
            for(k = 0; k < c1; k++)
            {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void mat_add(int mat1[20][20], int mat2[20][20], int result[20][20], int r, int c)
{
    int i, j;
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void mat_subtract(int mat1[20][20], int mat2[20][20], int result[20][20], int r, int c)
{
    int i, j;
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            result[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}