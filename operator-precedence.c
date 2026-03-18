#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

// Stack for operands
int values[MAX];
int vtop = -1;

// Stack for operators
char ops[MAX];
int otop = -1;

// Function to get precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Apply operation
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

// Evaluate expression
int evaluate(char* exp) {
    int i = 0;

    while (exp[i]) {

        // If digit, extract full number
        if (isdigit(exp[i])) {
            int val = 0;
            while (isdigit(exp[i])) {
                val = val * 10 + (exp[i] - '0');
                i++;
            }
            values[++vtop] = val;
            continue;
        }

        // If operator
        else if (exp[i] == '+' || exp[i] == '-' ||
                 exp[i] == '*' || exp[i] == '/') {

            while (otop >= 0 &&
                   precedence(ops[otop]) >= precedence(exp[i])) {

                int b = values[vtop--];
                int a = values[vtop--];
                char op = ops[otop--];

                values[++vtop] = applyOp(a, b, op);
            }

            ops[++otop] = exp[i];
        }

        i++;
    }

    // Final evaluation
    while (otop >= 0) {
        int b = values[vtop--];
        int a = values[vtop--];
        char op = ops[otop--];

        values[++vtop] = applyOp(a, b, op);
    }

    return values[vtop];
}

// Main function
int main() {
    char expr[MAX];

    printf("Enter expression: ");
    scanf("%s", expr);

    int result = evaluate(expr);

    printf("Result = %d\n", result);

    return 0;
}

