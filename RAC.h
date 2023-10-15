#ifndef RAC_H
#define RAC_H
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
} rac;




// ---------------------------------------------------------RAC
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
rloc LocalizarRAC(rac *RAC, char C[], int *pos, int p, int *FlagAlta) {
    int H = Hashing(C, MaxEnvios);
    int i = 0, j = 1;
    int primerbaldelibre = -1; // Inicializado a un valor no válido
    int controldeprimerbaldelibre = 0;
    rloc aux;

    while (i < MaxEnvios && ((RAC[H].Flag != 0 && RAC[H].Flag != 1) || strcmp(RAC[H].envio.codigo, C) != 0)) {
        if (controldeprimerbaldelibre == 0 && RAC[H].Flag == 1) {
            primerbaldelibre = H;
            controldeprimerbaldelibre = 1;
        }
        H = (H + j) % MaxEnvios;
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


///---------------------------------------------------------ALTA
int AltaRAC(rac *RAC, Envio envio, int *FlagAlta) {
    int pos;

    rloc aux = LocalizarRAC(RAC, envio.codigo, &pos, 0, FlagAlta); // Sin el &

    if (aux.exito || *FlagAlta == 1) {
        return 0; // Elemento ya existe o no se puede agregar
    } else {
        // Si la función LocalizarRAC encontró un lugar disponible, puedes insertar el elemento C
        RAC[aux.lugar].envio = envio;
        RAC[aux.lugar].Flag = 2; // Marcar el casillero como OCUPADO
        // Actualiza cualquier otro contador o información que necesites
        // CantElmRAC++;
        return 1; // Elemento agregado con éxito
    }
}


///---------------------------------------------------------BAJA
int BajaRAC(rac *RAC, Envio envio, int *FlagAlta) {
    int pos;
rloc aux = LocalizarRAC(RAC, envio.codigo, &pos, 0, FlagAlta); // Sin el &

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

        if (opcion == 1 && *FlagAlta == 0) {
            // Realiza la lógica de suprimir el artículo usando los campos reales de Envio
            strcpy(RAC[aux.lugar].envio.codigo, "nill");
            RAC[aux.lugar].envio.dni_receptor = 0;
            // Establece otros campos de Envio según tu estructura real
            strcpy(RAC[aux.lugar].envio.nombre, "nill");
            strcpy(RAC[aux.lugar].envio.direccion, "nill");
            RAC[aux.lugar].envio.dni_remitente = 0;
            strcpy(RAC[aux.lugar].envio.nombre_r, "nill");
            strcpy(RAC[aux.lugar].envio.fecha_envio, "nill");
            strcpy(RAC[aux.lugar].envio.fecha_recepcion, "nill");

            RAC[aux.lugar].Flag = 1;
            return 1; // BAJA EXITOSA
        } else if (*FlagAlta == 1) {
            return 2; // Error: No se puede dar de baja debido a FlagAlta
        } else {
            return 3; // BAJA CANCELADA
        }
    } else {
        return 0; // ELEMENTO NO ENCONTRADO
    }
}

///---------------------------------------------------------EVOCAR
int EvocarRAC(rac *RAC,char C[], Envio *envio ,  int *FlagAlta){
    int pos;
    rloc aux = LocalizarRAC(RAC, C, &pos, 0,  FlagAlta);
    if(aux.exito){
         (*envio)=RAC[aux.lugar].envio;
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
