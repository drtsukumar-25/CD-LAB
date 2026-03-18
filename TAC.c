#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[20];
int top=-1;

void push(char x){
    stack[++top]=x;
}

char pop(){
    return stack[top--];
} \

int priority(char x){
    if(x=='+' || x=='-') return 1;
    if(x=='*' || x=='/') return 2;
    return 0;
}

int main(){
    char infix[50], postfix[50];
    char st[20][10];
    int i=0,j=0,t=1,top2=-1;

    printf("Enter Expression: ");
    scanf("%s",infix);

    char lhs=infix[0];
    char exp[50];
    strcpy(exp,&infix[2]);
 
    while(exp[i]){
        if(isalpha(exp[i]))
            postfix[j++]=exp[i];
        else{
            while(top!=-1 && priority(stack[top])>=priority(exp[i]))
                postfix[j++]=pop();
            push(exp[i]);
        }
        i++;
    }

    while(top!=-1)
        postfix[j++]=pop();

    postfix[j]='\0';

    printf("\nThree Address Code:\n");

    for(i=0;i<j;i++){
        if(isalpha(postfix[i])){
            st[++top2][0]=postfix[i];
            st[top2][1]='\0';
        }
        else{
            char op2[10],op1[10];
            strcpy(op2,st[top2--]);
            strcpy(op1,st[top2--]);

            printf("t%d = %s %c %s\n",t,op1,postfix[i],op2);
            sprintf(st[++top2],"t%d",t++);
        }
    }

    printf("%c = %s\n",lhs,st[top2]);

    return 0;
}