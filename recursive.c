#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char input[100]; int i=0;

void E(); void E1(); void T(); void T1(); void F();

void E(){ T(); E1(); }
void E1(){ if(input[i]=='+'){ i++; T(); E1(); } }
void T(){ F(); T1(); }
void T1(){ if(input[i]=='*'){ i++; F(); T1(); } }
void F(){
    if(input[i]=='('){ i++; E(); if(input[i]==')') i++; }
    else if(input[i]=='i'){ i++; }
    else{ printf("Rejected\n"); exit(0); }
}

int main(){
    printf("Enter string: ");
    scanf("%s",input);
    E();
    if(input[i]=='\0') printf("Accepted\n");
    else printf("Rejected\n");
    return 0;
}