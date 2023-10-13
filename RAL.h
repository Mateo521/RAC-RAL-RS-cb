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
rloc LocalizarRAL(ral *RAL, char C[], int *pos, int p){

    int H = Hashing(C,MaxEnvios);
    int i=0, primerbaldelibre=0, controldeprimerbaldelibre=0, j=3;///AVANCE
    rloc aux;
    FlagAlta=0;
    while(i<MaxEnvios && RAL[H].Flag!=0 && (strcmp(RAL[H].envio.codigo,C)!=0)) {
        if (controldeprimerbaldelibre == 0 && RAL[H].Flag==1) {
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
                FlagAlta=1;
        }else
        if((strcmp(RAL[H].envio.codigo,C)==0))
            aux.exito=true;
    }
    aux.lugar=H;
    return aux;
}

///---------------------------------------------------------ALTA
int AltaRAL(ral *RAL, Envio envio) {
    int pos;



    rloc aux = LocalizarRAC(RAL, envio.codigo, pos,0);

    if (aux.exito || FlagAlta == 1) {
        return 0; // Elemento ya existe o no se puede agregar
    } else {

        // Si la función LocalizarRAC encontró un lugar disponible, puedes insertar el elemento C

        RAL[aux.lugar].envio = envio;
        RAL[aux.lugar].Flag = 2; // Marcar el casillero como OCUPADO
        // Actualiza cualquier otro contador o información que necesites
        // CantElmRAC++;
        return 1; // Elemento agregado con éxito
    }
}

///---------------------------------------------------------BAJA
int BajaRAL(ral *RAL, Envio envio) {
    int pos;
    rloc aux = LocalizarRAL(RAL, envio.codigo, &pos, 0);

    int opcion;
    if (aux.exito) {
        printf("EL ARTICULO SE ENCUENTRA EN STOCK");
        /*
        Mostrador(RAC[aux.lugar]);
        */
        printf("ESTA SEGURO QUE DESEA SUPRIMIR ESTE ARTICULO?\n");
        printf("1_ SI, ESTOY SEGURO \nCUALQUIER OTRO NUMERO PARA CANCELAR\n");
        fflush(stdin);
        scanf("%d", &opcion);
        fflush(stdin);

        if (opcion == 1 && FlagAlta == 0) {
            // Realiza la lógica de suprimir el artículo usando los campos reales de Envio
            strcpy(RAL[aux.lugar].envio.codigo, "nill");
            RAL[aux.lugar].envio.dni_receptor = 0;
            // Establece otros campos de Envio según tu estructura real
            strcpy(RAL[aux.lugar].envio.nombre, "nill");
            strcpy(RAL[aux.lugar].envio.direccion, "nill");
            RAL[aux.lugar].envio.dni_remitente = 0;
            strcpy(RAL[aux.lugar].envio.nombre_r, "nill");
            strcpy(RAL[aux.lugar].envio.fecha_envio, "nill");
            strcpy(RAL[aux.lugar].envio.fecha_recepcion, "nill");

            RAL[aux.lugar].Flag = 1;
            return 1; // BAJA EXITOSA
        } else if (FlagAlta == 1) {
            return 2; // Error: No se puede dar de baja debido a FlagAlta
        } else {
            return 3; // BAJA CANCELADA
        }
    } else {
        return 0; // ELEMENTO NO ENCONTRADO
    }
}

///---------------------------------------------------------EVOCAR
int EvocarRAL(ral *RAL,char C[], Envio *envio){
    int pos;
    rloc aux = LocalizarRAL(RAL, C, &pos, 0);
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
void MostrarEnviosRAL(rac RAL[]) {
    int i;
    for (i = 0; i < MaxEnvios; i++) {
        switch (RAL[i].Flag) {
            case 0:
                printf("\t\t POSICION [ %i ] VIRGEN\n", i);
                break;
            case 1:
                printf("\t\t POSICION [ %i ] LIBRE\n", i);
                break;
            case 2:
                printf("\t\t POSICION [ %i ] OCUPADA\n", i);
                mostrarenvio(RAL[i].envio); // Llama a la función para mostrar un envío
                break;
        }
    }
    system("pause");
}


// Contenido de rac.h

#endif
