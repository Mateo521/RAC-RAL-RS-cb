#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED


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



#endif // RAL_H_INCLUDED
