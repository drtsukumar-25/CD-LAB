#include<stdio.h>
#include<string.h>

char stack[100], input[100];
int top=-1, i=0;

void push(char c){ stack[++top]=c; }
char pop(){ return stack[top--]; }

int main(){
    printf("Enter input: ");
    scanf("%s", input);
    strcat(input,"$");

    push('$');
    push('E');

    while(top>=0){
        char X = stack[top];
        char a = input[i];

        /* Accept condition */
        if(X=='$' && a=='$'){
            printf("Accepted\n");
            return 0;
        }

        /* Terminal match for single char */
        if(X==a){
            pop();
            i++;
        }

        /* Match id (two characters) */
        else if(X=='F' && input[i]=='i' && input[i+1]=='d'){
            pop();
            i+=2;
        }

        /* E → T E'  (E' represented as A) */
        else if(X=='E'){
            pop();
            push('A');
            push('T');
        }

        /* E' → + T E' | ε */
        else if(X=='A'){
            pop();
            if(a=='+'){
                push('A');
                push('T');
                push('+');
            }
            else if(a==')' || a=='$'){
                /* epsilon */
            }
            else{
                printf("Rejected\n");
                return 0;
            }
        }

        /* T → F T'  (T' represented as B) */
        else if(X=='T'){
            pop();
            push('B');
            push('F');
        }

        /* T' → * F T' | ε */
        else if(X=='B'){
            pop();
            if(a=='*'){
                push('B');
                push('F');
                push('*');
            }
            else if(a=='+' || a==')' || a=='$'){
                /* epsilon */
            }
            else{
                printf("Rejected\n");
                return 0;
            }
        }

        /* F → (E) */
        else if(X=='F' && a=='('){
            pop();
            push(')');
            push('E');
            push('(');
        }

        else{
            printf("Rejected\n");
            return 0;
        }
    }

    printf("Rejected\n");
    return 0;
}