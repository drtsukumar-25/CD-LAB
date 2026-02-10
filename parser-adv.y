%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token INT ID SEMI

%%
program:
      program statement
    | statement
    ;

statement:
      INT ID SEMI
        { printf("Valid declaration\n"); }
    | INT ID
        { printf("Error: Missing semicolon\n"); }
    | ID INT SEMI
        { printf("Error: Wrong variable declaration (identifier before keyword)\n"); }
    | INT SEMI ID
        { printf("Error: Incorrect ordering of keyword, identifier, and semicolon\n"); }
    | INT INT SEMI
        { printf("Error: Reserved keyword 'int' cannot be used as variable name\n"); }
    ;
%%

void yyerror(const char *s)
{
    printf("Syntax Error\n");
}

int main()
{
    printf("Enter declarations:\n");
    yyparse();
    return 0;
}