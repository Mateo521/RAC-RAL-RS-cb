#ifndef RAL_H
#define RAL_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MaxEnvios 300

///---------------------------------------------------------ESTRUCTURAS
typedef struct {
    Envio envio;
    int Flag; // 0 VIRGEN 1 LIBRE 2 OCUPADA
} ral;

// ---------------------------------------------------------RAC
void initRAL(ral *RAL) {

    for (int i = 0; i < MaxEnvios; i++) {

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
rloc LocalizarRAL(ral *RAL, char C[], int *pos, int p, int *FlagAlta){

    int H = Hashing(C,MaxEnvios);
    int i=0, primerbaldelibre=0, controldeprimerbaldelibre=0, j=3;///AVANCE
    rloc aux;

 while (i < MaxEnvios && RAL[H].Flag != 0 && (strcmp(RAL[H].envio.codigo, C) != 0)) {
    if (controldeprimerbaldelibre == 0 && RAL[H].Flag == 1) {
        primerbaldelibre = H;
        controldeprimerbaldelibre = 1;
    }
    H = (H + j) % MaxEnvios;
    i++;
}

    if(RAL[H].Flag==0){
        if(controldeprimerbaldelibre==1)
            H=primerbaldelibre;
        aux.exito=false;
    }else {
        if(i==MaxEnvios){
            aux.exito=false;
            if(controldeprimerbaldelibre==1)
                H=primerbaldelibre;
            else
                *FlagAlta=1;
        }else
        if((strcmp(RAL[H].envio.codigo,C)==0))
            aux.exito=true;
    }
    aux.lugar=H;
    return aux;
}

///---------------------------------------------------------ALTA
int AltaRAL(ral *RAL, Envio envio, int *FlagAlta) {

    int pos;
    rloc aux = LocalizarRAL(RAL, envio.codigo, &pos,0, FlagAlta);
    if (aux.exito || *FlagAlta == 1) {
        return 0; // Elemento ya existe o no se puede agregar
    } else {

        RAL[aux.lugar].envio = envio;
        RAL[aux.lugar].Flag = 2; // Marcar el casillero como OCUPADO
        return 1; // Elemento agregado con éxito
    }
}

///---------------------------------------------------------BAJA

int BajaRAL(ral *RAL,Envio envio, int *FlagBaja) {
    int pos;
    rloc aux = LocalizarRAL(RAL, envio.codigo, &pos, 0, FlagBaja);

    if (aux.exito && *FlagBaja == 0) {


        RAL[aux.lugar].Flag = 1; // Marcar el casillero como LIBRE
        // Limpia o actualiza otros campos si es necesario
        // RAL[aux.lugar].envio = ...;
        return 1; // Baja exitosa
    } else if (*FlagBaja == 1) {
        return 2; // Error: No se puede dar de baja debido a FlagBaja
    } else {
        return 0; // Elemento no encontrado
    }
}


///---------------------------------------------------------EVOCAR
int EvocarRAL(ral *RAL,char C[], Envio *envio, int *FlagAlta){
    int pos;
    rloc aux = LocalizarRAL(RAL, C, &pos, 0, FlagAlta);
    if(aux.exito){
         (*envio)=RAL[aux.lugar].envio;
        return 1;///ARTICULO ENCONTRADO
    }else
        return 0;///ARTICULO NO ENCONTRADO
}
///---------------------------------------------------------MOSTRAR ESTRUCTURA
/*
void Muestra(Articulo A){
    printf("\t-------------------------------------------------------------------------------------\n\n"
           "\t    >>>>>>>>>>>                       DATOS:                       <<<<<<<<<<<\n\n"
           "\t-------------------------------------------------------------------------------------\n\n");

    printf("> CODIGO: %s\n", A.codigo);
    printf("> TIPO: %s\n", A.tipo);
    printf("> MARCA: %s\n", A.marca);
    printf("> DESCRIPCION: %s\n", A.Descripcion);
    printf("> CANTIDAD: %d\n", A.Cantidad);
    printf("> PRECIO: %f\n", A.precio);
}
*/
void MostrarEnviosRAL(ral RAL[]) {
 int i,contador=0;
    for (i = 0; i < MaxEnvios; i++) {
        switch (RAL[i].Flag) {
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
