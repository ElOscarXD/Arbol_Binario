%option noyywrap
%%

\/\/[^\n]*            { /* Comentario de una linea */ }
\/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/ { /* Comentario de bloque */ }
.                    { ECHO; }
%%

