#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stack[20];
int top = -1;

void push(int ele) {
    stack[++top] = ele;
}

int pop(void) {
    return stack[top--];
}

void exp_eval(char postfix[20]) {
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
            int op1 = pop();
            int op2 = pop();
            int result;
            
            if (postfix[i] == '+') {
                result = op2 + op1;
            } else if (postfix[i] == '-') {
                result = op2 - op1;
            } else if (postfix[i] == '*') {
                result = op2 * op1;
            } else {
                result = op2 / op1;
            }
            push(result);
        } else {
            int op = postfix[i] - '0'; 
            push(op);
        }
    }
    printf("result = %d\n", pop());
}

int main() {
    char postfix[20];
    printf("Enter the postfix expression: ");
    scanf("%s", postfix); 
    exp_eval(postfix);
    return 0;
}