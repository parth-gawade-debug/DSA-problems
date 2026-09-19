#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[20][20];
int top = -1;
void push(char op[20])
{
    strcpy(stack[++top], op);
}
char *pop(void)
{
    static char temp[20];
    strcpy(temp, stack[top--]);
    return temp;
}
void postfix_to_infix(char postfix[20]);

int main()
{
    char postfix[20];
    printf("Enter a postfix expression: ");
    scanf("%s", postfix);
    postfix_to_infix(postfix);
    return 0;
}
void postfix_to_infix(char postfix[20])
{
    char op1[20], op2[20];
    for(int i = 0; postfix[i] != '\0'; i++)
    {
        if(postfix[i] == '+' || postfix[i] == '-' ||
           postfix[i] == '*' || postfix[i] == '/' ||
           postfix[i] == '^')
        {
            strcpy(op1, pop());
            strcpy(op2, pop());
            char infix[20];
            infix[0] = '(';
            infix[1] = '\0';
            strcat(infix, op2);

            char temp[20];
            temp[0] = postfix[i];
            temp[1] = '\0';
            strcat(infix, temp);
            strcat(infix, op1);
            temp[0] = ')';
            temp[1] = '\0';
            strcat(infix, temp);
            push(infix);
        }
        else
        {
            char operand[2] = {postfix[i], '\0'};
            push(operand);
        }
    }
    printf("Infix expression: %s", pop());
}