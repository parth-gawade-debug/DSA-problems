#include <stdio.h>

void mat_display(int mat[20][20], int r, int c);
void mat_accept(int mat[20][20], int r, int c);
void compact_gen(int mat1[20][20], int r, int c, int CP[20][20]);
void simple_transpose(int CP[20][20], int TP[20][20]);

int main()
{
    int mat1[20][20];
    int r1, c1;
    int CP[20][20];
    int TP[20][20];

    printf("Enter the no. of rows and columns in mat1: ");
    scanf("%d %d", &r1, &c1);

    mat_accept(mat1, r1, c1);

    printf("\nMatrix 1:\n");
    mat_display(mat1, r1, c1);
    
    compact_gen(mat1, r1, c1, CP);
    
    printf("\nCompact Matrix: \n");
    mat_display(CP, (CP[0][2] + 1), 3);
    
    simple_transpose(CP, TP);
    
    printf("\nTransposed Compact Matrix:\n");
    mat_display(TP, (TP[0][2] + 1), 3);

    return 0;
}

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

void compact_gen(int mat1[20][20], int r, int c, int CP[20][20])
{
    int k = 1;
    int i, j;    
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            if(mat1[i][j] != 0)
            {
                CP[k][0] = i;
                CP[k][1] = j;
                CP[k][2] = mat1[i][j]; 
                k++;
            }
        }
    }
    CP[0][0] = r;
    CP[0][1] = c;
    CP[0][2] = k - 1;
}

void simple_transpose(int CP[20][20], int TP[20][20])
{
    int k = 1;

    // Set row count, col count, non-zero element count for TP
    TP[0][0] = CP[0][1];
    TP[0][1] = CP[0][0];
    TP[0][2] = CP[0][2];

    // Scan column by column to keep row indices sorted in output
    for(int i = 0; i < CP[0][1]; i++)
    {
        for(int j = 1; j <= CP[0][2]; j++)
        {
            if(CP[j][1] == i)
            {
                TP[k][0] = CP[j][1]; // transposed row = original col
                TP[k][1] = CP[j][0]; // transposed col = original row
                TP[k][2] = CP[j][2]; // value stays same
                k++;
            }
        }
    }
}
