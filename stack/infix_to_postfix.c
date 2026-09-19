#include <stdio.h>
#include <stdlib.h>

char stack[20];
int top = -1;

void push(char ch)
{
top++;
stack[top] = ch;
}

char pop()
{
char t;

t = stack[top];
top--;

return t;
}

int precedence(char op)
{
if (op == '(')
return 0;
if (op == '+' || op == '-')
return 1;
if (op == '*' || op == '/')
return 2;
if (op == '^')
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
while (top != -1 && precedence(stack[top]) >= precedence(infix[i]))
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
