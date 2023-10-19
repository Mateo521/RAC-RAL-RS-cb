#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#define MaxEnviosRS 300

#include <stdbool.h>
#include "Envios.h"
typedef struct Nodo {
    Envio envio;
    struct Nodo* siguiente;
} nodo;
typedef struct Rebalse_Separado {
    struct Nodo* celdas[MaxEnviosRS];
} rs;



void initRS(rs* RS) {
    for (int i = 0; i < MaxEnviosRS; i++) {
        RS->celdas[i] = NULL;
    }
}



float CantEvocarExitosoRS = 0.0;
float CantEvocarFracasoRS = 0.0;


float EvocarExitosoMaximoRS= 0.0;
float EvocarFracasoMaximoRS= 0.0;

float temporal_ERS=0.0;
float temporal_FRS=0.0;

int LocalizarRS(rs *RS, char *codigo, int *indice, int ev) {
     float costoEvocarExitoso =0.0;
     float costoEvocarFracaso =0.0;
     float temp = 0.0;
    int i = 0;

    for (i = 0; i < MaxEnviosRS; i++) {

        struct Nodo* p = RS->celdas[i];

        while (p != NULL) {
                 temp++;
            if (strcmp(p->envio.codigo, codigo) == 0) {
                *indice = i;

                  if(ev==1){
                    CantEvocarExitosoRS++;

                    if(EvocarExitosoMaximoRS<temp){
                        EvocarExitosoMaximoRS = temp;
                    }
                    costoEvocarExitoso+=temp;
                     temporal_ERS+=costoEvocarExitoso;
             }
                return 1;      // Se encontro el valor
            } else {
                p = p->siguiente;

            }

        }

    }
  if(ev==1){
                        CantEvocarFracasoRS++;
                         if(EvocarFracasoMaximoRS<temp){
                            EvocarFracasoMaximoRS = temp;
                    }
                costoEvocarFracaso+=temp;
                temporal_FRS+=costoEvocarFracaso;
             }
    return 0;  // El valor  no se encontro en ninguna de las celdas
}









int AltaRS(rs* RS, Envio nuevoEnvio) {
    int indice = Hashing(nuevoEnvio.codigo, MaxEnviosRS);


    if (LocalizarRS(RS, nuevoEnvio.codigo, &indice,0) == 0) {

    if (RS->celdas[indice] == NULL) {

        struct Nodo* nuevoNodo = malloc(sizeof(struct Nodo));
        nuevoNodo->envio = nuevoEnvio;
        nuevoNodo->siguiente = NULL;
        RS->celdas[indice] = nuevoNodo;
    } else {

        struct Nodo* p = RS->celdas[indice];
        while (p != NULL) {
            if (strcmp(p->envio.codigo, nuevoEnvio.codigo) == 0) {
                return 1;
            }
            p = p->siguiente;
        }

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
    int indice = Hashing(envio.codigo, MaxEnviosRS);

   int encontrado = LocalizarRS(RS, envio.codigo, &indice, 0);

    if (encontrado) {
        struct Nodo* p = RS->celdas[indice];
        struct Nodo* anterior = NULL;

        while (p != NULL) {
             if( (strcmp(p->envio.direccion , envio.direccion)==0) && (p->envio.dni_receptor == envio.dni_receptor)
        && (p->envio.dni_remitente == envio.dni_remitente) && (strcmp(p->envio.fecha_envio,envio.fecha_envio)==0)
        && (strcmp(p->envio.fecha_recepcion,envio.fecha_recepcion)==0) && (strcmp(p->envio.nombre,envio.nombre)==0)
        && (strcmp(p->envio.nombre_r,envio.nombre_r)==0)) {

                if (anterior == NULL) {

                    RS->celdas[indice] = p->siguiente;
                } else {

                    anterior->siguiente = p->siguiente;
                }

                free(p);
                return 1;  // Baja exitosa
            }
            anterior = p;
            p = p->siguiente;
        }
    }

    return 0;
}






void MostrarEnviosRS(rs* RS) {
    int contadorEnvios = 0;

    for (int i = 0; i < MaxEnviosRS; i++) {
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


int EvocarRS(rs* RS, char C[], Envio *envio) {
    int indice = Hashing(C, MaxEnviosRS);
    if (LocalizarRS(RS, C, &indice, 1) == 0) {
        struct Nodo* p = RS->celdas[indice];
        while (p != NULL) {
            if (strcmp(p->envio.codigo, C) == 0) {
                (*envio) = p->envio;

                return 1;
            }
            p = p->siguiente;
        }
        return 0;
    }
}



#endif // RS_H_INCLUDED
