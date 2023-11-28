%%
^[a-zA-Z0-9._%+-]+@(gmail\.com|hotmail\.com|xyz\.[a-zA-Z]+\.mx)$   { printf("El correo electronico es valido.\n"); }
. { printf("El correo electronico NO es valido.\n"); yyterminate();}
%%
