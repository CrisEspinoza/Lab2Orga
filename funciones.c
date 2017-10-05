#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "struct.h"

// Funciones que leen los archivos

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

/*
- Entrada: Recibe como parametro una estructura informacion y la cantidad de lineas del archivo uno.
- Salida: Entrega como salida la misma estructura recibida como parametro.
- Procedimiento: Se encarga de inicializar cada una de los atributos que contiene la estructura informacion
que es recibida como parametro.
 */

void inicializarMemoriaParaInstrucciones(Informacion *informacion, int cantidadLineas)
{   
    int i ;

    informacion->instrucciones = (Instruccion*)malloc(sizeof(Instruccion)*cantidadLineas);

    for (i = 0; i < cantidadLineas; i++)
    {
        informacion->instrucciones[i].instruccion = (char*)malloc(sizeof(char)*100);
        informacion->instrucciones[i].lineaDeControl = (LineaDeControl*)malloc(sizeof(LineaDeControl));
        informacion->instrucciones[i].lineaDeControl->Estado = (char*)malloc(sizeof(char)*100);
        informacion->instrucciones[i].lineaDeControl->ALUOp = (char*)malloc(sizeof(char)*100);
        informacion->instrucciones[i].rt = (char*)malloc(sizeof(char)*10);
        informacion->instrucciones[i].rs = (char*)malloc(sizeof(char)*10);
        informacion->instrucciones[i].rd = (char*)malloc(sizeof(char)*10);
    }

    for (i = 0; i < cantidadLineas; i++)
    {
        informacion->etiqueta[i].label = (char*)malloc(sizeof(char)*50);
    }
}

// Funciones que hacen los calculos de los registros obtenidos  

/*
- Entrada: Funcion que recibe en nombre del registro.
- Salida: Entrega la posicion del registro que se recibe como parametro.
- Procesimiento: Se encarga de buscar la ubicacion que tiene el registro dentro de los registros.
 */

int obtenerPosicionReg(char* registro)
{
    int i;

    for(i = 0; i < 32 ; i++)
    {
        if(strcmp(registroMars[i],registro) == 0)
        {
            return i;
        }
    }

    return -1;
} 

/*
- Entrada: Funcion que recibe como parametro el nombre de la etiqueta y la estructura informacion.
- Salida: Entrega la posicion de la etiqueta.
- Procedimiento: Se encarga de buscar la etiquera dentro de las instrucciones que fueron leidas desde el archivo 
numer uno, para luego entregar dicho numero.
 */

int buscarPosicionEtiqueta(char* etiqueta, Informacion *info)
{
    int i;

    for(i = 0; i < (info->cantidadDeInstrucciones + 1 ); i++)
    {   
        if(strcmp(etiqueta,info->etiqueta[i].label) == 0)
        {   
            return i;
        }
    }
    return -1;
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros rs y rt y realizando la suma de ellos 
y asi guardando el resultado en rd.
 */

void add (Informacion *info , Instruccion *instruccion)
{
    int posicionRt;
    int posicionRs;
    int posicionRd;

    posicionRt = obtenerPosicionReg(instruccion->rt);
    posicionRs = obtenerPosicionReg(instruccion->rs);
    posicionRd = obtenerPosicionReg(instruccion->rd);

    info->registros[posicionRd] = info->registros[posicionRs] + info->registros[posicionRt];
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros rs y rt y realizando la resta de ellos 
y asi guardando el resultado en rd.
 */

void sub (Informacion *info , Instruccion *instruccion)
{
    int posicionRt;
    int posicionRs;
    int posicionRd;
    posicionRt = obtenerPosicionReg(instruccion->rt);
    posicionRs = obtenerPosicionReg(instruccion->rs);
    posicionRd = obtenerPosicionReg(instruccion->rd);

    info->registros[posicionRd] = info->registros[posicionRs] - info->registros[posicionRt];
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros rs y inmediato y realizando la resta de ellos 
y asi guardando el resultado en rd.
 */

void subi (Informacion *info , Instruccion *instruccion)
{
    int posicionRt;
    int posicionRs;
    posicionRt = obtenerPosicionReg(instruccion->rt);
    posicionRs = obtenerPosicionReg(instruccion->rs);

    info->registros[posicionRt] = info->registros[posicionRs] - instruccion->inmediato;
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros rs y inmediato y realizando la suma de ellos 
y asi guardando el resultado en rd.
 */

void addi (Informacion *info , Instruccion *instruccion)
{
    int posicionRt;
    int posicionRs;
    posicionRt = obtenerPosicionReg(instruccion->rt);
    posicionRs = obtenerPosicionReg(instruccion->rs);

    info->registros[posicionRt] = info->registros[posicionRs] + instruccion->inmediato;
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros rs y rt y realizando la multiplicacíon de ellos 
y asi guardando el resultado en rd.
 */

void mul (Informacion *info , Instruccion *instruccion)
{
    int posicionRt;
    int posicionRs;
    int posicionRd;
    posicionRt = obtenerPosicionReg(instruccion->rt);
    posicionRs = obtenerPosicionReg(instruccion->rs);
    posicionRd = obtenerPosicionReg(instruccion->rd);

    info->registros[posicionRd] = info->registros[posicionRs] * info->registros[posicionRt];
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros rs y rt y realizando la division de ellos 
y asi guardando el resultado en rd.
 */

void divi (Informacion *info , Instruccion *instruccion)
{
    int posicionRt;
    int posicionRs;
    int posicionRd;
    posicionRt = obtenerPosicionReg(instruccion->rt);
    posicionRs = obtenerPosicionReg(instruccion->rs);
    posicionRd = obtenerPosicionReg(instruccion->rd);

    info->registros[posicionRd] = info->registros[posicionRs] / info->registros[posicionRt];
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: Entrega el valor de donde debe realizar el salto la funcion.
- Procedimiento: Se encarga de concatenar el nombre del label con un ':', para que asi luego ocupe el llamado a la funcion 
buscarPosicionEtiqueta y entregue el numero de donde se encuentra
 */

int jump(Informacion *info, Instruccion *instruccion)
{   
    int PC;
    char *etiqueta = (char*)malloc(sizeof(char)*100);
    strcpy(etiqueta,instruccion->rd);
    strcat(etiqueta,":");
    PC = buscarPosicionEtiqueta(etiqueta, info);

    return PC;
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: Entrega un 1 si se cumple la condicion y un 0 si esta no se cumple.
- Procedimiento: Se encarga de verificar si la condición de los registro se cumple o no, para asi tomar la decision
del valor a que retornara.
 */

int beq(Informacion *info, Instruccion *instruccion)
{             
    int posicionRt;
    int posicionRs;

    int PC;

    posicionRt = obtenerPosicionReg(instruccion->rt);
    posicionRs = obtenerPosicionReg(instruccion->rs);

    //SI CUMPLE CONDICIÓN
    if(info->registros[posicionRs] == info->registros[posicionRt])
    {   
        char *etiqueta = (char*)malloc(sizeof(char)*100);
        strcpy(etiqueta,instruccion->rd);
        strcat(etiqueta,":");

        PC = buscarPosicionEtiqueta(etiqueta, info);
    
        return 1;
    }

    return 0; 
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros inmediato y la direccion, para asi luego buscar
el valor del registro con dicho valor y asi guardarlo en el registro correspondiente.
 */

void lw(Informacion *info, Instruccion *instruccion)
{
    int inmediato;
    int direccion;
    int posRegistro;

    if(strcmp(instruccion->rs, "$sp") == 0)
    {
        inmediato = instruccion->inmediato;
        direccion = (info->registros[29])/4;
        direccion = inmediato + direccion;
        posRegistro = obtenerPosicionReg(instruccion->rt);

        info->registros[posRegistro] = info->memoria[direccion];
    }
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros inmediato y la direccion, para asi luego buscar
el valor del registro con dicho valor y asi guardarlo en la memoria correspondiente.
 */

void sw(Informacion *info, Instruccion *instruccion)
{   
    int inmediato;
    int direccion;
    int posRegistro;

    if(strcmp(instruccion->rs, "$sp") == 0)
    {
        inmediato = instruccion->inmediato;
        direccion = (info->registros[29])/4;
        direccion = inmediato + direccion;
        posRegistro = obtenerPosicionReg(instruccion->rt);

        info->memoria[direccion] = info->registros[posRegistro];
    }
}

/*
- Entrada: Funcion que recibe como parametro una lista y el largo de ella.
- Salida: -
- Procedimiento: Se encarga de mostrar las lineas de control que contiene la lista.
 */

void mostrar(Instruccion* lista, int largo)
{
    int j;
    for (j = 0; j < largo; j++)
    {
        printf("PC : %d ",lista[j].lineaDeControl->PC);
        printf("RegDst : %c ",lista[j].lineaDeControl->RegDst);
        printf("Jump : %c ",lista[j].lineaDeControl->Jump);
        printf("Branch : %c ",lista[j].lineaDeControl->Branch);
        printf("MemRead : %c ",lista[j].lineaDeControl->MemRead);
        printf("MemToReg : %c ",lista[j].lineaDeControl->MemToReg);
        printf("ALUOp : %s ",lista[j].lineaDeControl->ALUOp);
        printf("MemWrite : %c ",lista[j].lineaDeControl->MemWrite);
        printf("ALUSrc : %c ",lista[j].lineaDeControl->ALUSrc);
        printf("RegWrite : %c \n",lista[j].lineaDeControl->RegWrite);
        //printf("%d\n",j );
    }
}

// Lineas de control para las funciones

/*
- Entrada: Funcion que recibe como parametro el nombre de la instruccion y el PC.
- Salida: Se encarga de entregar la linea de control correspondiente al nombre de la instruccion dada.
- Procedimiento: Se encarga de verificar el nombre de la instruccion y otorgarle las lienas de control que le corresponden.
 */

void asignarLineasDeControl (Informacion* info,char* instruccion, int PC)
{
    if (
        !strcmp(instruccion,"add") ||
        !strcmp(instruccion,"sub") ||
        !strcmp(instruccion,"mul") ||
        !strcmp(instruccion,"div")
        ){
            info->instrucciones[PC].lineaDeControl->PC = PC;
            info->instrucciones[PC].lineaDeControl->RegDst = '1';
            info->instrucciones[PC].lineaDeControl->Jump = '0';
            info->instrucciones[PC].lineaDeControl->Branch = '0';
            info->instrucciones[PC].lineaDeControl->MemRead = '0';
            info->instrucciones[PC].lineaDeControl->MemToReg = '0';
            strcpy(info->instrucciones[PC].lineaDeControl->ALUOp , "10");
            info->instrucciones[PC].lineaDeControl->MemWrite = '0';
            info->instrucciones[PC].lineaDeControl->ALUSrc = '0';
            info->instrucciones[PC].lineaDeControl->RegWrite = '1';
    }

    else if (!strcmp(instruccion,"addi"))
    {
            info->instrucciones[PC].lineaDeControl->PC = PC;
            info->instrucciones[PC].lineaDeControl->RegDst = '0';
            info->instrucciones[PC].lineaDeControl->Jump = '0';
            info->instrucciones[PC].lineaDeControl->Branch = '0';
            info->instrucciones[PC].lineaDeControl->MemRead = '0';
            info->instrucciones[PC].lineaDeControl->MemToReg = '0';
            strcpy(info->instrucciones[PC].lineaDeControl->ALUOp , "00");
            info->instrucciones[PC].lineaDeControl->MemWrite = '0';
            info->instrucciones[PC].lineaDeControl->ALUSrc = '1';
            info->instrucciones[PC].lineaDeControl->RegWrite = '1';
    }

    else if (!strcmp(instruccion,"subi"))
    {
            info->instrucciones[PC].lineaDeControl->PC = PC;
            info->instrucciones[PC].lineaDeControl->RegDst = '0';
            info->instrucciones[PC].lineaDeControl->Jump = '0';
            info->instrucciones[PC].lineaDeControl->Branch = '0';
            info->instrucciones[PC].lineaDeControl->MemRead = '0';
            info->instrucciones[PC].lineaDeControl->MemToReg = '0';
            strcpy(info->instrucciones[PC].lineaDeControl->ALUOp , "01");
            info->instrucciones[PC].lineaDeControl->MemWrite = '0';
            info->instrucciones[PC].lineaDeControl->ALUSrc = '1';
            info->instrucciones[PC].lineaDeControl->RegWrite = '1';
    }

    else if (
        !strcmp(instruccion,"beq")
        ){
            info->instrucciones[PC].lineaDeControl->PC = PC;
            info->instrucciones[PC].lineaDeControl->RegDst = 'x';
            info->instrucciones[PC].lineaDeControl->Jump = '0';
            info->instrucciones[PC].lineaDeControl->Branch = '1';
            info->instrucciones[PC].lineaDeControl->MemRead = '0';
            info->instrucciones[PC].lineaDeControl->MemToReg = 'x';
            strcpy(info->instrucciones[PC].lineaDeControl->ALUOp , "01");
            info->instrucciones[PC].lineaDeControl->MemWrite = '0';
            info->instrucciones[PC].lineaDeControl->ALUSrc = '0';
            info->instrucciones[PC].lineaDeControl->RegWrite = '0';
    }

    else if (
        !strcmp(instruccion,"j")
        ){
            info->instrucciones[PC].lineaDeControl->PC = PC;
            info->instrucciones[PC].lineaDeControl->RegDst = 'x';
            info->instrucciones[PC].lineaDeControl->Jump = '1';
            info->instrucciones[PC].lineaDeControl->Branch = 'x';
            info->instrucciones[PC].lineaDeControl->MemRead = '0';
            info->instrucciones[PC].lineaDeControl->MemToReg = 'x';
            strcpy(info->instrucciones[PC].lineaDeControl->ALUOp , "xx");
            info->instrucciones[PC].lineaDeControl->MemWrite = '0';
            info->instrucciones[PC].lineaDeControl->ALUSrc = 'x';
            info->instrucciones[PC].lineaDeControl->RegWrite = '0';
    }

    else if (
        !strcmp(instruccion,"lw")
        ){
            info->instrucciones[PC].lineaDeControl->PC = PC;
            info->instrucciones[PC].lineaDeControl->RegDst = '0';
            info->instrucciones[PC].lineaDeControl->Jump = '0';
            info->instrucciones[PC].lineaDeControl->Branch = '0';
            info->instrucciones[PC].lineaDeControl->MemRead = '1';
            info->instrucciones[PC].lineaDeControl->MemToReg = '1';
            strcpy(info->instrucciones[PC].lineaDeControl->ALUOp , "00");
            info->instrucciones[PC].lineaDeControl->MemWrite = '0';
            info->instrucciones[PC].lineaDeControl->ALUSrc = '1';
            info->instrucciones[PC].lineaDeControl->RegWrite = '1';
    }

    else if (
        !strcmp(instruccion,"sw")
        ){
            info->instrucciones[PC].lineaDeControl->PC = PC;
            info->instrucciones[PC].lineaDeControl->RegDst = 'x';
            info->instrucciones[PC].lineaDeControl->Jump = '0';
            info->instrucciones[PC].lineaDeControl->Branch = '0';
            info->instrucciones[PC].lineaDeControl->MemRead = '0';
            info->instrucciones[PC].lineaDeControl->MemToReg = 'x';
            strcpy(info->instrucciones[PC].lineaDeControl->ALUOp , "00");
            info->instrucciones[PC].lineaDeControl->MemWrite = '1';
            info->instrucciones[PC].lineaDeControl->ALUSrc = '1';
            info->instrucciones[PC].lineaDeControl->RegWrite = '0';
    }

}

/*
- Entrada: -
- Salida: Entrega una lista inicializada.
- Procedimiento: Se encarga de pedir memoria para la ista y iniciarlizar cada uno de los parametros que cotiene la estructura.
 */

Lista* crearLista() // Creamos la lista nueva 
{
    Lista* lista = (Lista*)malloc(sizeof(Lista)); // Pedimos memoria para la nueva lista 
    lista->lineaTraza = NULL;
    lista->largo = 0 ; // El largo de la lista es igual a "0".
    return lista; // Se retorna la lista creada
}

/*
- Entrada: Funcion que recibe como parametro una lista y una linea de control.
- Salida: Entrega la lista.
- Procedimiento: Se encarga de agregar la linea de control reciida como parametro a la lista que se tiene, ademas de 
aumentar el tamaño de esta lista.
 */

Lista* agregarNodo(Lista* lista , LineaDeControl* aux)
{
    if(lista->largo == 0)
    {
        lista->lineaTraza = (LineaDeControl*)malloc(sizeof(LineaDeControl));
        lista->lineaTraza[0] = *aux;
    }
    else
    {
        lista->lineaTraza = (LineaDeControl*)realloc(lista->lineaTraza, (lista->largo + 1) * sizeof (LineaDeControl)); // Pedimos mas memoria para el arreglo creado
        lista->lineaTraza[lista->largo] = *aux; // Agregamos el nodo que se desea agregar, luego de haber solicitado memoria
    }
    lista->largo++; // aumnetamos el largo de la lista de arreglos
    return lista;
}