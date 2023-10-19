#ifndef RAC_H
#define RAC_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MaxEnviosRAC 300

typedef struct {
    Envio envio;
    int bandera;

} rac;


void initRAC(rac *RAC) {

    for (int i = 0; i < MaxEnviosRAC; i++) {

        RAC[i].bandera = 0;


       strcpy(RAC[i].envio.codigo, "");
strcpy(RAC[i].envio.direccion, "");
strcpy(RAC[i].envio.fecha_envio, "");
strcpy(RAC[i].envio.fecha_recepcion, "");
strcpy(RAC[i].envio.nombre, "");
strcpy(RAC[i].envio.nombre_r, "");
        RAC[i].envio.dni_receptor = 0;
        RAC[i].envio.dni_remitente = 0;

    }

}

float CantEvocarExitosoRAC = 0.0;
float CantEvocarFracasoRAC = 0.0;


float EvocarExitosoMaximoRAC= 0.0;
float EvocarFracasoMaximoRAC= 0.0;

float temporal_ERAC=0.0;
float temporal_FRAC=0.0;


float CantLocalizarRAC=0.0;

cons LocalizarRAC(rac *RAC, char C[], int *pos, int p)
{
      float costoEvocarExitoso =0.0;
     float costoEvocarFracaso =0.0;
     float temp = 0.0;
    int H = Hashing(C, MaxEnviosRAC);
    int i = 0, primerbaldelibre = 0, controldeprimerbaldelibre = 0, j = 1;
    cons aux;

  aux.exito= 0;
    while (i < MaxEnviosRAC && RAC[H].bandera != 0 && (strcmp(RAC[H].envio.codigo, C) != 0)) {
            temp++;
        if (controldeprimerbaldelibre == 0 && RAC[H].bandera == 1) {
            primerbaldelibre = H;
            controldeprimerbaldelibre = 1;
        }
        H = (H + j) % MaxEnviosRAC;
        i++;
        j++;
    }
    if (RAC[H].bandera == 0) {

            if(p==1){

                        CantEvocarFracasoRAC++;
                         if(EvocarFracasoMaximoRAC<temp){
                            EvocarFracasoMaximoRAC = temp;
                    }
                costoEvocarFracaso+=temp;
                temporal_FRAC+=costoEvocarFracaso;

            }

        if (controldeprimerbaldelibre == 1)
            H = primerbaldelibre;
        aux.exito = 0;
    } else {
        if (i == MaxEnviosRAC) {
            aux.exito = 0;
            if (controldeprimerbaldelibre == 1)
                H = primerbaldelibre;
        } else if ((strcmp(RAC[H].envio.codigo, C) == 0) &&  RAC[H].bandera == 2)
        {
if(p==1){
  CantEvocarExitosoRAC++;

                    if(EvocarExitosoMaximoRAC<temp){
                        EvocarExitosoMaximoRAC = temp;
                    }
                    costoEvocarExitoso+=temp;
                     temporal_ERAC+=costoEvocarExitoso;
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



float CantAltasRAC =0.0;
int AltaRAC(rac *RAC, Envio envio) {


    int pos;

    cons aux = LocalizarRAC(RAC, envio.codigo, &pos, 0); // Sin el &

    if (aux.exito) {
        return 0;
    } else {

        RAC[aux.lugar].envio = envio;

        RAC[aux.lugar].bandera = 2; // casillero  ocupado

        CantAltasRAC++;
        return 1;
    }

}


float CantBajasRAC =0.0;
int BajaRAC(rac *RAC, Envio envio)
{

    int pos;
    cons aux = LocalizarRAC(RAC, envio.codigo, &pos, 0);

    if (aux.exito == 1) {

         if ((strcmp(RAC[aux.lugar].envio.codigo, envio.codigo)==0) && (strcmp(RAC[aux.lugar].envio.direccion, envio.direccion)==0) && (RAC[aux.lugar].envio.dni_receptor == envio.dni_receptor) &&
             (RAC[aux.lugar].envio.dni_remitente == envio.dni_remitente)&& (strcmp(RAC[aux.lugar].envio.fecha_envio, envio.fecha_envio)==0) && (strcmp(RAC[aux.lugar].envio.fecha_recepcion, envio.fecha_recepcion)==0)
             && (strcmp(RAC[aux.lugar].envio.nombre, envio.nombre)==0) && (strcmp(RAC[aux.lugar].envio.nombre_r, envio.nombre_r)==0)
             ){

       RAC[aux.lugar].bandera = 1; //  casillero  libre
        CantBajasRAC++;

 return 1; // Baja exitosa
      }



    } else {

        return 0; // Baja no exitosa
    }
    return 0;
}
//float EvocarExitosoRAC = 0.0;
//float EvocarFracasoRAC = 0.0;
int EvocarRAC(rac *RAC,char C[], Envio *envio){
    int pos;
    cons aux = LocalizarRAC(RAC, C, &pos, 1);
    if(aux.exito){
   //         EvocarExitosoRAC++;
         (*envio)=RAC[aux.lugar].envio;
        return 1;
    }else
 //   EvocarFracasoRAC++;


        return 0;
}
void MostrarEnviosRAC(rac RAC[]) {
    int i,contador=0;
    for (i = 0; i < MaxEnviosRAC; i++) {
        switch (RAC[i].bandera) {
            case 0:
                printf(" posicion  %i  virgen\n", i);
                break;
            case 1:
                printf(" posicion  %i  libre\n", i);
                break;
            case 2:
                printf(" posicion  %i  ocupada\n", i);
                contador ++;
                mostrarenvio(RAC[i].envio);
                break;
        }
    }
    printf("total de envios : %d\n", contador);

}


#endif
