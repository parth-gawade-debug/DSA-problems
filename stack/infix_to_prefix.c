#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#define max 100 
 
//create a stack  
char stack[max]; 
 
// i have intialized the top to be -1 
int top=-1;//it just basically index only type thing  
 
 
//lets first check with stact is empty or full  
//lets goo for stack full check  
int isFull(){ 
    //now see for the elements to get at the top it will goo to the max of the stack size -1 
    if(top==max-1) 
        return 1;//true  
    else 
        return 0;//false 
     
} 
 
//now we have to check for stack for empty check 
 
int isEmpty(){ 
    //is empty means my poiinter must be at least box at the bottom  
    if(top==-1) 
        return 1; 
    else 
        return 0; 
 
} 
 
 
//now lets push the things into the stack for that we need a function  
void push(char item){ 
    //i have to store items into the stack  
    //condition over here to check is that stack is not full right  
 
    if (!isFull()){ 
        //if its not empty now what we will doo  
        //add/push the element  
        //first we have to bring index to 0 top to 0 then keep on undating it as we pushing  
        top=top+1; 
        stack[top]=item; 
    } 
} 
 
//now lets create a function for the poping for the stack 
 
char pop(){ 
    //we will pop the item from the top of the stack  
    //condition to be checked here is is full right empty shouldnt be there 
 
    if (!isEmpty()){ 
        char temp=stack[top]; 
        top=top-1; 
        return temp; 
    } 
    return'\0'; 
} 
 
//lets start with icp and isp  
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
 
 
//function we have to type for the infix to prefix expression  
void inpre(char inexp[]){ 
    //just i have to intialize the pointers 
    int k=0; 
    int i=0; 
    char prefix[max]; 
    char finalprefix[max];
    char tkn; 
    char reverse[max]; 
    //now for infix to prefix  
    //some rules where there to follow 
    //rule1: reverse the infix expression  
    reverseString(inexp,reverse); 
    //rule2: swapping the paranthesis  
    swapParentheses(reverse); 
 
    tkn=reverse[i]; 
    while (tkn!='\0'){ 
        if(isalnum(tkn)) 
        { 
            prefix[k]=reverse[i]; 
            k++; 
        } 
        else 
            //now we have to check for any paranthesis  
            if(tkn=='('){ 
                //if yes then we have to push this into the stack  
                push(tkn); 
            } 
         
        else 
            if(tkn==')'){ 
                //if cloasing paranthesis is there then we have to pop until  
                //there is opening parantheiss 
                //we need  a loop to check till opening paranthesis and to poping 
                while((tkn=pop())!='('){ 
                    prefix[k]=tkn; 
                    //prefix will keep on updating by the symbol in the expression  
                    //untill there is the true  
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
 
    // Reverse prefix to get final prefix expression 
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
