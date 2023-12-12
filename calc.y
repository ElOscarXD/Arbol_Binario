%{
#include <stdio.h>
#include <math.h>

void yyerror(const char *s);

extern double yylval;
extern FILE *yyin;

int vet[26];
int i = 0;
double data[100];

void getresult(double value) {
    data[i] = value;
    i++;
}

%}

%left MAIS MENOS
%left VEZES DIV
%left UMENOS
%left EXP
%left MOD
%left SHIFTLEFT SHIFTRIGHT
%left ABS RAIZ

%token NUMBER VARIAVEL
%token ABREP FECHAP MAIS MENOS VEZES DIV IGUAL ENTER EXP RAIZ UMENOS ABS SHIFTLEFT SHIFTRIGHT MOD

%define api.value.type { double }

%%

program:
  program statement ENTER
  | /* NULL */
  ;

statement:
  expression  { getresult($1); }
 | VARIAVEL IGUAL expression { vet[(int)$1] = $3; }
 ;

expression:
  expression MAIS expression { $$ = $1 + $3; }
 | expression MENOS expression { $$ = $1 - $3; }
 | term
 ;

term:
  term VEZES term { $$ = $1 * $3; }
 | term DIV term { $$ = $1 / $3; }
 | factor
 ;

factor:
  NUMBER { $$ = $1; }
 | VARIAVEL { $$ = vet[(int)$1]; }
 | MENOS factor %prec UMENOS { $$ = -$2; }
 | ABREP expression FECHAP { $$ = $2; }
 | factor EXP factor { $$ = pow($1, $3); }
 | RAIZ factor %prec UMENOS { $$ = sqrt($2); }
 | ABS factor %prec UMENOS { $$ = fabs($2); }
 | factor SHIFTLEFT factor { $$ = (int)$1 << (int)$3; } 
 | factor SHIFTRIGHT factor { $$ = (int)$1 >> (int)$3; } 
 | factor MOD factor { $$ = fmod($1, $3); }
 ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "%s\n", s);
}

int main(int argc, char *argv[]) {
  FILE *file = fopen("texto.txt", "r");
  if (!file) {
    perror("Error al abrir el archivo");
    return 1;
  }

  yyin = file;
  yyparse();
  fclose(file);

 
  i = 0;
  file = fopen("texto.txt", "r");
  char line[500];
  while (fgets(line, sizeof(line), file)) {
    printf("%s%.6f\n", line, data[i]); // Ajustado el formato de impresión
    i++;
  }
  fclose(file);

  return 0;
}
