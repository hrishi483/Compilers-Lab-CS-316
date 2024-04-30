%{
    #include<stdio.h>   
%}
%s B C D E DEAD


%%
<INITIAL>a BEGIN INITIAL;
<INITIAL>b BEGIN B;
<INITIAL>[^ab\n] BEGIN DEAD;
<INITIAL>\n BEGIN INITIAL; {printf("\nNot Accepted\n");}

<B>a BEGIN C;
<B>b BEGIN B;
<B>[^ab\n] BEGIN DEAD;
<B>\n BEGIN INITIAL; {printf("\nNot Accepted\n");}

<C>a BEGIN INITIAL; 
<C>b BEGIN D; 
<C>[^ab\n] BEGIN DEAD;
<C>\n BEGIN INITIAL; {printf("\nNot Accepted\n");}

<D>a BEGIN E;
<D>b BEGIN B;
<D>[^ab\n] BEGIN DEAD;
<D>\n BEGIN INITIAL; {printf("\nNot Accepted\n");}

<E>a BEGIN E;
<E>b BEGIN E;
<E>[^ab\n] BEGIN DEAD;
<E>\n BEGIN INITIAL; {printf("\nAccepted\n");}

<DEAD>[^\n] BEGIN DEAD; {printf("INVALID\n");}
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
