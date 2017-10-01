
// LABORATORIO 1 DE ORGA 

// Bibliotecas a utilizar
#include <stdio.h>
#include "funciones.c"
#include <string.h>
#include <locale.h>
#include <time.h>

int main()
{    
    int opcion,contador,instrucciones;
    int bandera = 0;
    char archivoEntrada[50];
    char archivoSalida[50];
    char archivoLineasDeControl[50];
    Informacion* info = (Informacion*)malloc(sizeof(Informacion));
    LineaDeControl* lineasControlDadas;

    do
    {
        printf( "\n   1. Ingrese el nombre del archivo de instrucciones de mips");
        printf( "\n   2. Ingrese el nombre del archivo de lineas de control");
        printf( "\n   3. Realizar la salida del programa");
        printf( "\n   4. Creditos");
        printf( "\n   5. Salir" );
        printf( "\n\n   Introduzca opcion (1-5): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: printf("Ingrese nombre del archivo a leer\n");
                    scanf("%s",archivoEntrada);            
                    instrucciones = contarLineas(archivoEntrada);
                    info = leerInstrucciones(archivoEntrada,instrucciones);
                    bandera++;
                    break;

            case 2: printf("Ingrese nombre del archivo de lineas de control\n");
                    scanf("%s",archivoLineasDeControl); 
                    contador = contarLineas(archivoLineasDeControl);
                    lineasControlDadas = leerLineaDeControl(archivoLineasDeControl,contador);
                    bandera++;
                    break;

            case 3: if (bandera >= 1)
                    { 
                        traza(info, info->instrucciones,archivoSalida,lineasControlDadas);
                    }
                    else
                    {
                        printf("Primero tiene que cargar la opcion numero 1 y 2, para poder realizar esta opcion\n");
                    }
                    break;

            case 4: printf(" * Autor: CRISTIAN EDUARDO ESPINOZA SILVA \n ");
                    printf(" * Universidad santiago de chile \n");
                    break;
        }

    }while(opcion!=5);

    return 0;
}