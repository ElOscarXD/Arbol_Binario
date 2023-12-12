%{
#include "calc.tab.h"
#include <stdlib.h>
%}

%%

[a-zA-Z] {yylval = *yytext - 'a'; return VARIAVEL;}
[0-9]+\.[0-9]+ {yylval = atof(yytext); return NUMBER;}
[0-9]+   {yylval = atoi(yytext); return NUMBER; }
"/"      {return DIV;}
" "      {return IGUAL;}
"*"      {return VEZES;}
"+"      {return MAIS;}
"-"      {return MENOS;}
"\**"    {return EXP; }
"sqrt"   {return RAIZ;}
"abs"    {return ABS;}
"<<"     {return SHIFTLEFT;}
">>"     {return SHIFTRIGHT;}
"("      {return ABREP;}
")"      {return FECHAP;}
"mod"    {return MOD;}
"="      {return ENTER;}

%%

int yywrap(void) {
    return 1;
}
