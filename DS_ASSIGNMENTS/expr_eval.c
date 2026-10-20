/*
 * Assignment: Infix to Postfix with the Stack at Each Step, and Evaluation (Unit IV)
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];       /* the operator stack: stack[0] is the bottom */
int top = -1;
char postfix[MAX];     /* the postfix expression being built */
int k = 0;             /* number of characters in postfix so far */

/* ---------------- provided - do not modify ---------------- */
void print_step(char sym)
{
    printf("%c ", sym);
    if (top == -1) printf("-");
    for (int i = 0; i <= top; i++) printf("%c", stack[i]);
    postfix[k] = '\0';
    printf(" %s\n", k ? postfix : "-");
}

/* ---------------- your part ---------------- */
int icp(char c)
{
    if (c == '(') return 5;
    if (c == '^') return 4;
    if (c == '*' || c == '/' || c == '%') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int isp(char c)
{
    if (c == '^') return 3;
    if (c == '*' || c == '/' || c == '%') return 2;
    if (c == '+' || c == '-') return 1;
    if (c == '(') return 0;
    return 0;
}

void push(char c)
{
    if (top < MAX - 1) {
        stack[++top] = c;
    }
}

char pop(void)
{
    if (top >= 0) {
        return stack[top--];
    }
    return '\0';
}

/* Convert the infix string in[] into postfix[] (and k), calling print_step
   after each symbol. Terminate postfix[] with '\0'. */
void infix_to_postfix(const char *in)
{
    top = -1;
    k = 0;
    postfix[0] = '\0';

    for (int i = 0; in[i] != '\0'; i++) {
        char c = in[i];

        // Skip whitespace
        if (c == ' ' || c == '\t') continue;

        if (isdigit((unsigned char)c)) {
            postfix[k++] = c;
            postfix[k] = '\0';
            print_step(c);
        } else if (c == '(') {
            push(c);
            print_step(c);
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                postfix[k++] = pop();
            }
            if (top >= 0 && stack[top] == '(') {
                pop(); // Discard '('
            }
            postfix[k] = '\0';
            print_step(c);
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^') {
            while (top >= 0 && isp(stack[top]) >= icp(c)) {
                postfix[k++] = pop();
            }
            push(c);
            postfix[k] = '\0';
            print_step(c);
        }
    }

    // Pop remaining operators from the stack
    while (top >= 0) {
        postfix[k++] = pop();
    }
    postfix[k] = '\0';
}

/* Helper function for exponentiation */
static int power(int base, int exp)
{
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

/* Evaluate the postfix string p and return its value. */
int eval_postfix(const char *p)
{
    int estack[MAX];
    int etop = -1;

    for (int i = 0; p[i] != '\0'; i++) {
        char c = p[i];

        if (isdigit((unsigned char)c)) {
            estack[++etop] = c - '0';
        } else {
            int op2 = estack[etop--];
            int op1 = estack[etop--];
            int res = 0;

            switch (c) {
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/': res = op1 / op2; break;
                case '%': res = op1 % op2; break;
                case '^': res = power(op1, op2); break;
                default: break;
            }
            estack[++etop] = res;
        }
    }

    return estack[etop];
}

/* ---------------- provided - do not modify ---------------- */
int main(void)
{
    char in[MAX];
    if (!fgets(in, sizeof in, stdin)) return 1;
    in[strcspn(in, "\r\n")] = '\0';
    printf("SYMBOL STACK POSTFIX\n");
    infix_to_postfix(in);
    printf("POSTFIX: %s\n", postfix);
    printf("VALUE: %d\n", eval_postfix(postfix));
    return 0;
}
