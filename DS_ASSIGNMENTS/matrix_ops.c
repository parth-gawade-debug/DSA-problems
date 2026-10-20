/*
 * Assignment 1 · Matrix operations (add, subtract, multiply, transpose)
 *
 * Lab assignment 1. Read two matrices A and B, then carry out commands:
 * A (add), S (subtract), M (multiply), TA / TB (transpose A or B),
 * reporting when the orders do not allow an operation.
 */
#include <stdio.h>

#define MAX 10

void read_matrix(int m[][MAX], int r, int c)
{
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) scanf("%d", &m[i][j]);
}

/* given: one row per line, numbers separated by a single space */
void print_matrix(int m[][MAX], int r, int c)
{
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) printf(j ? " %d" : "%d", m[i][j]);
        printf("\n");
    }
}

/* res = a + b (sign = +1) or a - b (sign = -1). Return 0 if the orders differ (and do nothing), else 1. */
int add_or_subtract(int a[][MAX], int ra, int ca, int b[][MAX], int rb, int cb, int sign, int res[][MAX])
{
    if (ra != rb || ca != cb) {
        return 0;
    }

    for (int i = 0; i < ra; i++) {
        for (int j = 0; j < ca; j++) {
            res[i][j] = a[i][j] + sign * b[i][j];
        }
    }
    return 1;
}

/* res = a x b. Return 0 if the columns of a != the rows of b (and do nothing), else 1. Result is ra x cb. */
int multiply(int a[][MAX], int ra, int ca, int b[][MAX], int rb, int cb, int res[][MAX])
{
    if (ca != rb) {
        return 0;
    }

    for (int i = 0; i < ra; i++) {
        for (int j = 0; j < cb; j++) {
            res[i][j] = 0;
            for (int k = 0; k < ca; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return 1;
}

/* t = transpose of the r x c matrix m (t is c x r). */
void transpose(int m[][MAX], int r, int c, int t[][MAX])
{
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            t[j][i] = m[i][j];
        }
    }
}

/* ---------------------------------------------------------------- do not change below */
int main(void)
{
    int ra, ca, rb, cb, a[MAX][MAX], b[MAX][MAX], res[MAX][MAX];
    char cmd[8];
    if (scanf("%d %d", &ra, &ca) != 2) return 0;
    read_matrix(a, ra, ca);
    scanf("%d %d", &rb, &cb);
    read_matrix(b, rb, cb);
    while (scanf("%7s", cmd) == 1) {
        if (cmd[0] == 'A' || cmd[0] == 'S') {
            int plus = cmd[0] == 'A';
            if (add_or_subtract(a, ra, ca, b, rb, cb, plus ? 1 : -1, res)) {
                printf("A %c B:\n", plus ? '+' : '-');
                print_matrix(res, ra, ca);
            } else {
                printf("Cannot %s: A is %d x %d, B is %d x %d\n", plus ? "add" : "subtract", ra, ca, rb, cb);
            }
        } else if (cmd[0] == 'M') {
            if (multiply(a, ra, ca, b, rb, cb, res)) {
                printf("A x B (%d x %d):\n", ra, cb);
                print_matrix(res, ra, cb);
            } else {
                printf("Cannot multiply: columns of A (%d) != rows of B (%d)\n", ca, rb);
            }
        } else if (cmd[0] == 'T') {
            int which_b = cmd[1] == 'B';
            transpose(which_b ? b : a, which_b ? rb : ra, which_b ? cb : ca, res);
            printf("Transpose of %c (%d x %d):\n", which_b ? 'B' : 'A', which_b ? cb : ca, which_b ? rb : ra);
            print_matrix(res, which_b ? cb : ca, which_b ? rb : ra);
        }
    }
    return 0;
}
