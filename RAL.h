#ifndef RAL_H
#define RAL_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MaxEnviosRAL 300

///---------------------------------------------------------ESTRUCTURAS
typedef struct
{
    Envio envio;
    int Flag; // 0 VIRGEN 1 LIBRE 2 OCUPADA
} ral;

// ---------------------------------------------------------RAC
void initRAL(ral *RAL)
{

    for (int i = 0; i < MaxEnviosRAL; i++)
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



float CantEvocarExitosoRAL = 0.0;
float CantEvocarFracasoRAL = 0.0;


float EvocarExitosoMaximoRAL= 0.0;
float EvocarFracasoMaximoRAL= 0.0;

float temporal_ERAL=0.0;
float temporal_FRAL=0.0;
int FlagAlta;

rloc LocalizarRAL(ral *RAL, char C[], int *pos, int p)
{
    int H = Hashing(C, MaxEnviosRAL);
    int i = 0, primerbaldelibre = 0, controldeprimerbaldelibre = 0, j = 1;
    rloc aux;
    FlagAlta = 0;
    while (i < MaxEnviosRAL && RAL[H].Flag != 0 && (strcmp(RAL[H].envio.codigo, C) != 0)) {
        if (controldeprimerbaldelibre == 0 && RAL[H].Flag == 1) {
            primerbaldelibre = H;
            controldeprimerbaldelibre = 1;
        }
        H = (H + j) % MaxEnviosRAL;
        i++;
    }
    if (RAL[H].Flag == 0) {
        if (controldeprimerbaldelibre == 1)
            H = primerbaldelibre;
        aux.exito = false;
    } else {
        if (i == MaxEnviosRAL) {
            aux.exito = false;
            if (controldeprimerbaldelibre == 1)
                H = primerbaldelibre;
            else
                FlagAlta = 1;
        } else if ((strcmp(RAL[H].envio.codigo, C) == 0) &&  RAL[H].Flag == 2)
            aux.exito = true;
    }
    aux.lugar = H;

    // Agrega el nuevo par�metro `pos` a la instrucci�n `return`
    if (pos != NULL) {
        *pos = aux.lugar;
    }

    return aux;
}

/*rloc LocalizarRAL(ral *RAL, char C[], int *pos, int p)
{

    float costoEvocarExitoso =0.0;
     float costoEvocarFracaso =0.0;
     float temp = 0.0;
    int H = Hashing(C, MaxEnviosRAL);
    int i = 0;
    rloc aux;

    while (i < MaxEnviosRAL) {
            temp++;
        if (RAL[H].Flag == 2 && strcmp(RAL[H].envio.codigo, C) == 0) {
            aux.exito = 1;
            aux.lugar = H;


                    if(p==1){
                    CantEvocarExitosoRAL++;
                    if(EvocarExitosoMaximoRAL<temp){
                        EvocarExitosoMaximoRAL = temp;
                    }
                    costoEvocarExitoso+=temp;

                     temporal_ERAL+=costoEvocarExitoso;


             }

            return aux;  // Encontramos el env�o, marcamos �xito y su posici�n
        }
        else if (RAL[H].Flag == 0) {
            aux.exito = 0;
            aux.lugar = H;  // Encontramos una posici�n vac�a, marcamos no �xito y su posici�n



               if(p==1){
                CantEvocarFracasoRAL++;
                         if(EvocarFracasoMaximoRAL<temp){
                        EvocarFracasoMaximoRAL = temp;
                    }
            costoEvocarFracaso+=temp;

            temporal_FRAL+=costoEvocarFracaso;


             }

            return aux;
        }
        H = (H + i) % MaxEnviosRAL;  // Avanzamos al siguiente �ndice
        i++;
    }

    aux.exito = 0;
    aux.lugar = -1;  // No se encontr� el env�o, marcamos no �xito y posici�n -1
    return aux;
}*/
///---------------------------------------------------------ALTA

float CantAltasRAL =0.0;
int AltaRAL(ral *RAL, Envio envio) {


    int pos;
    rloc aux = LocalizarRAL(RAL, envio.codigo, &pos, 0);
    if (aux.exito == 1) {
        return 0;
    } else {

            CantAltasRAL++;
            RAL[aux.lugar].envio = envio;
            RAL[aux.lugar].Flag = 2;
            return 1;

    }
}

///---------------------------------------------------------BAJA
float CantBajasRAL =0.0;
int BajaRAL(ral *RAL, Envio envio)
{
    int pos;
    rloc aux = LocalizarRAL(RAL, envio.codigo, &pos, 0);

    if (aux.exito==1) {
              if ((strcmp(RAL[aux.lugar].envio.codigo, envio.codigo)==0) && (strcmp(RAL[aux.lugar].envio.direccion, envio.direccion)==0) && (RAL[aux.lugar].envio.dni_receptor == envio.dni_receptor) &&
             (RAL[aux.lugar].envio.dni_remitente == envio.dni_remitente)&& (strcmp(RAL[aux.lugar].envio.fecha_envio, envio.fecha_envio)==0) && (strcmp(RAL[aux.lugar].envio.fecha_recepcion, envio.fecha_recepcion)==0)
             && (strcmp(RAL[aux.lugar].envio.nombre, envio.nombre)==0) && (strcmp(RAL[aux.lugar].envio.nombre_r, envio.nombre_r)==0)
             ){

            RAL[aux.lugar].Flag = 1; // Marcar el casillero como LIBRE
            CantBajasRAL++;
            return 1; // Baja exitosa

       }
        // Realiza cualquier otra operaci�n necesaria, como liberar memoria si es aplicable

    } else {

        return 0; // Baja no exitosa
    }
    return 0;
}




///---------------------------------------------------------EVOCAR
int EvocarRAL(ral *RAL,char C[], Envio *envio)
{
    int pos;
    rloc aux = LocalizarRAL(RAL, C, &pos, 1);
    if(aux.exito)
    {
        (*envio)=RAL[aux.lugar].envio;
        return 1;
    }
    else
        return 0;
}
///---------------------------------------------------------MOSTRAR ESTRUCTURA

void MostrarEnviosRAL(ral RAL[])
{

    int i,contador=0;
    for (i = 0; i < MaxEnviosRAL; i++)
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
            mostrarenvio(RAL[i].envio); // Llama a la funci�n para mostrar un env�o
            break;
        }
    }
    printf("total de envios : %d\n", contador);
    system("pause");
}


// Contenido de rac.h

#endif
