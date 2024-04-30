%{
    #include<stdio.h>   
%}
%s A B C DEAD


%%
<INITIAL>a BEGIN C;
<INITIAL>b BEGIN A;
<INITIAL>[^ab\n] BEGIN DEAD;
<INITIAL>\n BEGIN INITIAL; {printf("\nNot Accepted\n");}

<A>a BEGIN B;
<A>b BEGIN A;
<A>[^ab\n] BEGIN DEAD;
<A>\n BEGIN INITIAL; {printf("\nNot Accepted\n");}

<C>a BEGIN DEAD; {printf("\nNot Accepted\n");}
<C>b BEGIN DEAD; {printf("\nNot Accepted\n");}
<C>\n BEGIN INITIAL; {printf("\nNot Accepted\n");}

<B>a BEGIN B;
<B>b BEGIN A;
<B>[^ab\n] BEGIN DEAD;
<B>\n BEGIN INITIAL; {printf("\nAccepted\n");}

<DEAD>[^\n] BEGIN DEAD; {printf("INVALID\n");break;}
<DEAD>\n BEGIN INITIAL;  
%%

int main() {
    printf("Enter String: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
