/*
 * Assignment 6 · Expression conversions with a stack ADT
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEPTH 64
#define LEN 256

/* given (the notes' table): in-coming and in-stack priorities */
int icp(char c)
{
    return c == '(' ? 5 : c == '^' ? 4 : (c == '*' || c == '/' || c == '%') ? 2 : (c == '+' || c == '-') ? 1 : 0;
}

int isp(char c)
{
    return c == '^' ? 3 : (c == '*' || c == '/' || c == '%') ? 2 : (c == '+' || c == '-') ? 1 : 0;
}

int is_operand(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

/* the notes' priorities for infix -> prefix: pop while isp_pre(top) > icp_pre(c) */
int icp_pre(char c)
{
    return c == '(' ? 5 : c == '^' ? 3 : (c == '*' || c == '/' || c == '%') ? 2 : (c == '+' || c == '-') ? 1 : 0;
}

int isp_pre(char c)
{
    return c == '^' ? 4 : (c == '*' || c == '/' || c == '%') ? 2 : (c == '+' || c == '-') ? 1 : 0;
}

/* Helper to reverse a string in place */
static void str_reverse(char *str)
{
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
}

/* infix -> postfix: pop while isp(top) >= icp(c). */
void infix_to_postfix(const char *in, char *out)
{
    char stack[DEPTH];
    int top = -1;
    int k = 0;

    for (int i = 0; in[i] != '\0'; i++) {
        char c = in[i];
        if (is_operand(c)) {
            out[k++] = c;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                out[k++] = stack[top--];
            }
            if (top >= 0 && stack[top] == '(') {
                top--; // Discard '('
            }
        } else { // Operator
            while (top >= 0 && isp(stack[top]) >= icp(c)) {
                out[k++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    while (top >= 0) {
        if (stack[top] != '(' && stack[top] != ')') {
            out[k++] = stack[top];
        }
        top--;
    }
    out[k] = '\0';
}

/* infix -> prefix (the notes' method): reverse in, swapping '(' and ')'; convert with
   pop while isp_pre(top) > icp_pre(c); reverse the result. */
void infix_to_prefix(const char *in, char *out)
{
    int len = strlen(in);
    char rev[LEN];
    char stack[DEPTH];
    char temp[LEN];
    int top = -1;
    int k = 0;

    // 1. Reverse input and swap brackets
    for (int i = 0; i < len; i++) {
        char ch = in[len - 1 - i];
        if (ch == '(') rev[i] = ')';
        else if (ch == ')') rev[i] = '(';
        else rev[i] = ch;
    }
    rev[len] = '\0';

    // 2. Convert using pre priorities
    for (int i = 0; rev[i] != '\0'; i++) {
        char c = rev[i];
        if (is_operand(c)) {
            temp[k++] = c;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                temp[k++] = stack[top--];
            }
            if (top >= 0 && stack[top] == '(') {
                top--;
            }
        } else { // Operator
            while (top >= 0 && isp_pre(stack[top]) > icp_pre(c)) {
                temp[k++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    while (top >= 0) {
        if (stack[top] != '(' && stack[top] != ')') {
            temp[k++] = stack[top];
        }
        top--;
    }
    temp[k] = '\0';

    // 3. Reverse output
    str_reverse(temp);
    strcpy(out, temp);
}

/* postfix -> infix: op2 = pop, op1 = pop, push "(op1 c op2)". */
void postfix_to_infix(const char *in, char *out)
{
    char stack[DEPTH][LEN];
    int top = -1;

    for (int i = 0; in[i] != '\0'; i++) {
        char c = in[i];
        if (is_operand(c)) {
            char str[2] = {c, '\0'};
            strcpy(stack[++top], str);
        } else {
            char op2[LEN], op1[LEN], expr[LEN];
            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);

            snprintf(expr, sizeof(expr), "(%s%c%s)", op1, c, op2);
            strcpy(stack[++top], expr);
        }
    }

    if (top >= 0) {
        strcpy(out, stack[top]);
    } else {
        out[0] = '\0';
    }
}

/* postfix -> prefix: op2 = pop, op1 = pop, push "c op1 op2". */
void postfix_to_prefix(const char *in, char *out)
{
    char stack[DEPTH][LEN];
    int top = -1;

    for (int i = 0; in[i] != '\0'; i++) {
        char c = in[i];
        if (is_operand(c)) {
            char str[2] = {c, '\0'};
            strcpy(stack[++top], str);
        } else {
            char op2[LEN], op1[LEN], expr[LEN];
            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);

            snprintf(expr, sizeof(expr), "%c%s%s", c, op1, op2);
            strcpy(stack[++top], expr);
        }
    }

    if (top >= 0) {
        strcpy(out, stack[top]);
    } else {
        out[0] = '\0';
    }
}

/* prefix -> infix: scan right to left; op1 = pop, op2 = pop, push "(op1 c op2)". */
void prefix_to_infix(const char *in, char *out)
{
    char stack[DEPTH][LEN];
    int top = -1;
    int len = strlen(in);

    for (int i = len - 1; i >= 0; i--) {
        char c = in[i];
        if (is_operand(c)) {
            char str[2] = {c, '\0'};
            strcpy(stack[++top], str);
        } else {
            char op1[LEN], op2[LEN], expr[LEN];
            strcpy(op1, stack[top--]);
            strcpy(op2, stack[top--]);

            snprintf(expr, sizeof(expr), "(%s%c%s)", op1, c, op2);
            strcpy(stack[++top], expr);
        }
    }

    if (top >= 0) {
        strcpy(out, stack[top]);
    } else {
        out[0] = '\0';
    }
}

/* prefix -> postfix: scan right to left; op1 = pop, op2 = pop, push "op1 op2 c". */
void prefix_to_postfix(const char *in, char *out)
{
    char stack[DEPTH][LEN];
    int top = -1;
    int len = strlen(in);

    for (int i = len - 1; i >= 0; i--) {
        char c = in[i];
        if (is_operand(c)) {
            char str[2] = {c, '\0'};
            strcpy(stack[++top], str);
        } else {
            char op1[LEN], op2[LEN], expr[LEN];
            strcpy(op1, stack[top--]);
            strcpy(op2, stack[top--]);

            snprintf(expr, sizeof(expr), "%s%s%c", op1, op2, c);
            strcpy(stack[++top], expr);
        }
    }

    if (top >= 0) {
        strcpy(out, stack[top]);
    } else {
        out[0] = '\0';
    }
}

/* ---------------------------------------------------------------- do not change below */
int main(void)
{
    char cmd[16], e[LEN], out[LEN];
    while (scanf("%15s %255s", cmd, e) == 2) {
        out[0] = '\0';
        if (strcmp(cmd, "IN-POST") == 0) infix_to_postfix(e, out);
        else if (strcmp(cmd, "IN-PRE") == 0) infix_to_prefix(e, out);
        else if (strcmp(cmd, "POST-IN") == 0) postfix_to_infix(e, out);
        else if (strcmp(cmd, "POST-PRE") == 0) postfix_to_prefix(e, out);
        else if (strcmp(cmd, "PRE-IN") == 0) prefix_to_infix(e, out);
        else if (strcmp(cmd, "PRE-POST") == 0) prefix_to_postfix(e, out);
        else continue;
        printf("%s %s = %s\n", cmd, e, out);
    }
    return 0;
}
