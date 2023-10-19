
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Envios.h"
#include "RAC.h"

#include "RAL.h"
#include "RS.h"


// Resultados de la comparación de estructuras de datos:
//   1. Rebalse Abierto Lineal (RAL)
//   2. Rebalse Abierto Cuadrático (RAC)
//   3. Rebalse Separado (RS)
// - Conclusiones:
//   - RAL y RAC superan a RS en términos de eficiencia.
//   - RAL y RAC muestran un mejor rendimiento en términos de evocaciones exitosas y fallidas.
//   - RS tiene un rendimiento deficiente en términos de evocaciones exitosas y especialmente evocaciones fallidas.
// - Resultados obtenidos:
//   Max.Ev.Ex | Med.Ev.Ex | Max.Ev.Fr | Med.Ev.Fr |
//   RAL: 5.00  | 0.68      | 5.00     | 1.00     |
//   RAC: 6.00  | 0.72      | 4.00     | 1.00     |
//   RS:  60.00 | 0.72      | 43.00    | 31.55    |


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

    int opcion, submenu_opcion;


rac RAC[MaxEnviosRAC];
initRAC(RAC);


rs RS;
initRS(&RS);

ral RAL[MaxEnviosRAL];
initRAL(RAL);


   LecturaOperaciones(&RAC, &RAL, &RS);
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



                printf("\t Max.Ev.Ex | Med.Ev.Ex | Max.Ev.Fr | Med.Ev.Fr|\n");
                   printf("   RAL::");
               printf(" %0.2f |      %0.2f |       %0.2f |      %0.2f |\n", EvocarExitosoMaximoRAL,(temporal_ERAL/CantEvocarExitosoRAL), EvocarFracasoMaximoRAL , (temporal_FRAL/CantEvocarFracasoRAL) );
                printf("-----------------------------------------------------------------\n");
                printf("   RAC::");
                printf(" %0.2f |      %0.2f |      %0.2f |        %0.2f |\n", EvocarExitosoMaximoRAC ,(temporal_ERAC/CantEvocarExitosoRAC), EvocarFracasoMaximoRAC , (temporal_FRAC/CantEvocarFracasoRAC) );
                printf("-----------------------------------------------------------------\n");
                 printf("   RS::");
               printf(" %0.2f |      %0.2f |      %0.2f |        %0.2f |\n", EvocarExitosoMaximoRS ,(temporal_ERAC/CantEvocarExitosoRS), EvocarFracasoMaximoRS , (temporal_FRS/CantEvocarFracasoRS) );
                printf("------------------------------------------------------------------\n");

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




                   AltaRAC(RAC,aux);
                   AltaRAL(RAL,aux);

                 AltaRS(RS, aux);

                }
               else if(codigoOperador == 2)
                {

            BajaRAC(RAC,aux);


             BajaRAL(RAL,aux);

                BajaRS(RS, aux);
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
