/*
 * Assignment: Sparse Matrix in Triplet Form: Fast Transpose and Addition (Unit II)
 *
 * Complete every function marked TODO. Do NOT change main(), the print and
 * read functions, or the input/output format - your program is graded automatically.
 */
#include <stdio.h>

#define MAXR 20
#define MAXC 20
#define MAXT (MAXR * MAXC + 1)

/* Convert the m x n matrix a into triplet (compact) form b:
 * b[0] = {m, n, t}, then b[1..t] = {row, col, value} in row-major order.
 * Return t, the number of non-zero elements. */
int compact(int a[][MAXC], int m, int n, int b[][3])
{
    int k = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                b[k][0] = i;
                b[k][1] = j;
                b[k][2] = a[i][j];
                k++;
            }
        }
    }
    b[0][0] = m;
    b[0][1] = n;
    b[0][2] = k - 1;
    return k - 1;
}

/* FAST transpose of the triplet matrix a into b.
 * Fill s[0..n-1] (non-zeros per column of a) and t[0..n-1] (starting
 * position of each row of b). Leave t[] holding the STARTING positions:
 * use a separate copy if you need to move positions forward while placing.
 * b[0] must be {n, m, t}. */
void fast_transpose(int a[][3], int b[][3], int s[], int t[])
{
    int num_cols = a[0][1];
    int num_terms = a[0][2];

    b[0][0] = a[0][1];
    b[0][1] = a[0][0];
    b[0][2] = a[0][2];

    /* Count non-zero elements per column in matrix A */
    for (int i = 0; i < num_cols; i++) {
        s[i] = 0;
    }
    for (int i = 1; i <= num_terms; i++) {
        s[a[i][1]]++;
    }

    /* Compute starting positions for each row in the transposed matrix */
    t[0] = 1;
    for (int i = 1; i < num_cols; i++) {
        t[i] = t[i - 1] + s[i - 1];
    }

    /* Working array for element placement */
    int pos[MAXC];
    for (int i = 0; i < num_cols; i++) {
        pos[i] = t[i];
    }

    /* Place elements into transposed triplet matrix b */
    for (int i = 1; i <= num_terms; i++) {
        int col = a[i][1];
        int j = pos[col]++;
        b[j][0] = a[i][1];
        b[j][1] = a[i][0];
        b[j][2] = a[i][2];
    }
}

/* c = a + b, all three in triplet form (a and b have the same size).
 * Walk both lists in row-major order: same position -> add (store only if
 * the sum is not 0) and advance both; otherwise copy the one that comes
 * first. Set c[0] = {rows, cols, number of triples stored}. Return that number. */
int sparse_add(int a[][3], int b[][3], int c[][3])
{
    int i = 1, j = 1, k = 1;
    int t1 = a[0][2];
    int t2 = b[0][2];

    c[0][0] = a[0][0];
    c[0][1] = a[0][1];

    while (i <= t1 && j <= t2) {
        if (a[i][0] < b[j][0] || (a[i][0] == b[j][0] && a[i][1] < b[j][1])) {
            c[k][0] = a[i][0];
            c[k][1] = a[i][1];
            c[k][2] = a[i][2];
            i++;
            k++;
        } else if (b[j][0] < a[i][0] || (a[i][0] == b[j][0] && b[j][1] < a[i][1])) {
            c[k][0] = b[j][0];
            c[k][1] = b[j][1];
            c[k][2] = b[j][2];
            j++;
            k++;
        } else {
            int sum_val = a[i][2] + b[j][2];
            if (sum_val != 0) {
                c[k][0] = a[i][0];
                c[k][1] = a[i][1];
                c[k][2] = sum_val;
                k++;
            }
            i++;
            j++;
        }
    }

    /* Copy remaining elements from a */
    while (i <= t1) {
        c[k][0] = a[i][0];
        c[k][1] = a[i][1];
        c[k][2] = a[i][2];
        i++;
        k++;
    }

    /* Copy remaining elements from b */
    while (j <= t2) {
        c[k][0] = b[j][0];
        c[k][1] = b[j][1];
        c[k][2] = b[j][2];
        j++;
        k++;
    }

    c[0][2] = k - 1;
    return k - 1;
}

/* ---------------- provided - do not modify ---------------- */
void print_triplets(const char *name, int b[][3])
{
    printf("%s = %d %d %d\n", name, b[0][0], b[0][1], b[0][2]);
    for (int k = 1; k <= b[0][2]; k++)
        printf("%d %d %d\n", b[k][0], b[k][1], b[k][2]);
}

void print_array(const char *name, int x[], int n)
{
    printf("%s =", name);
    for (int i = 0; i < n; i++)
        printf(" %d", x[i]);
    printf("\n");
}

void read_matrix(int a[][MAXC], int m, int n)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (scanf("%d", &a[i][j]) != 1)
                a[i][j] = 0;
}

int main(void)
{
    static int A[MAXR][MAXC], B[MAXR][MAXC];
    static int ta[MAXT][3], tb[MAXT][3], tr[MAXT][3], sum[2 * MAXT][3];
    int S[MAXC], T[MAXC], m, n;

    if (scanf("%d %d", &m, &n) != 2 || m < 1 || n < 1 || m > MAXR || n > MAXC)
        return 1;
    read_matrix(A, m, n);
    read_matrix(B, m, n);

    compact(A, m, n, ta);
    compact(B, m, n, tb);
    fast_transpose(ta, tr, S, T);
    sparse_add(ta, tb, sum);

    print_triplets("A", ta);
    print_triplets("B", tb);
    print_array("S", S, n);
    print_array("T", T, n);
    print_triplets("TRANSPOSE", tr);
    print_triplets("SUM", sum);
    return 0;
}
