#ifndef RAL_H
#define RAL_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MaxEnviosRAL 300


typedef struct
{
    Envio envio;
    int bandera;
} ral;

void initRAL(ral *RAL)
{

    for (int i = 0; i < MaxEnviosRAL; i++)
    {

        RAL[i].bandera = 0;

        strcpy(RAL[i].envio.codigo, "");
        strcpy(RAL[i].envio.direccion, "");
        strcpy(RAL[i].envio.fecha_envio, "");
        strcpy(RAL[i].envio.fecha_recepcion, "");
        strcpy(RAL[i].envio.nombre, "");
        strcpy(RAL[i].envio.nombre_r, "");
        RAL[i].envio.dni_receptor = 0;
        RAL[i].envio.dni_remitente = 0;



    }

}



float CantEvocarExitosoRAL = 0.0;
float CantEvocarFracasoRAL = 0.0;


float EvocarExitosoMaximoRAL= 0.0;
float EvocarFracasoMaximoRAL= 0.0;

float temporal_ERAL=0.0;
float temporal_FRAL=0.0;
//int banderaAlta;

cons LocalizarRAL(ral *RAL, char C[], int *pos, int p)
{

     float costoEvocarExitoso =0.0;
     float costoEvocarFracaso =0.0;
     float temp = 0.0;
    int H = Hashing(C, MaxEnviosRAL);
    int i = 0, primerbaldelibre = 0, controldeprimerbaldelibre = 0, j = 1;
    cons aux;
    aux.exito = 0;
  //  banderaAlta = 0;
    while (i < MaxEnviosRAL && RAL[H].bandera != 0 && (strcmp(RAL[H].envio.codigo, C) != 0)) {
            temp++;
        if (controldeprimerbaldelibre == 0 && RAL[H].bandera == 1) {
            primerbaldelibre = H;
            controldeprimerbaldelibre = 1;
        }
        H = (H + j) % MaxEnviosRAL;
        i++;
    }
    if (RAL[H].bandera == 0) {
        if (controldeprimerbaldelibre == 1)
            H = primerbaldelibre;
     if(p==1){
                        CantEvocarFracasoRAL++;
                         if(EvocarFracasoMaximoRAL<temp){
                            EvocarFracasoMaximoRAL = temp;
                    }
                costoEvocarFracaso+=temp;
                temporal_FRAL+=costoEvocarFracaso;
            }
        aux.exito = 0;
    } else {
        if (i == MaxEnviosRAL) {
            aux.exito = 0;
            if (controldeprimerbaldelibre == 1)
                H = primerbaldelibre;
        } else if ((strcmp(RAL[H].envio.codigo, C) == 0) &&  RAL[H].bandera == 2){
        if(p==1){
  CantEvocarExitosoRAL++;
                if(EvocarExitosoMaximoRAL<temp){
                        EvocarExitosoMaximoRAL = temp;
                    }
                    costoEvocarExitoso+=temp;
                     temporal_ERAL+=costoEvocarExitoso;
            }
             aux.exito = 1;
        }

    }
    aux.lugar = H;

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
        if (RAL[H].bandera == 2 && strcmp(RAL[H].envio.codigo, C) == 0) {
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

            return aux;  // Encontramos el envío, marcamos éxito y su posición
        }
        else if (RAL[H].bandera == 0) {
            aux.exito = 0;
            aux.lugar = H;  // Encontramos una posición vacía, marcamos no éxito y su posición



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
        H = (H + i) % MaxEnviosRAL;  // Avanzamos al siguiente índice
        i++;
    }

    aux.exito = 0;
    aux.lugar = -1;  // No se encontró el envío, marcamos no éxito y posición -1
    return aux;
}*/


float CantAltasRAL =0.0;
int AltaRAL(ral *RAL, Envio envio) {


    int pos;
    cons aux = LocalizarRAL(RAL, envio.codigo, &pos, 0);
    if (aux.exito == 1) {
        return 0;
    } else {

            CantAltasRAL++;
            RAL[aux.lugar].envio = envio;
            RAL[aux.lugar].bandera = 2;
            return 1;

    }
}

float CantBajasRAL =0.0;
int BajaRAL(ral *RAL, Envio envio)
{
    int pos;
    cons aux = LocalizarRAL(RAL, envio.codigo, &pos, 0);

    if (aux.exito==1) {
              if ((strcmp(RAL[aux.lugar].envio.codigo, envio.codigo)==0) && (strcmp(RAL[aux.lugar].envio.direccion, envio.direccion)==0) && (RAL[aux.lugar].envio.dni_receptor == envio.dni_receptor) &&
             (RAL[aux.lugar].envio.dni_remitente == envio.dni_remitente)&& (strcmp(RAL[aux.lugar].envio.fecha_envio, envio.fecha_envio)==0) && (strcmp(RAL[aux.lugar].envio.fecha_recepcion, envio.fecha_recepcion)==0)
             && (strcmp(RAL[aux.lugar].envio.nombre, envio.nombre)==0) && (strcmp(RAL[aux.lugar].envio.nombre_r, envio.nombre_r)==0)
             ){

            RAL[aux.lugar].bandera = 1; // casillero  libre
            CantBajasRAL++;
            return 1; // Baja exitosa

       }


    } else {

        return 0; // Baja no exitosa
    }
    return 0;
}

int EvocarRAL(ral *RAL,char C[], Envio *envio)
{
    int pos;
    cons aux = LocalizarRAL(RAL, C, &pos, 1);
    if(aux.exito)
    {
        (*envio)=RAL[aux.lugar].envio;
        return 1;
    }
    else
        return 0;
}

void MostrarEnviosRAL(ral RAL[])
{

    int i,contador=0;
    for (i = 0; i < MaxEnviosRAL; i++)
    {

        switch (RAL[i].bandera)
        {
         case 0:
                printf(" posicion  %i  virgen\n", i);
                break;
            case 1:
                printf(" posicion  %i  libre\n", i);
                break;
            case 2:
                printf(" posicion  %i  ocupada\n", i);
            contador++;
            mostrarenvio(RAL[i].envio); // Llama a la función para mostrar un envío
            break;
        }
    }
    printf("total de envios : %d\n", contador);

}


#endif
