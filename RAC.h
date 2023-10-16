#ifndef RAC_H
#define RAC_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MaxEnvios 300

typedef struct {
    Envio envio;
    int Flag; // 0 VIRGEN 1 LIBRE 2 OCUPADA
} rac;

void initRAC(rac *RAC) {

    for (int i = 0; i < MaxEnvios; i++) {

        RAC[i].Flag = 0; // Inicializar el campo Flag a 0

        // Inicializar los campos de la estructura Envio dentro de la estructura rac
       strcpy(RAC[i].envio.codigo, "");
strcpy(RAC[i].envio.direccion, "");
strcpy(RAC[i].envio.fecha_envio, "");
strcpy(RAC[i].envio.fecha_recepcion, "");
strcpy(RAC[i].envio.nombre, "");
strcpy(RAC[i].envio.nombre_r, "");
        RAC[i].envio.dni_receptor = 0; // Inicializar dni_receptor a 0
        RAC[i].envio.dni_remitente = 0; // Inicializar dni_remitente a 0

    }

}


///---------------------------------------------------------LOCALIZAR
rloc LocalizarRAC(rac *RAC, char C[], int *pos, int p)
{
    int H = Hashing(C, MaxEnvios);
    int i = 0,j=1;
    rloc aux;

    while (i < MaxEnvios) {
        if (RAC[H].Flag == 2 && strcmp(RAC[H].envio.codigo, C) == 0) {
            aux.exito = 1;
            aux.lugar = H;
            return aux;  // Encontramos el envío, marcamos éxito y su posición
        }
        else if (RAC[H].Flag == 0) {
            aux.exito = 0;
            aux.lugar = H;  // Encontramos una posición vacía, marcamos no éxito y su posición
            return aux;
        }
        H = (H + j * j) % MaxEnvios;  // Rebalse cuadrático abierto: Avanzamos cuadráticamente
        i++;
        j++;
    }

    aux.exito = 0;
    aux.lugar = -1;  // No se encontró el envío, marcamos no éxito y posición -1
    return aux;
}


/*
rloc LocalizarRAC(rac *RAC, char C[], int *pos, int p, int *FlagAlta) {
    int H = Hashing(C, MaxEnvios);
    int i = 0;
    int primerbaldelibre = -1;
    int controldeprimerbaldelibre = 0;
    int j = 1; // Inicializar j en 1 (se incrementará cuadráticamente)
    rloc aux;

    while (i < MaxEnvios && RAC[H].Flag != 0 && (strcmp(RAC[H].envio.codigo, C) != 0)) {
        if (controldeprimerbaldelibre == 0 && RAC[H].Flag == 1) {
            primerbaldelibre = H;
            controldeprimerbaldelibre = 1;
        }
        H = (H + j * j) % MaxEnvios; // Incremento cuadrático
        i++;
        j++;
    }

    if (RAC[H].Flag == 0) {
        if (controldeprimerbaldelibre == 1) {
            H = primerbaldelibre;
        }
        aux.exito = false;
    } else {
        if (i == MaxEnvios) {
            aux.exito = false;
            if (controldeprimerbaldelibre == 1) {
                H = primerbaldelibre;
            }
            // No modifiques *FlagAlta aquí, ya que el código no se encontró.
        } else if (strcmp(RAC[H].envio.codigo, C) == 0) {
            aux.exito = true;
        }
    }

    aux.lugar = H;

    // Si el código se encontró o si se cambió FlagAlta en la última parte, modifica *FlagAlta.
    if (aux.exito || controldeprimerbaldelibre == 1) {
        *FlagAlta = 1;
    }

    return aux;
}
*/


///---------------------------------------------------------ALTA
int AltaRAC(rac *RAC, Envio envio) {
    int pos;

    rloc aux = LocalizarRAC(RAC, envio.codigo, &pos, 0); // Sin el &

    if (aux.exito) {
        return 0; // Elemento ya existe o no se puede agregar
    } else {
        // Si la función LocalizarRAC encontró un lugar disponible, puedes insertar el elemento C
        RAC[aux.lugar].envio = envio;
        RAC[aux.lugar].Flag = 2; // Marcar el casillero como OCUPADO
        // Actualiza cualquier otro contador o información que necesites
        return 1; // Elemento agregado con éxito
    }
}


///---------------------------------------------------------BAJA
int BajaRAC(rac *RAC, Envio envio)
{
    int pos;
    rloc aux = LocalizarRAC(RAC, envio.codigo, &pos, 0);

    if (aux.exito == 1) {

         if ((strcmp(RAC[aux.lugar].envio.codigo, envio.codigo)==0) && (strcmp(RAC[aux.lugar].envio.direccion, envio.direccion)==0) && (RAC[aux.lugar].envio.dni_receptor == envio.dni_receptor) &&
             (RAC[aux.lugar].envio.dni_remitente == envio.dni_remitente)&& (strcmp(RAC[aux.lugar].envio.fecha_envio, envio.fecha_envio)==0) && (strcmp(RAC[aux.lugar].envio.fecha_recepcion, envio.fecha_recepcion)==0)
             && (strcmp(RAC[aux.lugar].envio.nombre, envio.nombre)==0) && (strcmp(RAC[aux.lugar].envio.nombre_r, envio.nombre_r)==0)
             ){



       RAC[aux.lugar].Flag = 1; // Marcar el casillero como LIBRE
        // Realiza cualquier otra operación necesaria, como liberar memoria si es aplicable
 return 1; // Baja exitosa
      }



    } else {
        return 0; // Baja no exitosa
    }
}

///---------------------------------------------------------EVOCAR
int EvocarRAC(rac *RAC,char C[], Envio *envio){
    int pos;
    rloc aux = LocalizarRAC(RAC, C, &pos, 0);
    if(aux.exito){
         (*envio)=RAC[aux.lugar].envio;
        return 1;///ARTICULO ENCONTRADO
    }else
        return 0;///ARTICULO NO ENCONTRADO
}
///---------------------------------------------------------MOSTRAR ESTRUCTURA
void MostrarEnviosRAC(rac RAC[]) {
    int i,contador=0;
    for (i = 0; i < MaxEnvios; i++) {
        switch (RAC[i].Flag) {
            case 0:
                printf("\t\t POSICION [ %i ] VIRGEN\n", i);
                break;
            case 1:
                printf("\t\t POSICION [ %i ] LIBRE\n", i);
                break;
            case 2:
                printf("\t\t POSICION [ %i ] OCUPADA\n", i);
                contador ++;
                mostrarenvio(RAC[i].envio); // Llama a la función para mostrar un envío
                break;
        }
    }
    printf("total de envios : %d\n", contador);
    system("pause");
}


// Contenido de rac.h

#endif
