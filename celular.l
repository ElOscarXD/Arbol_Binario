%{
#include <stdio.h>
%}

%%
^[0-9]{10}$  { printf("Número de celular válido\n"); }
[^0-9\n]     { printf("Número de celular no válido: contiene caracteres no numéricos\n"); }
.            ; // Ignorar otros caracteres
%%

int main() {
    yylex();
    return 0;
}

