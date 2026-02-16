#include <stdio.h>
#include <string.h>

char stack[50];
int top = -1;

void push(char c){ stack[++top] = c; }
void pop(){ top--; }

int main() {
    char input[50];
    int i = 0;

    printf("Enter expression (use i for id): ");
    scanf("%s", input);
    strcat(input, "$");

    push('$'); push('E');

    while (top != -1) {

        if (stack[top] == input[i]) {
            pop(); i++;
        }

        else if (stack[top] == 'E' && (input[i]=='i' || input[i]=='(')){
            pop(); push('e'); push('T');
        }

        else if (stack[top] == 'e' && input[i]=='+'){
            pop(); push('e'); push('T'); push('+');
        }

        else if (stack[top] == 'e' && (input[i]==')' || input[i]=='$')){
            pop();   // ε
        }

        else if (stack[top] == 'T' && (input[i]=='i' || input[i]=='(')){
            pop(); push('t'); push('F');
        }

        else if (stack[top] == 't' && input[i]=='*'){
            pop(); push('t'); push('F'); push('*');
        }

        else if (stack[top] == 't' && (input[i]=='+' || input[i]==')' || input[i]=='$')){
            pop();   // ε
        }

        else if (stack[top]=='F' && input[i]=='i'){
            pop(); push('i');
        }

        else if (stack[top]=='F' && input[i]=='('){
            pop(); push(')'); push('E'); push('(');
        }

        else{
            printf("Rejected\n");
            return 0;
        }
    }

    if (input[i]=='$')
        printf("Accepted\n");
    else
        printf("Rejected\n");

    return 0;
}