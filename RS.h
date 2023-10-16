#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#define MaxEnvios 300

#include <stdbool.h>
#include "Envios.h"

// Definición de la estructura Nodo
typedef struct Nodo {
    Envio envio;
    struct Nodo* siguiente;
} nodo;
// Define la estructura de la tabla hash
// Definición del tamaño de la tabla hash
// TablaHash.h


typedef struct Rebalse_Separado {
    struct Nodo* celdas[MaxEnvios];
} rs;  // Define un alias "rs" para la estructura TablaHash



void initRS(rs* RS) {
    for (int i = 0; i < MaxEnvios; i++) {
        RS->celdas[i] = NULL;
    }
}


// Función hash


// Función para verificar si un valor 'codigo' pertenece a la tabla hash con rebalse separado
int LocalizarRS(struct Nodo* RS, char *codigo) {
    struct Nodo* p = RS;

    while (p != NULL) {
        if (strcmp(p->envio.codigo, codigo) == 0) {
            return 1; // Se encontró el valor 'codigo'
        }
        p = p->siguiente;
    }

    return 0; // El valor 'codigo' no se encontró en la lista vinculada
}







void AltaRS(rs* RS, Envio nuevoEnvio) {
    int indice = Hashing(nuevoEnvio.codigo, MaxEnvios);

    // Verificar si la lista en esta celda está vacía
    if (RS->celdas[indice] == NULL) {
        // La lista está vacía, creamos un nuevo nodo y lo asignamos como cabeza de la lista
        struct Nodo* nuevoNodo = malloc(sizeof(struct Nodo));
        nuevoNodo->envio = nuevoEnvio;
        nuevoNodo->siguiente = NULL;
        RS->celdas[indice] = nuevoNodo;
    } else {
        // La lista no está vacía, verificamos si el elemento ya existe en la lista
        struct Nodo* p = RS->celdas[indice];
        while (p != NULL) {
            if (strcmp(p->envio.codigo, nuevoEnvio.codigo) == 0) {
                return;  // El elemento ya existe, no se puede dar de alta nuevamente
            }
            p = p->siguiente;
        }
        // El elemento no existe en la lista, creamos un nuevo nodo y lo agregamos al final
        struct Nodo* nuevoNodo = malloc(sizeof(struct Nodo));
        nuevoNodo->envio = nuevoEnvio;
        nuevoNodo->siguiente = NULL;
        p = RS->celdas[indice];
        while (p->siguiente != NULL) {
            p = p->siguiente;
        }
        p->siguiente = nuevoNodo;
    }
}



void MostrarEnviosRS(rs* RS) {
    int contadorEnvios = 0;

    for (int i = 0; i < MaxEnvios; i++) {
        struct Nodo* p = RS->celdas[i];
        printf("Celda %d:\n", i);
        while (p != NULL) {
            mostrarenvio(p->envio);
            contadorEnvios++;

            p = p->siguiente;
        }
    }

    printf("Cantidad de envios: %d\n", contadorEnvios);
}

#endif // RS_H_INCLUDED
