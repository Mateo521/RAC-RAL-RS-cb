
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Envios.h"
#include "RAC.h"

#include "RAL.h"
#include "RS.h"

int LecturaOperaciones();
char* Mayusculas();
void mostrarSubmenu()
{
    printf("--Submenu--\n");
    printf("1. Rebalse Abierto Lineal (RAL)\n");
    printf("2. Rebalse Abierto Cuadratico (RAC)\n");
    printf("3. Rebalse Separado (RS)\n");
    printf("4. Volver al Menu Principal\n");
}
char *Mayusculas(char string[])
{
    int i;
    for(i=0; string[i]!='\0'; i++)
    {
        string[i]= toupper(string[i]);
    }
    return  string;
}




int main()
{
    // Crea las estructuras de datos (LSO, ABB) aqu

    int opcion, submenu_opcion;


rac RAC[MaxEnvios];
initRAC(RAC);


rs RS;
initRS(&RS);

ral RAL[MaxEnvios];
initRAL(RAL);



    do
    {
        // Men  principal

        printf("1. Comparacion de estructuras\n");
        printf("2. Mostrar Estructura\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
            case 1:
                system("cls");

                LecturaOperaciones(&RAC, &RAL, &RS);

                printf("\n         AltaMax | AltaMed | BajaMax | BajaMed | Max.Ev.Ex | Med.Ev.Ex | Max.Ev.Fr | Med.Ev.Fr|\n");
                 printf("   RAL::\n");
                printf("-----------------------------------------------------------------------------------------------\n");
                printf("   RAC::\n");
                printf("-----------------------------------------------------------------------------------------------\n");
                printf("    RS::\n");
                printf("-----------------------------------------------------------------------------------------------\n");
                    break;
            case 2:


                system("cls");
                do
                {
                    mostrarSubmenu();
                    printf("Seleccione una opcion: ");
                    scanf("%d", &submenu_opcion);
                    switch (submenu_opcion)
                    {
                        case 1:
                            system("cls");

                            printf("Rebalse Abierto Lineal (RAL):\n");

                            MostrarEnviosRAL(RAL);

                            break;
                        case 2:
                            system("cls");
                            printf("Rebalse Abierto Cuadratico (RAC):\n");
                            MostrarEnviosRAC(RAC);

                            break;
                        case 3:
                            system("cls");
                            printf("Rebalse Separado (RS):\n");
                            MostrarEnviosRS(&RS);
                            break;
                        case 4:
                            system("cls");
                            // Volver
                            break;
                        default:
                            printf("Opcion no valida. Intente de nuevo.\n");
                    }
                }
                while (submenu_opcion != 4);

                break;
            case 3:
                system("cls");
                printf("Saliendo de la aplicacion.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    }
    while (opcion != 3);


    return 0;
}
int LecturaOperaciones(rac *RAC, ral *RAL, rs *RS)
{

    // Declaraciones e inicializaciones

    Envio aux;
    FILE* fp;

    if ((fp = fopen(/*"Operaciones-Envios.txt"*/"Operaciones-Envios.txt", "r")) == NULL)
    {
        printf("No se pudo abrir el archivo");
        return 0;
    }
    else
    {
        int codigoOperador=0,i;
        while (!(feof(fp)))
        {



            fscanf(fp, "%d", &codigoOperador);

            fscanf(fp, " %[^\n]", aux.codigo);
             for(i=0;i<=8;i++){
                aux.codigo[i]=toupper(aux.codigo[i]);
            }
            if (codigoOperador == 1 || codigoOperador == 2)
            {
                fscanf(fp, "%d", &aux.dni_receptor);

                fscanf(fp, " %[^\n]", aux.nombre);
                 for(i=0;i<=strlen(aux.nombre);i++){
                aux.nombre[i]=toupper(aux.nombre[i]);
            }
                fscanf(fp, " %[^\n]", aux.direccion);
                  for(i=0;i<=strlen(aux.direccion);i++){
                aux.direccion[i]=toupper(aux.direccion[i]);
            }
                fscanf(fp, "%d", &aux.dni_remitente);
                fscanf(fp, " %[^\n]", aux.nombre_r);
                  for(i=0;i<=strlen(aux.nombre_r);i++){
                aux.nombre_r[i]=toupper(aux.nombre_r[i]);
            }
                fscanf(fp, " %[^\n]", aux.fecha_envio);
                fscanf(fp, " %[^\n]", aux.fecha_recepcion);
                if(codigoOperador == 1)
                {


          //     printf("ALTA: %s\n", aux.codigo);

                       AltaRS(RS, aux);
                       AltaRAC(RAC,aux);
                       AltaRAL(RAL,aux);
/*
                        printf("%d\n" , Hashing(aux.codigo,300));
*/
                }
               else if(codigoOperador == 2)
                {


             //   printf("BAJA: %s\n", aux.codigo);

            BajaRS(RS, aux); //funciono

    BajaRAC(RAC,aux); // no funciona

    BajaRAL(RAL,aux); // no funciona

                }

            }
            else if (codigoOperador == 3)
            {
               EvocarRAC(RAC,aux.codigo,&aux);
               EvocarRAL(RAL,aux.codigo,&aux);

               EvocarRS(RS, aux.codigo, &aux);

           }
            else
            {
                // Maneja el caso de c digo de operaci n no reconocido
                printf("Error: Codigo de operaci n no reconocido.\n");
                //break;
            }

        }

        fclose(fp);


        return 1;
    }

}
