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

void postfixToPrefix(const char postfix[20]);

int main(void)
{
    char postfix[20];
    printf("Enter a postfix expression: ");
    scanf("%s", postfix);
    postfixToPrefix(postfix);
    return 0;
}

void postfixToPrefix(const char postfix[20])
{
char prefix[20], op1[20], op2[20];
int i;
for (i = 0; postfix[i] != '\0'; i++)
{
if(postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^')
{
    strcpy(op1, pop());
    strcpy(op2, pop());
    prefix[0]= postfix[i];
    prefix[1]='\0';
    strcat(prefix, op2);
    strcat(prefix, op1);
    push(prefix);
}
else
{
    char operand[2] = { postfix[i], '\0' };
    push(operand);
}
}
printf("Prefix expression: %s\n", pop());
}
