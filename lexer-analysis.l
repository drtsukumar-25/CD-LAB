%{
#include "parser-adv.tab.h"
%}

%%
"int"        { return INT; }
";"          { return SEMI; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }
[ \t\n]+     ;   /* ignore whitespace */
.            ;   /* ignore other characters */
%%

int yywrap(void)
{
    return 1;
}