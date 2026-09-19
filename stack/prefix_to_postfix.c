#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[20][20];
int top = -1;

void push(const char *str)
{
    strcpy(stack[++top], str);
}

char *pop(void)
{
    return stack[top--];
}

void prefixToPostfix(const char prefix[20]);

int main(void)
{
    char prefix[20];
    printf("Enter a prefix expression: ");
    scanf("%s", prefix);
    prefixToPostfix(prefix);
    return 0;
}

void prefixToPostfix(const char prefix[20])
{
char postfix[20], op1[20], op2[20];
int i;
for (i = strlen(prefix) - 1; i >= 0; i--)
{
if(prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/' || prefix[i] == '^')
{
    strcpy(op1, pop());
    strcpy(op2, pop());
    postfix[0]= prefix[i];
    postfix[1]='\0';
    strcat(postfix, op2);
    strcat(postfix, op1);
    push(postfix);
}
else
{
    char operand[2] = { prefix[i], '\0' };
    push(operand);
}
}
printf("Postfix expression: %s\n", pop());
}
