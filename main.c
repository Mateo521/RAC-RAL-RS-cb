
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Envios.h"
#include "RAC.h"
/*
#include "RAL.h"
#include "RS.h"
*/
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

    LecturaOperaciones();

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

                            break;
                        case 2:
                            system("cls");
                            printf("Rebalse Abierto Cuadratico (RAC):\n");


                            break;
                        case 3:
                            system("cls");
                            printf("Rebalse Separado (RS):\n");

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
int LecturaOperaciones()
{

    // Declaraciones e inicializaciones
    int respuesta = 2, alta=0,baja=0,evocar=0;
    Envio aux;
    FILE* fp;

    if ((fp = fopen(/*"Operaciones-Envios.txt"*/"Operaciones-Envios.txt", "r")) == NULL)
    {
        printf("No se pudo abrir el archivo");
        return 0;
    }
    else
    {
        int codigoOperador=0, contadorEnvios=0,i;
        while (!(feof(fp))&&contadorEnvios<=MAX_Envios)
        {


            fscanf(fp, "%d", &codigoOperador);
            fscanf(fp, " %[^\n]", aux.codigo);
             for(i=0;i<=8;i++){
                aux.codigo[i]=toupper(aux.codigo[i]);
            }
            if (codigoOperador == 1 || codigoOperador == 2)
            {

                // Leer y procesar los datos para Alta o Baja
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

                // Llama a la funci n correspondiente para alta o baja en las estructuras
                if(codigoOperador == 1)
                {
                  // AltaRAL(aux);
/*
                        printf("%d\n" , Hashing(aux.codigo,300));
*/
                }
                if(codigoOperador == 2)
                {



                }

            }
            else if (codigoOperador == 3)
            {

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
