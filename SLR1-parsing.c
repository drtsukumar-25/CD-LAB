#include<stdio.h>
#include<string.h>

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

int main(){
    int stack[100], top=0;
    char input[100];
    int i=0;

    printf("Enter input: ");
    scanf("%s",input);
    strcat(input,"$");

    stack[0]=0;

    while(1){
        int state = stack[top];
        int col;

        if(input[i]=='i') col=0;
        else if(input[i]=='+') col=1;
        else if(input[i]=='*') col=2;
        else if(input[i]=='(') col=3;
        else if(input[i]==')') col=4;
        else if(input[i]=='$') col=5;
        else { printf("Rejected\n"); return 0; }

        int act = action[state][col];

        if(act==999){
            printf("Accepted\n");
            return 0;
        }

        if(act>0){   // SHIFT
            stack[++top] = act;
            i++;
        }
        else if(act<0){  // REDUCE
            int r = -act;

            int pop_count;
            if(r==1) pop_count=3;   // E→E+T
            else if(r==2) pop_count=1; // E→T
            else if(r==3) pop_count=3; // T→T*F
            else if(r==4) pop_count=1; // T→F
            else if(r==5) pop_count=3; // F→(E)
            else if(r==6) pop_count=1; // F→i
            else { printf("Rejected\n"); return 0; }

            if(top-pop_count<0){
                printf("Rejected\n");
                return 0;
            }

            top -= pop_count;
            state = stack[top];

            int nt;
            if(r==1||r==2) nt=0; // E
            else if(r==3||r==4) nt=1; // T
            else nt=2; // F

            stack[++top] = go[state][nt];
        }
        else{
            printf("Rejected\n");
            return 0;
        }
    }
}