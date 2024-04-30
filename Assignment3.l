%{
    #include<stdio.h>   
%}
%s B DEAD


%%
<INITIAL>a BEGIN INITIAL;
<INITIAL>b BEGIN B;
<INITIAL>[^ab\n] BEGIN DEAD;
<INITIAL>\n BEGIN INITIAL; {printf("\nNot Accepted\n");}

<B>a BEGIN B;
<B>b BEGIN INITIAL;
<B>[^ab\n] BEGIN DEAD;
<B>\n BEGIN INITIAL; {printf("\nAccepted\n");}

<DEAD>[^\n] BEGIN DEAD;
<DEAD>\n BEGIN INITIAL; {printf("INVALID\n");} 
%%

int main() {
    printf("Enter String: ");
    yylex();  
    return 0;
}

int yywrap() {
    return 1;
}
