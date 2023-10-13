#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MaxEnvios 300
#define MaxRAL 337
#define Max 250
///---------------------------------------------------------ESTRUCTURAS
typedef struct {
    Envio envio [MaxEnvios];
    int     Flag;/// 0 VIRGEN 1 LIBRE 2 OCUPADA
}rac;
///---------------------------------------------------------RAC
void initRAC(rac * RAC){
    for(int i=0;i<MaxEnvios;i++){
        strcpy(RAC[i]->envio.codigo, "null");
        strcpy(RAC[i]->envio.direccion, "null");
        strcpy(RAC[i].envio.dni_receptor, 0);
        strcpy(RAC[i].envio.dni_remitente, 0);
        strcpy(RAC[i].envio.fecha_envio, "null");
          strcpy(RAC[i].envio.fecha_recepcion, "null");
           strcpy(RAC[i].envio.nombre, "null");
            strcpy(RAC[i].envio.nombre_r, "null");

    }
}
///---------------------------------------------------------LOCALIZAR
rloc LocalizarRAC(char C[]){
    int H=Hashing(C,MaxRAC), i=0, j=1, primerbaldelibre=0, controldeprimerbaldelibre=0;
    rloc aux;
    FlagAlta=0;
    while(i<MaxRAC && RAC[H].Flag!=0 && (strcmp(RAC[H].codigo,C)!=0)){
        if(controldeprimerbaldelibre==0 && RAC[H].Flag==1) {
            primerbaldelibre = H;
            controldeprimerbaldelibre = 1;
        }
        H=(H+j)%MaxRAC;
        i++;
        j++;
    }
    if(RAC[H].Flag==0){
        if(controldeprimerbaldelibre==1)
            H=primerbaldelibre;
        aux.exito=false;
    }else {
        if(i==MaxRAC){
            aux.exito=false;
            if(controldeprimerbaldelibre==1)
                H=primerbaldelibre;
            else
                FlagAlta=1;
        }else
        if((strcmp(RAC[H].codigo,C)==0))
            aux.exito=true;
    }
    aux.lugar=H;
    return aux;
}
///---------------------------------------------------------ALTA
int AltaRAC(Articulo C){
    rloc aux = LocalizarRAC(C.codigo);
    if(aux.exito || FlagAlta==1)
        return 0;
    else{
        RAC[aux.lugar]=C;
        RAC[aux.lugar].Flag=2;
        //CantElmRAC++;
        return 1;
    }
}
///---------------------------------------------------------BAJA
int BajaRAC(char C[]){
    rloc aux = LocalizarRAC(C);
    int opcion;
    if(aux.exito){
        printf("EL ARTICULO SE ENCUENTRA EN STOCK");
        Mostrador(RAC[aux.lugar]);
        printf("ESTA SEGURO QUE DESEA SUPRIMIR ESTE ARTICULO?\n");
        printf("1_ SI, ESTOY SEGURO \nCUALQUIER OTRO NUMERO PARA CANCELAR\n");
        fflush(stdin);
        scanf("%d",&opcion);
        fflush(stdin);
        if(opcion==1){
            strcpy(RAC[aux.lugar].codigo, "nill");
            strcpy(RAC[aux.lugar].marca, "nill");
            strcpy(RAC[aux.lugar].tipo, "nill");
            strcpy(RAC[aux.lugar].Descripcion, "nill");
            RAC[aux.lugar].Cantidad=0;
            RAC[aux.lugar].precio=0.0;
            RAC[aux.lugar].Flag=1;
            return 1;///BAJA EXITOSA
        }else
            return 3;///BAJA CANCELADA

    }else
        return 0;///ELEMENTO NO ENCONTRADO
}
///---------------------------------------------------------EVOCAR
int EvocarRAC(char C[], Articulo *A){
    rloc aux = LocalizarRAC(C);
    if(aux.exito){
        *A=RAC[aux.lugar];
        return 1;///ARTICULO ENCONTRADO
    }else
        return 0;///ARTICULO NO ENCONTRADO
}
///---------------------------------------------------------MOSTRAR ESTRUCTURA
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
void MostrarRAC(){
    int i;
    for(i=0;i<MaxRAC;i++){
        switch(RAC[i].Flag){
            case 0: printf("\t\t POSICION [ %i ] VIRGEN\n",i);break;
            case 1: printf("\t\t POSICION [ %i ] LIBRE\n",i);break;
            case 2: printf("\t\t POSICION [ %i ] OCUPADA\n",i);Muestra(RAC[i]);break;
        }
    }
    system("pause");
}

#endif // RAC_H_INCLUDED
