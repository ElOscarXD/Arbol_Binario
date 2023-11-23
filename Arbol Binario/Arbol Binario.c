#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

// Definición de la estructura de un nodo del árbol
    struct Nodo {
    int clave;
    struct Nodo *izquierdo;
    struct Nodo *derecho;
};

// Prototipos de funciones
struct Nodo* nuevoNodo(int clave);
struct Nodo* insertar(struct Nodo* raiz, int clave);
void imprimirNodo(struct Nodo* nodo);
void recorridoEnOrden(struct Nodo* raiz);
void recorridoPreOrden(struct Nodo* raiz);
void recorridoPostOrden(struct Nodo* raiz);
struct Nodo* buscar(struct Nodo* raiz, int clave);
bool validarBST(struct Nodo* raiz, int min, int max);
bool insertarConValidacion(struct Nodo** raiz, int clave);
void liberarArbol(struct Nodo* raiz);

int main() {
    struct Nodo* raiz = NULL;
    int opcion, clave, claveBusqueda;

    do {
        system(CLEAR);
        printf("------------------------ BIENVENIDO A LA BUSQUEDA DEL ARBOL BINARIO ------------------------ \n");

        printf("\nOpciones:\n");
        printf("1. Insertar una clave\n");
        printf("2. Mostrar el arbol en inorden\n");
        printf("3. Mostrar el arbol en preorden\n");
        printf("4. Mostrar el arbol en postorden\n");
        printf("5. Buscar una clave\n");
        printf("6. Validar si es un BST\n");
        printf("7. Salir\n");
        printf("Elija una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese la clave a insertar: ");
                scanf("%d", &clave);
                if (!insertarConValidacion(&raiz, clave)) {
                    printf("Insercion incorrecta. El Arbol ya no es un BST.\n");
                    liberarArbol(raiz);
                    return 1;
                }
                break;
            case 2:
                printf("Arbol en inorden:\n");
                recorridoEnOrden(raiz);
                printf("\n");
                getchar();
                break;
            case 3:
                printf("Arbol en preorden:\n");
                recorridoPreOrden(raiz);
                printf("\n");
                getchar();
                break;
            case 4:
                printf("Arbol en postorden:\n");
                recorridoPostOrden(raiz);
                printf("\n");
                getchar();
                break;
            case 5:
                printf("Ingrese la clave a buscar: ");
                scanf("%d", &claveBusqueda);
                struct Nodo* resultadoBusqueda = buscar(raiz, claveBusqueda);
                if (resultadoBusqueda != NULL) {
                    printf("Se encontro la clave %d\n", claveBusqueda);
                } else {
                    printf("La clave %d no se encontro en el arbol.\n", claveBusqueda);
                }
                getchar();
                break;
            case 6:
                if (!validarBST(raiz, INT_MIN, INT_MAX)) {
                    printf("El Arbol no es un BST.\n");
                    liberarArbol(raiz);
                    return 1;
                }
                printf("El Arbol es un BST.\n");
                printf("Presione Enter para continuar...");
                getchar();
                break;
            case 7:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                getchar();
        }
        getchar();
    } while (opcion != 7);

    // Liberar la memoria asignada para el árbol antes de salir del programa
    liberarArbol(raiz);

    return 0;
}

// Implementación de funciones

struct Nodo* nuevoNodo(int clave) {
    struct Nodo* nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nodo == NULL) {
        perror("Error al asignar memoria para el nodo");
        exit(EXIT_FAILURE);
    }
    nodo->clave = clave;
    nodo->izquierdo = nodo->derecho = NULL;
    return nodo;
}

struct Nodo* insertar(struct Nodo* raiz, int clave) {
    if (raiz == NULL) {
        return nuevoNodo(clave);
    }

    if (clave < raiz->clave) {
        raiz->izquierdo = insertar(raiz->izquierdo, clave);
    } else if (clave > raiz->clave) {
        raiz->derecho = insertar(raiz->derecho, clave);
    }

    return raiz;
}

bool insertarConValidacion(struct Nodo** raiz, int clave) {
    if (*raiz == NULL) {
        *raiz = nuevoNodo(clave);
        return true;
    }

    if (clave < (*raiz)->clave) {
        if (!insertarConValidacion(&(*raiz)->izquierdo, clave)) {
            return false;
        }
    } else if (clave > (*raiz)->clave) {
        if (!insertarConValidacion(&(*raiz)->derecho, clave)) {
            return false;
        }
    } else {
        // Clave duplicada, no se permite en un BST
        return false;
    }

    return true;
}

void imprimirNodo(struct Nodo* nodo) {
    printf("Clave: %d\n", nodo->clave);
    if (nodo->izquierdo != NULL) {
        printf("   Hijo izquierdo: %d\n", nodo->izquierdo->clave);
    }
    if (nodo->derecho != NULL) {
        printf("   Hijo derecho: %d\n", nodo->derecho->clave);
    }
}

void recorridoEnOrden(struct Nodo* raiz) {
    if (raiz != NULL) {
        recorridoEnOrden(raiz->izquierdo);
        imprimirNodo(raiz);
        recorridoEnOrden(raiz->derecho);
    }
}

void recorridoPreOrden(struct Nodo* raiz) {
    if (raiz != NULL) {
        imprimirNodo(raiz);
        recorridoPreOrden(raiz->izquierdo);
        recorridoPreOrden(raiz->derecho);
    }
}

void recorridoPostOrden(struct Nodo* raiz) {
    if (raiz != NULL) {
        recorridoPostOrden(raiz->izquierdo);
        recorridoPostOrden(raiz->derecho);
        imprimirNodo(raiz);
    }
}

struct Nodo* buscar(struct Nodo* raiz, int clave) {
    if (raiz == NULL || raiz->clave == clave) {
        return raiz;
    }

    if (clave < raiz->clave) {
        return buscar(raiz->izquierdo, clave);
    } else {
        return buscar(raiz->derecho, clave);
    }
}

bool validarBST(struct Nodo* raiz, int min, int max) {
    if (raiz == NULL) {
        return true;
    }

    if (raiz->clave <= min || raiz->clave >= max) {
        return false;
    }

    return validarBST(raiz->izquierdo, min, raiz->clave) && validarBST(raiz->derecho, raiz->clave, max);
}

void liberarArbol(struct Nodo* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izquierdo);
        liberarArbol(raiz->derecho);
        free(raiz);
    }
}



