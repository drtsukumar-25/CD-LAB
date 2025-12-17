%option noyywrap

%{
#include <stdio.h>
%}

%%
int|float|double|char|if|else|for|while|return|void|break|continue   { printf("Reserved Word: %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*                                               { printf("Identifier: %s\n", yytext); }

[ \t\n]+   ;
.          ;
%%

int main(void)
{
    yylex();
    return 0;
}
