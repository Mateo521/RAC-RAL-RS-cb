#ifndef RAL_H
#define RAL_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MaxEnvios 300

///---------------------------------------------------------ESTRUCTURAS
typedef struct
{
    Envio envio;
    int Flag; // 0 VIRGEN 1 LIBRE 2 OCUPADA
} ral;

// ---------------------------------------------------------RAC
void initRAL(ral *RAL)
{

    for (int i = 0; i < MaxEnvios; i++)
    {

        RAL[i].Flag = 0; // Inicializar el campo Flag a 0

        // Inicializar los campos de la estructura Envio dentro de la estructura rac
        strcpy(RAL[i].envio.codigo, "");
        strcpy(RAL[i].envio.direccion, "");
        strcpy(RAL[i].envio.fecha_envio, "");
        strcpy(RAL[i].envio.fecha_recepcion, "");
        strcpy(RAL[i].envio.nombre, "");
        strcpy(RAL[i].envio.nombre_r, "");
        RAL[i].envio.dni_receptor = 0; // Inicializar dni_receptor a 0
        RAL[i].envio.dni_remitente = 0; // Inicializar dni_remitente a 0



    }

}


///---------------------------------------------------------LOCALIZAR
rloc LocalizarRAL(ral *RAL, char C[], int *pos, int p)
{
    int H = Hashing(C, MaxEnvios);
    int i = 0;
    rloc aux;

    while (i < MaxEnvios) {
        if (RAL[H].Flag == 2 && strcmp(RAL[H].envio.codigo, C) == 0) {
            aux.exito = 1;
            aux.lugar = H;
            return aux;  // Encontramos el envío, marcamos éxito y su posición
        }
        else if (RAL[H].Flag == 0) {
            aux.exito = 0;
            aux.lugar = H;  // Encontramos una posición vacía, marcamos no éxito y su posición
            return aux;
        }
        H = (H + 1) % MaxEnvios;  // Avanzamos al siguiente índice
        i++;
    }

    aux.exito = 0;
    aux.lugar = -1;  // No se encontró el envío, marcamos no éxito y posición -1
    return aux;
}


///---------------------------------------------------------ALTA
int AltaRAL(ral *RAL, Envio envio) {

    int pos;
    rloc aux = LocalizarRAL(RAL, envio.codigo, &pos, 0);
    if (aux.exito) {
        return 0; // Elemento ya existe o no se puede agregar
    } else {
        if (aux.lugar >= 0 && aux.lugar < MaxEnvios) {

     //             printf("%d\n",aux.lugar);
            RAL[aux.lugar].envio = envio;
            RAL[aux.lugar].Flag = 2; // Marcar el casillero como OCUPADO
            return 1; // Elemento agregado con éxito
        } else {
            return 0; // El índice está fuera de rango
        }
    }
}
///---------------------------------------------------------BAJA

int BajaRAL(ral *RAL, Envio envio)
{
    int pos;
    rloc aux = LocalizarRAL(RAL, envio.codigo, &pos, 0);

    if (aux.exito == 1) {


       RAL[aux.lugar].Flag = 1; // Marcar el casillero como LIBRE
        // Realiza cualquier otra operación necesaria, como liberar memoria si es aplicable
        return 1; // Baja exitosa
    } else {

        return 0; // Baja no exitosa
    }
}




///---------------------------------------------------------EVOCAR
int EvocarRAL(ral *RAL,char C[], Envio *envio)
{
    int pos;
    rloc aux = LocalizarRAL(RAL, C, &pos, 0);
    if(aux.exito)
    {
        (*envio)=RAL[aux.lugar].envio;
        return 1;///ARTICULO ENCONTRADO
    }
    else
        return 0;///ARTICULO NO ENCONTRADO
}
///---------------------------------------------------------MOSTRAR ESTRUCTURA

void MostrarEnviosRAL(ral RAL[])
{

    int i,contador=0;
    for (i = 0; i < MaxEnvios; i++)
    {

        switch (RAL[i].Flag)
        {
        case 0:
            printf("POSICION [ %i ] VIRGEN\n", i);
            break;
        case 1:
            printf("POSICION [ %i ] LIBRE\n", i);
            break;
        case 2:
            printf("POSICION [ %i ] OCUPADA\n", i);
            contador++;
            mostrarenvio(RAL[i].envio); // Llama a la función para mostrar un envío
            break;
        }
    }
    printf("total de envios : %d\n", contador);
    system("pause");
}


// Contenido de rac.h

#endif
