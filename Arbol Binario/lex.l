%{
#include <stdio.h>

int num_a = 0;
int num_x = 0;

%}

%%
^xx { num_x += 2; }
a   { num_a++; }
bb  { if (num_x > 0 && num_a > 0) printf("Cadena válida\n");
      else printf("Cadena inválida\n");
      num_x = 0; num_a = 0; }
.   { printf("Cadena inválida\n"); }
%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}

