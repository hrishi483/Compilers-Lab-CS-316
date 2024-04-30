%{
#include <stdio.h>
int words = 0, special_chars = 0, spaces = 0, tabs = 0, lines = 0;
%}

%%
[a-zA-Z]+   { words = words + 1; }   /* Rule to match one or more alphabetic characters, counting words */
[ \t]       { spaces = spaces + 1; } /* Rule to match spaces and tabs, counting spaces */
[!@#$%^&*]  { special_chars = special_chars + 1; } /* Rule to match specific special characters, counting special characters */
[\n]          { lines = lines + 1; }    /* Rule to match newline characters, counting lines */
.           ;                          /* Rule to match any other character (not explicitly handled) */
%%

int main() {
    printf("Enter the Paragraph: ");
    yylex();
    printf("Number of words = %d\n", words);
    printf("Number of special characters = %d\n", special_chars);
    printf("Number of spaces = %d\n", spaces);
    printf("Number of tabs = %d\n", tabs);
    printf("Number of lines = %d\n", lines);
    return 0;
}

int yywrap() {
    return 1;
}
