#include <stdio.h>
#include <string.h>

int action[12][6]={
{5,0,0,4,0,0},{0,6,0,0,0,999},{0,-2,7,0,-2,-2},
{0,-4,-4,0,-4,-4},{5,0,0,4,0,0},{0,-6,-6,0,-6,-6},
{5,0,0,4,0,0},{5,0,0,4,0,0},{0,6,0,0,11,0},
{0,-1,7,0,-1,-1},{0,-3,-3,0,-3,-3},{0,-5,-5,0,-5,-5}
};

int go[12][3]={
{1,2,3},{0,0,0},{0,0,0},{0,0,0},
{8,2,3},{0,0,0},{0,9,3},{0,0,10},
{0,0,0},{0,0,0},{0,0,0},{0,0,0}
};

char *prod[]={"","E->E+T","E->T","T->T*F","T->F","F->(E)","F->i"};

int main(){
    int st[100],top=0,i=0,col,act,r;
    char ip[100],stackStr[100];

    printf("Enter input: ");
    scanf("%s",ip);
    if(ip[strlen(ip)-1]!='$') strcat(ip,"$");

    st[0]=0;

    printf("\n%-18s %-15s %s\n","Stack","Input","Action");
    printf("------------------------------------------------\n");

    while(1){
        col=(ip[i]=='i')?0:(ip[i]=='+')?1:(ip[i]=='*')?2:
            (ip[i]=='(')?3:(ip[i]==')')?4:5;

        act=action[st[top]][col];

        stackStr[0]='\0';
        for(int k=0;k<=top;k++){
            char t[5]; sprintf(t,"%d",st[k]); strcat(stackStr,t);
        }

        printf("%-18s %-15s ",stackStr,ip+i);

        if(act==999){ printf("Accept\n"); break; }

        if(act>0){ printf("S%d\n",act); st[++top]=act; i++; }

        else if(act<0){
            r=-act; printf("R%d: %s\n",r,prod[r]);
            top-=(r==1||r==3||r==5)?3:1;
            st[++top]=go[st[top]][(r<=2)?0:(r<=4)?1:2];
        }
        else{ printf("Rejected\n"); break; }
    }
    return 0;
}
