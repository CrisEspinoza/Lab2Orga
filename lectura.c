#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "struct.h"

/*
- Entrada: Recibe como entrada el nombre del archivo.
- Salida: Entrega la cantidad de lineas del archivo.
- Procedimiento: Se preocupa de contar las lineas del archivo.
 */
int contarLineas(char nombre[])
{
    FILE *archivo;
    archivo = fopen(nombre, "r");
    char *string = (char*)malloc(sizeof(char)*100);
    int contador = 0;

    if(archivo == NULL)
    {
        printf("Error al abrir archivo \n");
        return 0;
    }
    
    while(!feof(archivo)) // Que lea el archivo siempre y cuando no sea un salto de linea
    {
        string = fgets(string, 100, archivo);
        contador++;
    }

    fclose(archivo);
    //printf("el numero de lineas es: %d\n", contador);
    return contador;
}

/*
- Entrada: Recibe como entrada el nombre del archivo.
- Salida: Entrega la cantidad de lineas del archivo.
- Procedimiento: Se preocupa de leer los valores de los registros
 */
Informacion* leerRegistros(Informacion* info,char nombre[])
{
    FILE *archivo;
    archivo = fopen(nombre, "r");
    char *instruccion = (char*)malloc(sizeof(char)*100);
    int valor;
    int contador = 0;

    if(archivo == NULL)
    {
        printf("Error al abrir archivo \n");
        return 0;
    }
    
    while(!feof(archivo)) // Que lea el archivo siempre y cuando no sea un salto de linea
    {
        fscanf(archivo,"%s %d", instruccion, &valor);
        //printf("%d\n",valor );
        info->registros[contador] = valor;
        contador++;
    }

    int j;

    for (j = 0; j < 32; j++)
    {
        printf("El registro %d es : %d\n", j,info->registros[j] );    
    }

    fclose(archivo);
    //printf("el numero de lineas es: %d\n", contador);
    return info;
}

/*
- Entrada: Recibe como parametro el nombre y la cantidad de lineas del archivo.
- Salida: Entrega las instrucciones leidas del archivo.
- Procedimiento: Se encarga de almacenar cada una de las instrucciones que son leidas del archivo uno en una
estructura llamada informacion que contiene a toda las instrucciones que estan contenidas en el archivo uno.
 */

Informacion* leerInstrucciones(char nombre[], int numeroDeLineas)
{
    FILE *archivo; // Declaramos un puntero File para poder leer el archivo de entrada.

    archivo = fopen(nombre, "r"); // Estamos abriendo el archivo en modo lectura

    Informacion* info = (Informacion*)malloc(sizeof(Informacion)); // Declaramos un variable de tipo de la structura tablero.

    //Verificamos si el archivo se encuentra nulo
    if( archivo == NULL)
    {
        printf("Error al abrir archivo \n");
        return 0;
    }

    inicializarMemoriaParaInstrucciones(info,numeroDeLineas);
    
    int posicionArreglo = 0;

    while(!feof(archivo)) // Que lea el archivo siempre y cuando no sea un salto de linea
    {
        char *instruccion = (char*)malloc(sizeof(char)*6);
        fscanf(archivo,"%s ", instruccion);
        asignarLineasDeControl(info,instruccion,posicionArreglo);
        //printf("%d\n", posicionArreglo );

        if(strcmp(instruccion, "add") == 0 || strcmp(instruccion, "sub") == 0 
            || strcmp(instruccion, "mul") == 0 || strcmp(instruccion, "div") == 0 )
        {
            char *rt = (char*)malloc(sizeof(char)*10);
            char *rs = (char*)malloc(sizeof(char)*10);
            char *rd = (char*)malloc(sizeof(char)*10);
            fscanf(archivo,"%[^','], %[^','], %s", rd, rs, rt);
            
            info->instrucciones[posicionArreglo].instruccion = instruccion;
            info->instrucciones[posicionArreglo].rd = rd;
            info->instrucciones[posicionArreglo].rs = rs;
            info->instrucciones[posicionArreglo].rt = rt;
            info->instrucciones[posicionArreglo].PC = posicionArreglo;
            posicionArreglo++;
            info->cantidadDeInstrucciones = posicionArreglo;
            printf("%s %s %s \n",  info->instrucciones[posicionArreglo-1].rt, info->instrucciones[posicionArreglo-1].rs, info->instrucciones[posicionArreglo-1].rd );
        }

        else if(strcmp(instruccion, "addi") == 0 || strcmp(instruccion, "subi") == 0 )
        {
            char *rt = (char*)malloc(sizeof(char)*10);
            char *rs = (char*)malloc(sizeof(char)*10);
            int inmediato;
            fscanf(archivo,"%[^','], %[^','], %d", rt, rs, &inmediato);
            
            info->instrucciones[posicionArreglo].instruccion = instruccion;
            info->instrucciones[posicionArreglo].inmediato = inmediato;
            info->instrucciones[posicionArreglo].rs = rs;
            info->instrucciones[posicionArreglo].rt = rt;
            info->instrucciones[posicionArreglo].PC = posicionArreglo;
            posicionArreglo++;
            info->cantidadDeInstrucciones = posicionArreglo;
            printf("%s %s %d \n",  info->instrucciones[posicionArreglo-1].rt, info->instrucciones[posicionArreglo-1].rs, info->instrucciones[posicionArreglo-1].inmediato);
        }

        else if(strcmp(instruccion, "beq") == 0)
        {
            char *rt = (char*)malloc(sizeof(char)*10);
            char *rs = (char*)malloc(sizeof(char)*10);
            char *label = (char*)malloc(sizeof(char)*10);
            fscanf(archivo,"%[^','], %[^','], %s", rs, rt, label);
            
            info->instrucciones[posicionArreglo].instruccion = instruccion;
            info->instrucciones[posicionArreglo].rd = label;
            info->instrucciones[posicionArreglo].rs = rs;
            info->instrucciones[posicionArreglo].rt = rt;
            info->instrucciones[posicionArreglo].PC = posicionArreglo;
            posicionArreglo++;
            info->cantidadDeInstrucciones = posicionArreglo;
            printf("%s %s %s \n",  info->instrucciones[posicionArreglo-1].rt, info->instrucciones[posicionArreglo-1].rs, info->instrucciones[posicionArreglo-1].rd );
        }

        else if(strcmp(instruccion, "j") == 0)
        {
            char *label = (char*)malloc(sizeof(char)*10);
            fscanf(archivo,"%s",label);            
            info->instrucciones[posicionArreglo].instruccion = instruccion;
            info->instrucciones[posicionArreglo].rd = label;
            info->instrucciones[posicionArreglo].PC = posicionArreglo;
            posicionArreglo++;
            info->cantidadDeInstrucciones = posicionArreglo;
            printf("%s \n",  info->instrucciones[posicionArreglo-1].rd );
        }

        else if(strcmp(instruccion, "sw") == 0 || strcmp(instruccion, "lw") == 0)
        {
            char *rt = (char*)malloc(sizeof(char)*10);
            char *rs = (char*)malloc(sizeof(char)*10);
            int inmediato;
            fscanf(archivo,"%[^','], %d(%[^')'])", rt, &inmediato, rs);
            
            info->instrucciones[posicionArreglo].instruccion = instruccion;
            info->instrucciones[posicionArreglo].inmediato = inmediato;
            info->instrucciones[posicionArreglo].rs = rs;
            info->instrucciones[posicionArreglo].rt = rt;
            info->instrucciones[posicionArreglo].PC = posicionArreglo;
            posicionArreglo++;
            info->cantidadDeInstrucciones = posicionArreglo;
            printf("%s %s %d \n",  info->instrucciones[posicionArreglo-1].rt, info->instrucciones[posicionArreglo-1].rs, info->instrucciones[posicionArreglo-1].inmediato );
        }

        else if(instruccion[strlen(instruccion)-1] == ':')
        { 
            info->etiqueta[posicionArreglo].label = instruccion;
            info->etiqueta[posicionArreglo].PC = posicionArreglo;
            //printf("%s\n",instruccion );
        }

    }

    fclose(archivo); // Cerramos el archivo
 
    return info; //Retornamo la variable matriz, con el tablero contenido, el cual se leyó desde el archivo ingresado
}
