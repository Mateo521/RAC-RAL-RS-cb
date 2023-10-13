#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MaxRAC 307
#define MaxRAL 337
#define Max 250
///---------------------------------------------------------ESTRUCTURAS
typedef struct {
    char    codigo[10];
    char    tipo[21];
    char    marca[31];
    char    Descripcion[101];
    int     Cantidad;
    float   precio;
    int     Flag;/// 0 VIRGEN 1 LIBRE 2 OCUPADA
}Articulo;

typedef struct {
    int lugar;
    bool exito;
}rloc;

typedef struct Nodo{
    Articulo Articulo;
    struct Nodo *HI,*HD;
}Nodo;
///---------------------------------------------------------VARIABLES
double pRAC=0.83,pRAL=0.75;
Nodo *Actual=NULL, *Anterior=NULL, *ActualAux=NULL,*AnteriorAux=NULL,*Raiz=NULL;
Articulo RAC[MaxRAC],RAL[MaxRAL];
int FlagAlta;
//int CantElmRAC=0,CantElmRAL=0;/// CANTIDAD DE ELEMENTOS EN CADA ESTRUCTURA
///---------------------------------------------------------HASHING
int Hashing(char codigo[], int M){
    int  longitud,i,contador=0;
    //char codigo[8];
    // sprintf(codigo, "%s", x);
    // longitud=strlen(codigo);
    longitud=strlen(codigo);
    for(i=0;i<longitud;i++)
        contador+=((int)codigo[i]) * (i+1);
    return (contador % M);
}
///---------------------------------------------------------AUXILIARES
void Mostrador(Articulo A){
    printf("CODIGO:\t\t%s\n", A.codigo);
    printf("MARCA:\t\t%s\n", A.marca);
    printf("TIPO:\t\t%s\n", A.tipo);
    printf("DESCRIPCION:\t%s\n", A.Descripcion);
    printf("PRECIO:\t\t%f\n", A.precio);
    printf("CANTIDAD:\t\t%i\n", A.Cantidad);
    printf("--------------------------\n");
}
Articulo CargaDatos(){
    Articulo A;
    ///CODIGO
    printf("INGRESE EL CODIGO DEL ARTICULO\n");
    fflush(stdin);
    gets(A.codigo);
    for(int i=0;A.codigo[i]!='\0';i++)
        A.codigo[i]= toupper(A.codigo[i]);
    ///TIPO
    printf("INGRESE EL TIPO DE ARTICULO\n");
    fflush(stdin);
    gets(A.tipo);
    for(int i=0;A.tipo[i]!='\0';i++)
        A.tipo[i]= toupper(A.tipo[i]);
    ///MARCA
    printf("INGRESE LA MARCA DEL ARTICULO\n");
    fflush(stdin);
    gets(A.marca);
    for(int i=0;A.marca[i]!='\0';i++)
        A.marca[i]= toupper(A.marca[i]);
    ///DESCRIPCION
    printf("INGRESE UNA DESCRIPCION DEL ARTICULO\n");
    fflush(stdin);
    gets(A.Descripcion);
    for(int i=0;A.Descripcion[i]!='\0';i++)/// CAMBIO EL 0 POR LA N YA QUE HAY ESPACIOS EN BLANCO
        A.Descripcion[i]= toupper(A.Descripcion[i]);
    ///CANTIDAD
    printf("INGRESE LA CANTIDAD DE ARTICULOS\n");
    fflush(stdin);
    scanf("%d",&A.Cantidad);
    ///PRECIO
    printf("INGRESE EL PRECIO DEL ARTICULO\n");
    fflush(stdin);
    scanf("%f",&A.precio);
    return A;
}
///---------------------------------------------------------RAC
void initRAC(){
    for(int i=0;i<MaxRAC;i++){
        strcpy(RAC[i].codigo, "nill");
        strcpy(RAC[i].marca, "nill");
        strcpy(RAC[i].tipo, "nill");
        strcpy(RAC[i].Descripcion, "nill");
        RAC[i].Cantidad=0;
        RAC[i].precio=0.0;
        RAC[i].Flag=0;
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
///---------------------------------------------------------RAL
void initRAL(){
    for(int i=0;i<MaxRAL;i++){
        strcpy(RAL[i].codigo, "nill");
        strcpy(RAL[i].marca, "nill");
        strcpy(RAL[i].tipo, "nill");
        strcpy(RAL[i].Descripcion, "nill");
        RAL[i].Cantidad=0;
        RAL[i].precio=0.0;
        RAL[i].Flag=0;
    }
}
///---------------------------------------------------------LOCALIZAR
rloc LocalizarRAL(char C[]) {
    int H = Hashing(C,MaxRAL);
    int i=0, primerbaldelibre=0, controldeprimerbaldelibre=0, j=3;///AVANCE
    rloc aux;
    FlagAlta=0;
    while(i<MaxRAL && RAL[H].Flag!=0 && (strcmp(RAL[H].codigo,C)!=0)) {
        if (controldeprimerbaldelibre == 0 && RAL[H].Flag==1) {
            primerbaldelibre = H;
            controldeprimerbaldelibre = 1;
        }
        H = (H + j) % MaxRAL;
        i++;
    }
    if(RAL[H].Flag==0){
        if(controldeprimerbaldelibre==1)
            H=primerbaldelibre;
        aux.exito=false;
    }else {
        if(i==MaxRAL){
            aux.exito=false;
            if(controldeprimerbaldelibre==1)
                H=primerbaldelibre;
            else
                FlagAlta=1;
        }else
        if((strcmp(RAL[H].codigo,C)==0))
            aux.exito=true;
    }
    aux.lugar=H;
    return aux;
}
///---------------------------------------------------------ALTA
int AltaRAL(Articulo A){
    rloc aux = LocalizarRAL(A.codigo);
    if(aux.exito || FlagAlta==1)
        return 0;
    else{
        RAL[aux.lugar]=A;
        RAL[aux.lugar].Flag=2;
        //CantElmRAL++;
        return 1;
    }
}
///---------------------------------------------------------BAJA
int BajaRAL(char C[]){
    rloc aux = LocalizarRAL(C);
    int opcion;
    if(aux.exito){
        printf("EL ARTICULO SE ENCUENTRA EN STOCK");
        Mostrador(RAL[aux.lugar]);
        printf("ESTA SEGURO QUE DESEA SUPRIMIR ESTE ARTICULO?\n");
        printf("1_ SI, ESTOY SEGURO \nCUALQUIER OTRO NUMERO PARA CANCELAR\n");
        fflush(stdin);
        scanf("%d",&opcion);
        fflush(stdin);
        if(opcion==1){
            strcpy(RAL[aux.lugar].codigo, "nill");
            strcpy(RAL[aux.lugar].marca, "nill");
            strcpy(RAL[aux.lugar].tipo, "nill");
            strcpy(RAL[aux.lugar].Descripcion, "nill");
            RAL[aux.lugar].Cantidad=0;
            RAL[aux.lugar].precio=0.0;
            RAL[aux.lugar].Flag=1;
            return 1;///BAJA EXITOSA
        }else
            return 3;///BAJA CANCELADA

    }else
        return 0;///ELEMENTO NO ENCONTRADO
}
///---------------------------------------------------------EVOCAR
int EvocarRAL(char C[], Articulo *A){
    rloc aux = LocalizarRAL(C);
    if(aux.exito){
        *A=RAL[aux.lugar];
        return 1;///ARTICULO ENCONTRADO
    }else
        return 0;///ARTICULO NO ENCONTRADO
}
///---------------------------------------------------------MOSTAR ESTRUCTURA
void MostrarRAL(){
    int i;
    for(i=0;i<MaxRAL;i++){
        switch(RAL[i].Flag){
            case 0: printf("\t\t POSICION [ %i ] VIRGEN\n",i);break;
            case 1: printf("\t\t POSICION [ %i ] LIBRE\n",i);break;
            case 2: printf("\t\t POSICION [ %i ] OCUPADA\n",i);Muestra(RAL[i]);break;
        }
    }
}
///---------------------------------------------------------ARBOL BINARIO DE BUSQUEDA
Nodo* NuevoNodo(Articulo A){
    Nodo *aux= (Nodo *) malloc(sizeof(Nodo));
    aux->Articulo=A;
    aux->HD=NULL;
    aux->HI=NULL;
    return aux;
}
void NodoMayor(Nodo* Inicio){
    AnteriorAux=NULL;
    ActualAux=Inicio;
    while(ActualAux->HD!=NULL){
        AnteriorAux=ActualAux;
        ActualAux=ActualAux->HD;
    }
}
///---------------------------------------------------------MOSTRAR
void Recorrer(struct Nodo* Aux){
    Articulo *AuxiliarI=&(Aux->HI->Articulo);
    Articulo *AuxiliarD=&(Aux->HD->Articulo);
    if(((*Aux).HI != NULL) && ((*Aux).HD != NULL)){ // AMBOS HIJOS DISTINTOS DE NULL
        printf("\n-----------Hijo Izquierdo--------------------------Hijo Derecho---------------\n");
        printf("CODIGO: %s\t\t\t\t\tCODIGO: %s\n",(*AuxiliarI).codigo,(*AuxiliarD).codigo);
    }else{
        if((*Aux).HI != NULL){ // HIJO IZQUIERDO DISTINTO DE NULL
            printf("\n-----------Hijo Izquierdo---------------\n");
            printf("CODIGO: %s\n",(*AuxiliarI).codigo);
        }else{
            printf("\n---Hijo IZQ: NULL----");
        }
        if((*Aux).HD != NULL){ // HIJO DERECHO DISTINTO DE NULL
            printf("\n\t\t\t\t\t-----------Hijo Derecho---------------\n");
            printf("\t\t\t\t\t\tDNI: %s\n",(*AuxiliarD).codigo);
        }else{
            printf("\n\t\t\t\t\t\t---Hijo DER: NULL----");
        }
    }
    printf("\n-------------------------------------------------------------------------\n");
}
void MostrarABB(Nodo* Padre){///BARRIDO PREORDEN
    if(Padre!=NULL){
        Muestra((*Padre).Articulo);
        Recorrer(Padre);
        fflush(stdin);
        printf("> INGRESE ENTER PARA MOSTRAR MAS\n\n");
        getchar();
        MostrarABB((*Padre).HI);
        MostrarABB((*Padre).HD);
    }
}
///---------------------------------------------------------LOCALIZAR
int LocalizarABB(char C[]){
    Actual=Anterior=Raiz;
    while(Actual!=NULL && (strcmp(Actual->Articulo.codigo,C)!=0)){
        if(strcmp(C,Actual->Articulo.codigo)<0){
            Anterior=Actual;
            Actual=Actual->HI;
        }else{
            Anterior=Actual;
            Actual=Actual->HD;
        }
    }
    if(Actual!=NULL){
        return 1;
    }else
        return 0;
}
///---------------------------------------------------------ALTA
int AltaABB(Articulo A){
    if(LocalizarABB(A.codigo)){
        return 0;///EL ELEMENTO SE ENCUENTRA EN LA ESTRUCTURA
    }else{
        Nodo *Aux;
        Aux= NuevoNodo(A);
        if(Aux!=NULL) {///HAY MEMORIA DISPONIBLE
            if(Raiz==NULL){
                Raiz=Aux;
            }else{
                if((strcmp(Aux->Articulo.codigo,Anterior->Articulo.codigo)<0))
                    Anterior->HI=Aux;
                else
                    Anterior->HD=Aux;
            }
            return 1;
        }else
            return -1;
    }
}
///---------------------------------------------------------BAJA
int BajaABB(char C[]){
    int opcion;
    if(LocalizarABB(C)){
        printf("EL ARTICULO SE ENCUENTRA EN STOCK");
        Mostrador(Actual->Articulo);
        printf("ESTA SEGURO QUE DESEA SUPRIMIR ESTE ARTICULO?\n");
        printf("1_ SI, ESTOY SEGURO \nCUALQUIER OTRO NUMERO PARA CANCELAR\n");
        fflush(stdin);
        scanf("%d",&opcion);
        fflush(stdin);
        if(opcion==1){
            if(Actual->HD==NULL && Actual->HI==NULL){///CASO SIN HIJOS
                if(Actual==Raiz){///ES RAIZ
                    Raiz=NULL;
                }else{///NO ES RAIZ
                    if((strcmp(Actual->Articulo.codigo,Anterior->Articulo.codigo)<0))///ACTUAL ES HIJO IZQUIERDO
                        Anterior->HI=NULL;
                    else///ACTUAL ES HIJO DERECHO
                        Anterior->HD=NULL;
                }
                free(Actual);
            }
            if((Actual->HD!=NULL && Actual->HI==NULL) || (Actual->HD==NULL && Actual->HI!=NULL)){///CASO CON UN SOLO HIJO
                Nodo *Aux;
                if(Actual->HI!=NULL)
                    Aux=Actual->HI;
                else
                    Aux=Actual->HD;
                if(Actual==Raiz){
                    Raiz=Aux;
                }else{
                    if((strcmp(Actual->Articulo.codigo,Anterior->Articulo.codigo)<0))///ES HIJO IZQUIERDO
                        Anterior->HI=Aux;
                    else
                        Anterior->HD=Aux;
                }
                free(Actual);
            }
            if(Actual->HD!=NULL && Actual->HI!=NULL){///TIENE AMBOS HIJOS
                NodoMayor(Actual->HI);
                if(AnteriorAux==NULL){
                    Actual->HI=ActualAux->HI;
                }else{
                    AnteriorAux->HD=ActualAux->HI;
                }
                Actual->Articulo=ActualAux->Articulo;
                free(ActualAux);
            }
            return 1;///BAJA EXITOSA
        }else
            return 0;///BAJA CANCELADA
    }else
        return -1;///EL ARTICULO NO SE ENCUENTRA EN STOCK
}
///---------------------------------------------------------EVOCAR
int EvocarABB(char C[], Articulo *A){
    if(LocalizarABB(C)){
        *A=Actual->Articulo;
        return 1;///ARTICULO ENCONTRADO
    }else
        return 0;///EL ARTICULO NO SE ENCUENTRA EN STOCK
}
///---------------------------------------------------------MEMORIZACION PREVIA
void Memorizacion(int Estructura){
    FILE *Archivo;
    Articulo Articulos;
    Archivo= fopen("Articulos.txt","r");
    if(Archivo==NULL){
        printf("ERROR, NO SE PUDO ABRIR EL ARCHIVO");
        system("pause");
        system("cls");
    }else{
        while(!feof(Archivo)){

            fgets(Articulos.codigo,10,Archivo);
                Articulos.codigo[8]='\0';
                fgets(Articulos.tipo,21,Archivo);
                Articulos.tipo[strlen(Articulos.tipo)-1]='\0';
                fgets(Articulos.marca,31,Archivo);
                Articulos.marca[strlen(Articulos.marca)-1]='\0';
                fgets(Articulos.Descripcion,101,Archivo);
                Articulos.Descripcion[strlen(Articulos.Descripcion)-1]='\0';
                fscanf(Archivo,"%f\n",&Articulos.precio);
                fscanf(Archivo,"%d\n",&Articulos.Cantidad);


            /*
            fgets(Articulos.tipo,20,Archivo);
            for(int i=0;i<20;i++)
            Articulos.tipo[i]= toupper(Articulos.tipo[i]);
            fgets(Articulos.marca,30,Archivo);
            for(int i=0;i<30;i++)
            Articulos.marca[i]= toupper(Articulos.marca[i]);
            fgets(Articulos.Descripcion,100,Archivo);
            for(int i=0;i<100;i++)
            Articulos.Descripcion[i]= toupper(Articulos.Descripcion[i]);
            fscanf(Archivo,"%d",&Articulos.Cantidad);
            fscanf(Archivo,"%f",&Articulos.precio);
            */
            if(Estructura==1)
            AltaRAL(Articulos);
            if(Estructura==2)
            AltaRAC(Articulos);
            if(Estructura==3)
            AltaABB(Articulos);
        }
        printf("CARGA EXITOSA.\n");
        system("pause");
        system("cls");
    }
    fclose(Archivo);
}
///---------------------------------------------------------MAIN
int main(){
    int selector, Operacion =0, retorno=-1;
    Articulo BALDES;
    initRAC();
    initRAL();
    printf("BIENVENIDO. QUE ESTRUCTURA DESEA UTILIZAR?: :\n\n"); ///---MENU PRIMARIO
    do{
        printf("\n 1_REBALSE ABIERTO LINEAL\n");
        printf(" 2_REBALSE ABIERTO CUADRATICO\n");
        printf(" 3_ARBOL BINARIO DE BUSQUEDA\n");
        printf(" 4_SALIR\n");
        fflush(stdin);
        scanf("%i",&selector);
        if (selector<1 || selector>4)
            printf("INGRESE UN NUMERO VALIDO:\n");
        if(selector==4){
            break;
        }
        do{                   ///MENU DE MANEJO DE ESTRUCTURAS
            system("cls");
            printf("1_INGRESO DE ARTICULO NUEVO\n");//ALTA
            printf("2_ELIMINAR ARTICULO EN STOCK\n");//BAJA
            printf("3_CONSULTA DESCRIPCION DE UN ARTICULO EN STOCK\n");//EVOCAR
            printf("4_MEMORIZACION PREVIA\n");//MEMORIZACION PREVIA
            printf("5_MOSTRAR ESTRUCTURA\n");//MOSTRAR
            printf("6_VOLVER\n");//VOLVER
            fflush(stdin);
            scanf("%i", &Operacion);
            if (Operacion<1 || Operacion>6){
                system("cls");
                printf("INGRESE UN NUMERO VALIDO:\n");
            }

            switch (Operacion){
                case 1:{///ALTA
                    /*printf("INGRESE EL CODIGO DEL ARTICULO\n");
                    fflush(stdin);
                    scanf("%s",BALDES.codigo);
                    for(int i=0;BALDES.codigo[i]!='\0';i++)
                        BALDES.codigo[i]= toupper(BALDES.codigo[i]);
                    printf("INGRESE EL TIPO DEL ARTICULO\n");
                    fflush(stdin);
                    scanf("%s",BALDES.tipo);
                    for(int i=0;BALDES.tipo[i]!='\0';i++)
                        BALDES.tipo[i]= toupper(BALDES.tipo[i]);
                    printf("INGRESE LA MARCA DEL ARTICULO\n");
                    fflush(stdin);
                    scanf("%s",BALDES.marca);
                    for(int i=0;BALDES.marca[i]!='\0';i++)
                        BALDES.marca[i]= toupper(BALDES.marca[i]);
                    printf("INGRESE UNA DESCRIPCION DEL ARTICULO\n");
                    fflush(stdin);
                    scanf("%[^\n]s",BALDES.Descripcion);
                    for(int i=0;BALDES.Descripcion[i]!='\0';i++)
                        BALDES.Descripcion[i]= toupper(BALDES.Descripcion[i]);
                    printf("INGRESE LA CANTIDAD DE ARTICULOS\n");
                    fflush(stdin);
                    scanf("%d",&BALDES.Cantidad);
                    printf("INGRESE EL PRECIO DEL ARTICULO\n");
                    fflush(stdin);
                    scanf("%f",&BALDES.precio);*/

                    BALDES=CargaDatos();

                    switch (selector){
                        case 1: ///REBALSE ABIERTO LINEAL
                            retorno=AltaRAL(BALDES);
                            break;
                        case 2: ///REBALSE ABIERTO CUADRATICO
                            retorno=AltaRAC(BALDES);
                            break;
                        case 3: ///ARBOL BINARIO DE BUSQUEDA
                            retorno= AltaABB(BALDES);
                    }
                    if (retorno==1)
                        printf("ALTA REALIZADA.\n");
                    else
                        printf("EL ARTICULO YA SE ENCUENTRA EN EL STOCK\n");
                    system("pause");
                    Operacion=0;
                    break;
                }
                case 2: {///BAJA
                    char codigo[8];
                    printf("INGRESE EL CODIGO DEL ARTICULO A ELIMINAR\n");
                    fflush(stdin);
                    gets(codigo);
                    for(int i=0;codigo[i]!='\0';i++)
                        codigo[i]= toupper(codigo[i]);
                    /* printf("INGRESE EL TIPO DEL ARTICULO A ELIMINAR");
                     fflush(stdin);
                     scanf("%[^\n]s",BALDES.tipo);
                     printf("INGRESE LA MARCA DEL ARTICULO A ELIMINAR");
                     fflush(stdin);
                     scanf("%[^\n]s",BALDES.marca);
                     printf("INGRESE UNA DESCRIPCION DEL ARTICULO A ELIMINAR");
                     fflush(stdin);
                     scanf("%[^\n]s",BALDES.Descripcion);
                     printf("INGRESE LA CANTIDAD DE ARTICULOS A ELIMINAR");
                     fflush(stdin);
                     scanf("%d",&BALDES.Cantidad);
                     printf("INGRESE EL PRECIO DEL ARTICULO A ELIMINAR");
                     fflush(stdin);
                     scanf("%f",&BALDES.precio);*/
                    switch (selector){
                        case 1: ///REBALSE ABIERTO LINEAL
                            retorno=BajaRAL(codigo);
                            break;
                        case 2: ///REBALSE ABIERTO CUADRATICO
                            retorno=BajaRAC(codigo);
                            break;
                        case 3: ///ARBOL BINARIO DE BUSQUEDA
                            retorno= BajaABB(codigo);
                            break;
                    }
                    if (retorno==1)
                        printf("BAJA REALIZADA.\n");
                    else {
                        if(retorno==0)
                            printf("EL ARTICULO NO SE ENCUENTRA EN EL STOCK\n");
                        else
                            printf("LA BAJA A SIDO CANCELADA CON EXITO\n");
                    }
                    system("pause");
                    Operacion=0;
                    break;
                }
                case 3:{///EVOCAR
                    printf("INGRESE EL CODIGO DEL ARTICULO A EVOCAR.\n");
                    fflush(stdin);
                    scanf("%[^\n]s",BALDES.codigo);
                    for(int i=0;BALDES.codigo[i]!='\0';i++)
                    BALDES.codigo[i]= toupper(BALDES.codigo[i]);
                    switch (selector){
                        case 1: ///REBALSE ABIERTO LINEAL
                            retorno=EvocarRAL(BALDES.codigo,&BALDES);
                            break;
                        case 2: ///REBALSE ABIERTO CUADRATICO
                            retorno=EvocarRAC(BALDES.codigo,&BALDES);
                            break;
                        case 3: ///ARBOL BINARIO DE BUSQUEDA
                            retorno=EvocarABB(BALDES.codigo,&BALDES);
                            break;
                    }
                    if (retorno==1){
                        printf("ARTICULO EN STOCK.\n");
                        Muestra(BALDES);
                        }
                    else {
                        printf("EL ARTICULO NO SE ENCUENTRA EN EL STOCK.\n");
                    }
                    system("pause");
                    Operacion=0;
                    break;
                }
                case 4:{///MEMORIZACION PREVIA
                    switch(selector){
                        case 1:
                            Memorizacion(1);
                            break;
                        case 2:
                            Memorizacion(2);
                            break;
                        case 3:
                            Memorizacion(3);
                            break;

                    }
                    Operacion=0;
                    break;
                }
                case 5:{///MOSTRAR
                    system("cls");
                    switch(selector){
                        case 1:
                            MostrarRAL();
                            break;
                        case 2:
                            MostrarRAC();
                            break;
                        case 3:{
                            if(Raiz==NULL)
                                printf("ARBOL VACIO");
                            else
                                MostrarABB(Raiz);
                            break;
                        }
                    }
                    Operacion=0;
                    system("pause");
                    break;
                }
                case 6:{///SALIR
                    //Operacion=0;
                    system("cls");
                    break;
                }
            }
        } while (Operacion<1 || Operacion>6);
    }while(selector>1 || selector<4);
    return 0;
}
