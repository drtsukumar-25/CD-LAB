/*

Consider the syntax of a programming language construct such as while-loop --
while ( condition )
begin
 statement ;
 :
end
where while, begin, end are keywords; condition can be a single comparision expression (such as 
x == 20, etc.); and statement is the assignment to a location the result of a single arithmatic 
operation (eg., a = 10 * b).
Write a program that verifies whether the input follows the above syntax.

sample input

Enter the loop line: while ( x == 20 )
Enter 'begin': begin
Enter statement: a = 10 * b;
Enter 'end': end


*/




#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isIdentifier(char *s) {
    if (!isalpha(s[0])) return 0;
    for (int i = 1; s[i]; i++) {
        if (!isalnum(s[i]) && s[i] != '_')
            return 0;
    }
    return 1;
}

int isNumber(char *s) {
    for (int i = 0; s[i]; i++) {
        if (!isdigit(s[i])) return 0;
    }
    return 1;
}

int isCondition(char *s) {
    char left[50], op[5], right[50];
    if (sscanf(s, " %[^<>=! ] %[<>=!] %s", left, op, right) != 3)
        return 0;

    if (!isIdentifier(left)) return 0;
    if (!(strcmp(op, "==") == 0 || strcmp(op, "!=") == 0 ||
          strcmp(op, "<") == 0 || strcmp(op, "<=") == 0 ||
          strcmp(op, ">") == 0 || strcmp(op, ">=") == 0))
        return 0;
    if (!isIdentifier(right) && !isNumber(right)) return 0;
    return 1;
}

int isStatement(char *s) {
    char left[50], num1[50], num2[50];
    char op;
    int i = 0, j = 0;

    // Skip leading spaces
    while (isspace(s[i])) i++;

    // Get left identifier
    j = 0;
    while (isalnum(s[i]) || s[i] == '_')
        left[j++] = s[i++];
    left[j] = '\0';

    if (!isIdentifier(left)) return 0;

    // Skip spaces
    while (isspace(s[i])) i++;

    if (s[i++] != '=') return 0;

    // Skip spaces
    while (isspace(s[i])) i++;

    // Get first operand (num1)
    j = 0;
    while (isalnum(s[i]))
        num1[j++] = s[i++];
    num1[j] = '\0';
    if (!isIdentifier(num1) && !isNumber(num1)) return 0;

    // Skip spaces
    while (isspace(s[i])) i++;

    // Get operator
    op = s[i++];
    if (!(op == '+' || op == '-' || op == '*' || op == '/'))
        return 0;

    // Skip spaces
    while (isspace(s[i])) i++;

    // Get second operand (num2)
    j = 0;
    while (isalnum(s[i]))
        num2[j++] = s[i++];
    num2[j] = '\0';
    if (!isIdentifier(num2) && !isNumber(num2)) return 0;

    // Skip spaces
    while (isspace(s[i])) i++;

    // Expect semicolon
    if (s[i] != ';') return 0;

    return 1;
}

int main() {
    char line[200], condition[100], statement[100];

    printf("Enter the loop line: ");
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = 0;

    if (strncmp(line, "while", 5) != 0) {
        printf("Syntax Error: Missing 'while' keyword.\n");
        return 0;
    }

    char *p = strchr(line, '(');
    char *q = strchr(line, ')');
    if (!p || !q || p > q) {
        printf("Syntax Error: Missing or misplaced parentheses.\n");
        return 0;
    }

    strncpy(condition, p + 1, q - p - 1);
    condition[q - p - 1] = '\0';

    if (!isCondition(condition)) {
        printf("Syntax Error in condition.\n");
        return 0;
    }

    printf("Enter 'begin': ");
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = 0;
    if (strcmp(line, "begin") != 0) {
        printf("Syntax Error: Missing 'begin'.\n");
        return 0;
    }

    printf("Enter statement: ");
    fgets(statement, sizeof(statement), stdin);
    statement[strcspn(statement, "\n")] = 0;
    if (!isStatement(statement)) {
        printf("Syntax Error in statement.\n");
        return 0;
    }

    printf("Enter 'end': ");
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = 0;
    if (strcmp(line, "end") != 0) {
        printf("Syntax Error: Missing 'end'.\n");
        return 0;
    }

    printf("✅ Syntax is correct!\n");
    return 0;
}
