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
int LocalizarRS(rs *RS, char *codigo, int *indice) {
    struct Nodo* p = RS;
    int i = 0;

    while (p != NULL) {
        if (strcmp(p->envio.codigo, codigo) == 0) {
            *indice = i;  // Almacena el índice donde se encontró el valor 'codigo'
            return 1;      // Se encontró el valor 'codigo'
        }
        p = p->siguiente;
        i++;
    }

    return 0;  // El valor 'codigo' no se encontró en la lista vinculada
}







void AltaRS(rs* RS, Envio nuevoEnvio) {
    int indice = Hashing(nuevoEnvio.codigo, MaxEnvios);


    if (LocalizarRS(RS, nuevoEnvio.codigo, indice) == 0) {

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
    return 1;
    }
    else{
        return 0;
    }
}



int BajaRS(rs* RS, Envio envio) {
   int indice = Hashing(envio.codigo, MaxEnvios);
    if (LocalizarRS(RS, envio.codigo, &indice) == 0) {
        struct Nodo* p = RS->celdas[indice];
        struct Nodo* anterior = NULL;
        while (p != NULL) {
            if (strcmp(p->envio.codigo, envio.codigo) == 0) {
                // Se encontró el envío, ahora lo eliminamos del RS
                if (anterior == NULL) {
                    // El envío estaba en la primera posición de la lista
                    RS->celdas[indice] = p->siguiente;
                } else {
                    // El envío estaba en una posición diferente de la lista
                    anterior->siguiente = p->siguiente;
                }

                free(p);  // Liberamos la memoria del nodo
                return 1;  // Baja exitosa
            }
            anterior = p;
            p = p->siguiente;
        }
    }
    return 0;  // El envío no se encontró en la estructura RS
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
