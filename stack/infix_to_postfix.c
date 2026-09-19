#include <stdio.h>
#include <stdlib.h>

char stack[20];
int top = -1;
int isempty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}
int isfull()
{
    if (top == 19)
        return 1;
    else
        return 0;
}
void push(char ch)
{
    if (isfull() == 0)
    {
        top++;
        stack[top] = ch;
    }
    else
    {
        printf("Stack is full");
    }
}
char pop()
{
    if (isempty() == 0)
    {
        char t;
        t = stack[top];
        top--;
        return t;
    }
    else
    {
        printf("Stack is empty");
        return -1;
    }
}
int precedence(char op)
{
    if (op == '(')
        return 0;
    else if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '^')
        return 3;
    return -1;
}
void infixToPostfix(char infix[20])
{
    char post[20], ch;
    int k = 0;
    for (int i = 0; infix[i] != '\0'; i++)
    {
        if (infix[i] == '(')
        {
            push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while ((ch = pop()) != '(')
            {
                post[k++] = ch;
            }
        }
        else if (infix[i] == '+' || infix[i] == '-' ||
                 infix[i] == '*' || infix[i] == '/' || infix[i] == '^')
        {
            while (top != -1 &&
                   precedence(stack[top]) >= precedence(infix[i]))
            {
                post[k++] = pop();
            }
            push(infix[i]);
        }
        else
        {
            post[k++] = infix[i];
        }
    }
    while (top != -1)
    {
        post[k++] = pop();
    }
    post[k] = '\0';
    printf("Postfix: %s\n", post);
}
int main()
{
    char infix[20];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix);
    return 0;
}
