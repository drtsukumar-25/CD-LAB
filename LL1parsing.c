#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = -1, i = 0, step = 1;

void push(char c){ stack[++top] = c; }
char pop(){ return stack[top--]; }

void printStack(){
    for(int j=0;j<=top;j++)
        printf("%c",stack[j]);
}

int main(){

    printf("Enter string (end with $): ");
    scanf("%s",input);

    push('$');
    push('E');

    printf("\nStep\tStack\tInput\tAction\n");
    printf("---------------------------------------------\n");

    while(top>=0){

        char X = stack[top];
        char a = input[i];

        printf("%d\t",step++);
        printStack();
        printf("\t%s\t",input+i);

        if(X==a){
            pop(); i++;
            printf("match %c\n",a);
        }

        else if(X=='E' && a=='i'){
            pop(); push('e'); push('T');
            printf("E->TE'\n");
        }

        else if(X=='e' && a=='+'){
            pop(); push('e'); push('T'); push('+');
            printf("E'->+TE'\n");
        }

        else if(X=='e' && (a=='$')){
            pop();
            printf("E'->ε\n");
        }

        else if(X=='T' && a=='i'){
            pop(); push('t'); push('F');
            printf("T->FT'\n");
        }

        else if(X=='t' && a=='*'){
            pop(); push('t'); push('F'); push('*');
            printf("T'->*FT'\n");
        }

        else if(X=='t' && (a=='+'||a=='$')){
            pop();
            printf("T'->ε\n");
        }

        else if(X=='F' && a=='i'){
            pop(); push('i');
            printf("F->i\n");
        }

        else{
            printf("Error\n");
            return 0;
        }
    }

    if(input[i]=='\0')
        printf("\n$ accepted\n");
    else
        printf("\nRejected\n");

    return 0;
}
