#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#define max 100 
 

char stack[max]; 
 

int top=-1; 
 
 

int isFull(){ 
    
    if(top==max-1) 
        return 1;
    else 
        return 0; 
     
} 
 

 
int isEmpty(){ 
    
    if(top==-1) 
        return 1; 
    else 
        return 0; 
 
} 
 
 
 
void push(char item){ 
  
 
    if (!isFull()){ 
      
        top=top+1; 
        stack[top]=item; 
    } 
} 
 

char pop(){ 
  
 
    if (!isEmpty()){ 
        char temp=stack[top]; 
        top=top-1; 
        return temp; 
    } 
    return'\0'; 
} 
 

int icp (char ch) 
{ 
    if(ch=='+' || ch=='-') 
    return 1; 
    if(ch=='*' || ch=='/') 
    return 2; 
    if(ch=='^') 
    return 3; 
    if(ch=='(') 
    return 5; 
    else 
    return 0; 
} 
 
int isp(char ch) 
{ 
 if(ch=='+' || ch=='-') 
 return 1; 
 if(ch=='*' || ch=='/') 
 return 2; 
 if(ch=='^') 
 return 4; 
 else 
 return 0; 
} 

void reverseString(char str[], char rev[]);
void swapParentheses(char str[]);
 
 
 
void inpre(char inexp[]){ 
    
    int k=0; 
    int i=0; 
    char prefix[max]; 
    char finalprefix[max];
    char tkn; 
    char reverse[max]; 
   
    reverseString(inexp,reverse); 
   
    swapParentheses(reverse); 
 
    tkn=reverse[i]; 
    while (tkn!='\0'){ 
        if(isalnum(tkn)) 
        { 
            prefix[k]=reverse[i]; 
            k++; 
        } 
        else 
           
            if(tkn=='('){ 
               
                push(tkn); 
            } 
         
        else 
            if(tkn==')'){ 
            
                while((tkn=pop())!='('){ 
                    prefix[k]=tkn; 
                  
                    k++; 
                     
                } 
            } 
 
 
         
        else{ 
            while(!isEmpty() && isp(stack[top])>icp(tkn)){ 
                prefix[k]=pop(); 
                k++; 
             
            } 
            push(tkn); 
        } 
        i++; 
        tkn=reverse[i]; 
    } 
 
     while (!isEmpty()) 
    { 
        prefix[k] = pop(); 
        k++; 
    } 
 
    prefix[k] = '\0'; 
 

    reverseString(prefix, finalprefix); 
 
    printf("Prefix expression = %s", finalprefix); 
} 
 
int main(){ 
    char inexp[max]; 
    printf("enter the string:"); 
    scanf("%s",inexp); 
    inpre(inexp); 
    
    return 0;
} 
 
void reverseString(char str[], char rev[]) 
{ 
    int i = 0; 
    int j = 0; 
 
    while (str[i] != '\0') 
    { 
        i++; 
    } 
 
    i--; 
 
    while (i >= 0) 
    { 
        rev[j] = str[i]; 
        j++; 
        i--; 
    } 
 
    rev[j] = '\0'; 
} 
 
void swapParentheses(char str[]) 
{ 
    int i = 0; 
 
    while (str[i] != '\0') 
    { 
        if (str[i] == '(') 
        { 
            str[i] = ')'; 
        } 
        else if (str[i] == ')') 
        { 
            str[i] = '('; 
        } 
 
        i++; 
    } 
}
