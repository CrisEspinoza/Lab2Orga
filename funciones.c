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
- Entrada: Recibe como entrada el nombre del archivo y la cantidad de lineas que tiene.
- Salida: Entrega las lineas de control leidas.
- Procedimiento: Se encarga de otorgar las lineas de control del archivo dos a las instrucciones leidas
en el archivo uno.
 */

LineaDeControl* leerLineaDeControl(char nombre[],int numeroDeLineas) 
{
    FILE *archivo; // Declaramos un puntero File para poder leer el archivo de entrada.

    archivo = fopen(nombre, "r"); // Estamos abriendo el archivo en modo lectura

    LineaDeControl *lineasControlDadas; // Declaramos un variable de tipo de la structura tablero.
    lineasControlDadas = (LineaDeControl*)malloc(sizeof(LineaDeControl)*(numeroDeLineas-1));
    
    char a1[10];
    int contador = 0;

    //Verificamos si el archivo se encuentra nulo
    if( archivo == NULL)
    {
        printf("Error al abrir archivo \n");
        return 0;
    }
    //printf("aca estot \n");

    fscanf(archivo, "%s %s %s %s %s %s %s %s %s ",a1,a1,a1,a1,a1,a1,a1,a1,a1);
    
    while(!feof(archivo)) // Que lea el archivo siempre y cuando no sea un salto de linea
    {
        //printf("GUARDO EN : %d\n",contador );
        lineasControlDadas[contador].ALUOp = (char*)malloc(sizeof(char)*2);
        lineasControlDadas[contador].PC = contador;

    	fscanf(archivo, "%c %c %c %c %c %s %c %c %c ",&lineasControlDadas[contador].RegDst,&lineasControlDadas[contador].Jump,
            &lineasControlDadas[contador].Branch,&lineasControlDadas[contador].MemRead,&lineasControlDadas[contador].MemToReg,
            lineasControlDadas[contador].ALUOp,&lineasControlDadas[contador].MemWrite,&lineasControlDadas[contador].ALUSrc,
            &lineasControlDadas[contador].RegWrite); 

        contador++;
    }

    fclose(archivo); // Cerramos el archivo
 
    return lineasControlDadas; //Retornamo la variable matriz, con el tablero contenido, el cual se leyó desde el archivo ingresado
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
        //printf("%d\n", posicionArreglo );

        if(strcmp(instruccion, "add") == 0)
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
            //printf("%s %s %s \n", rt,rs,rd );
        }

        else if(strcmp(instruccion, "addi") == 0)
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
            //printf("%s %s %d \n", rt,rs,inmediato);
        }

        else if(strcmp(instruccion, "subi") == 0)
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
            //printf("%s %s %d \n", rt,rs,inmediato);
        }

        else if(strcmp(instruccion, "sub") == 0)
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
            //printf("%s %s %s \n", rt,rs,rd );
        }

        else if(strcmp(instruccion, "mul") == 0)
        {
            //printf("entre aca:\n");
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
            //printf("%s %s %s \n", rt,rs,rd );
        }

        else if(strcmp(instruccion, "div") == 0)
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
            //printf("%s %s %s \n", rt,rs,rd );
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
            //printf("%s %s %s \n", rt,rs,label );
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
            //printf("%s \n", label );
        }

        else if(strcmp(instruccion, "sw") == 0)
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
            //printf("%s %s %d \n", rt,rs,inmediato );
        }

        else if(strcmp(instruccion, "lw") == 0)
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
            //printf("%s %s %d \n", rt,rs,inmediato );
        }

        else if(instruccion[strlen(instruccion)-1] == ':')
        {
            info->etiqueta[posicionArreglo].label = instruccion;
            info->etiqueta[posicionArreglo].PC = posicionArreglo;
            //printf("%s\n",instruccion );
        }

        //else{} //Por si el archivo viene con espacios .

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
        informacion->instrucciones[i].rt = (char*)malloc(sizeof(char)*10);
        informacion->instrucciones[i].rs = (char*)malloc(sizeof(char)*10);
        informacion->instrucciones[i].rd = (char*)malloc(sizeof(char)*10);
    }

    for (i = 0; i < 32; i++)
    {
        informacion->registros[i] = 0;
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
- Entrada: Funcion que recibe como parametro una lista.
- Salida: -
- Procedimiento: Se encarga de mostrar lo que se encuentra en la lista.
 */

void mostrarLineasDeControl(Lista* lista)
{
    int j;
    for (j = 0; j < lista->largo; j++)
    {
        printf("PC : %d ",lista->lineaTraza[j].PC);
        printf("RegDst : %c ",lista->lineaTraza[j].RegDst);
        printf("Jump : %c ",lista->lineaTraza[j].Jump);
        printf("Branch : %c ",lista->lineaTraza[j].Branch);
        printf("MemRead : %c ",lista->lineaTraza[j].MemRead);
        printf("MemToReg : %c ",lista->lineaTraza[j].MemToReg);
        printf("ALUOp : %s ",lista->lineaTraza[j].ALUOp);
        printf("MemWrite : %c ",lista->lineaTraza[j].MemWrite);
        printf("ALUSrc : %c ",lista->lineaTraza[j].ALUSrc);
        printf("RegWrite : %c \n",lista->lineaTraza[j].RegWrite);
        //printf("%d\n",j );
    }
}

/*
- Entrada: Funcion que recibe como parametro una lista y el largo de ella.
- Salida: -
- Procedimiento: Se encarga de mostrar las lineas de control que contiene la lista.
 */

void mostrar(LineaDeControl* lista, int largo)
{
    int j;
    for (j = 0; j < largo-1; j++)
    {
        printf("PC : %d ",lista[j].PC);
        printf("RegDst : %c ",lista[j].RegDst);
        printf("Jump : %c ",lista[j].Jump);
        printf("Branch : %c ",lista[j].Branch);
        printf("MemRead : %c ",lista[j].MemRead);
        printf("MemToReg : %c ",lista[j].MemToReg);
        printf("ALUOp : %s ",lista[j].ALUOp);
        printf("MemWrite : %c ",lista[j].MemWrite);
        printf("ALUSrc : %c ",lista[j].ALUSrc);
        printf("RegWrite : %c \n",lista[j].RegWrite);
        //printf("%d\n",j );
    }
}

/*
- Entrada: Funcion que recibe como parametro un puntero a info, un puntero a instrucciones, el nombre del archivo de salida ,
y una estructura de linea de econtrol.
- Salida: -
- Procedimiento: Se encarga de realizar la traza del programa, y ir verificando cada uno de los valores para poder asi tener los valores
de los registros actualizados y saber al momento de detener el programa.
 */

void traza(Informacion* info, Instruccion* instrucciones,char* nombreArchivoSalida, LineaDeControl* lineasControlDadas)
{
    //printf("1\n");
    FILE *salida;
    strcat(nombreArchivoSalida,".out");
    salida = fopen(nombreArchivoSalida,"w");
    //printf("2\n");
    Lista* lineasDeControl;
    lineasDeControl = crearLista(lineasDeControl);
    //printf("3\n");
    Lista* lineasDadas;
    lineasDadas = crearLista(lineasDadas);
    //printf("4\n");
    int i,j;

    //printf("%d\n",info->cantidadDeInstrucciones );
    
    for(i = 0 ; i < info->cantidadDeInstrucciones; i++)
    { 
        //printf("5\n");
        //printf("El nombre de la instruccion es: %s\n", info->instrucciones[i].instruccion );

        if(strcmp(info->instrucciones[i].instruccion,"add") == 0)
        {   
            add(info, &info->instrucciones[i]);
            lineasDeControl = agregarNodo(lineasDeControl,asignarLineasDeControl(info->instrucciones[i].instruccion,info->instrucciones[i].PC));
            //mostrarLineasDeControl(lineasDeControl);
        }

        else if(strcmp(info->instrucciones[i].instruccion,"sub") == 0)
        {   
            sub(info, &info->instrucciones[i]);
            lineasDeControl =  agregarNodo(lineasDeControl,asignarLineasDeControl(info->instrucciones[i].instruccion,info->instrucciones[i].PC));
            //mostrarLineasDeControl(lineasDeControl);           
        }

        else if(strcmp(info->instrucciones[i].instruccion,"addi") == 0)
        {   
            addi(info, &info->instrucciones[i]);
            lineasDeControl = agregarNodo(lineasDeControl,asignarLineasDeControl(info->instrucciones[i].instruccion,info->instrucciones[i].PC));
            //mostrarLineasDeControl(lineasDeControl);
        }

        else if(strcmp(info->instrucciones[i].instruccion,"subi") == 0)
        {   
            subi(info, &info->instrucciones[i]);
            lineasDeControl = agregarNodo(lineasDeControl,asignarLineasDeControl(info->instrucciones[i].instruccion,info->instrucciones[i].PC));
            //mostrarLineasDeControl(lineasDeControl);
        }

        else if(strcmp(info->instrucciones[i].instruccion,"mul") == 0)
        {   
            mul(info, &info->instrucciones[i]);
            lineasDeControl = agregarNodo(lineasDeControl,asignarLineasDeControl(info->instrucciones[i].instruccion,info->instrucciones[i].PC));
            //mostrarLineasDeControl(lineasDeControl);
        }

        else if(strcmp(info->instrucciones[i].instruccion,"div") == 0)
        {   
            divi(info, &info->instrucciones[i]);
            lineasDeControl = agregarNodo(lineasDeControl,asignarLineasDeControl(info->instrucciones[i].instruccion,info->instrucciones[i].PC));
            //mostrarLineasDeControl(lineasDeControl);
        }

        else if(strcmp(info->instrucciones[i].instruccion,"beq") == 0)
        {   
            int aux;
            aux = beq(info, &info->instrucciones[i]);

            lineasDeControl = agregarNodo(lineasDeControl,asignarLineasDeControl(info->instrucciones[i].instruccion,info->instrucciones[i].PC));
            //mostrarLineasDeControl(lineasDeControl);
            
            if(aux == 1)
            {   
                char *etiqueta = (char*)malloc(sizeof(char)*100);
                strcpy(etiqueta,info->instrucciones[i].rd);
                strcat(etiqueta,":");
                i = buscarPosicionEtiqueta(etiqueta,info) - 1;
            }
        }

        else if(strcmp(info->instrucciones[i].instruccion,"j") == 0)
        {   
            lineasDeControl = agregarNodo(lineasDeControl,asignarLineasDeControl(info->instrucciones[i].instruccion,info->instrucciones[i].PC));
            //mostrarLineasDeControl(lineasDeControl);
            i = jump(info, &info->instrucciones[i]);
            i--;
        }

        else if(strcmp(info->instrucciones[i].instruccion,"sw") == 0)
        {
            sw(info,&info->instrucciones[i]);
            lineasDeControl = agregarNodo(lineasDeControl,asignarLineasDeControl(info->instrucciones[i].instruccion,info->instrucciones[i].PC));
            //mostrarLineasDeControl(lineasDeControl);
        }

        else if(strcmp(info->instrucciones[i].instruccion,"lw") == 0)
        {
            lw(info,&info->instrucciones[i]);
            lineasDeControl = agregarNodo(lineasDeControl,asignarLineasDeControl(info->instrucciones[i].instruccion,info->instrucciones[i].PC));
            //mostrarLineasDeControl(lineasDeControl);
        }
    } 
    //mostrarLineasDeControl(lineasDeControl);
    realizarSalida(lineasDeControl,lineasControlDadas);
}

/*
- Entrada: Funcion que recibe como parametro una lista y las lineas de control del archivo que se entrega.
- Salida: -
- Procedimiento: Se encarga de verificar si las lineas de control que fueron obtenidas corresponden a las correctas, ademas de
indicar un error si estas contienen.
 */

void realizarSalida(Lista* lista,LineaDeControl* lineasControlDadas)
{
    int j ,i;
    int contador = 0;
    LineaDeControl* aux = (LineaDeControl*)malloc(sizeof(LineaDeControl)*lista->largo);
    
    FILE *archivo;


    for (j = 0; j < lista->largo ; j++)
    {
        i = lista->lineaTraza[j].PC;
        aux[j].ALUOp = (char*)malloc(sizeof(char)*2);
        aux[j].Estado = (char*)malloc(sizeof(char)*10);

        if (lista->lineaTraza[j].RegDst == lineasControlDadas[i].RegDst || lineasControlDadas[i].RegDst == 'x' || lista->lineaTraza[j].RegDst == 'x')
        {
            //printf("RegDst : - ");
            aux[j].RegDst = '-';
            contador++;
        }
        else
        {
            //printf("RegDst : %c ",lineasControlDadas[i].RegDst);
            aux[j].RegDst = lineasControlDadas[i].RegDst;
        }

        if (lista->lineaTraza[j].Jump == lineasControlDadas[i].Jump || lineasControlDadas[i].Jump == 'x' || lista->lineaTraza[j].Jump == 'x')
        {
            //printf("Jump : - ");
            aux[j].Jump = '-';
            contador++;
        }
        else
        {
            //printf("Jump : %c ",lineasControlDadas[i].Jump);
            aux[j].Jump = lineasControlDadas[i].Jump;
        }

        if (lista->lineaTraza[j].Branch == lineasControlDadas[i].Branch || lineasControlDadas[i].Branch == 'x' || lista->lineaTraza[j].Branch == 'x')
        {
            //printf("Branch : - ");
            aux[j].Branch = '-';
            contador++;
        }
        else
        {
            //printf("Branch : %c ",lineasControlDadas[i].Branch);
            aux[j].Branch = lineasControlDadas[i].Branch;
        }

        if (lista->lineaTraza[j].MemRead == lineasControlDadas[i].MemRead || lineasControlDadas[i].MemRead == 'x' || lista->lineaTraza[j].MemRead == 'x')
        {
            //printf("MemRead : - ");
            aux[j].MemRead = '-';
            contador++;
        }
        else
        {
            //printf("MemRead : %c ",lineasControlDadas[i].MemRead);
            aux[j].MemRead = lineasControlDadas[i].MemRead;
        }

        if (lista->lineaTraza[j].MemToReg == lineasControlDadas[i].MemToReg || lineasControlDadas[i].MemToReg == 'x' || lista->lineaTraza[j].MemToReg == 'x')
        {
            //printf("MemToReg : - ");
            aux[j].MemToReg = '-';
            contador++;
        }
        else
        {
            //printf("MemToReg : %c ",lineasControlDadas[i].MemToReg);
            aux[j].MemToReg = lineasControlDadas[i].MemToReg;
        }

        if (strcmp(lista->lineaTraza[j].ALUOp ,lineasControlDadas[i].ALUOp) == 0)
        {
            //printf("ALUOp : - ");
            aux[j].ALUOp = "-";
            contador++;
        }

        else if (lineasControlDadas[i].ALUOp[0] == lista->lineaTraza[j].ALUOp[0] && 
            lineasControlDadas[i].ALUOp[1] == 'x')
        {
            //printf("ALUOp : - ");
            aux[j].ALUOp = "-";
            contador++;
        }

        else if (lineasControlDadas[i].ALUOp[1] == lista->lineaTraza[j].ALUOp[1] && 
            lineasControlDadas[i].ALUOp[0] == 'x')
        {
            //printf("ALUOp : - ");
            aux[j].ALUOp = "-";
            contador++;
        }

        else if (lineasControlDadas[i].ALUOp[0] == 'x' && 
            lineasControlDadas[i].ALUOp[1] == 'x')
        {
            //printf("ALUOp : - ");
            aux[j].ALUOp = "-";
            contador++;
        }

        else
        {
            //printf("ALUOp : %s ",lineasControlDadas[i].ALUOp);
            aux[j].ALUOp = lineasControlDadas[i].ALUOp;
        }

        if (lista->lineaTraza[j].MemWrite == lineasControlDadas[i].MemWrite || lineasControlDadas[i].MemWrite == 'x' || lista->lineaTraza[j].MemWrite == 'x')
        {
            //printf("MemWrite : - ");
            aux[j].MemWrite = '-';
            contador++;
        }
        else
        {
            //printf("MemWrite : %c ",lineasControlDadas[i].MemWrite);
            aux[j].MemWrite = lineasControlDadas[i].MemWrite;
        }

        if (lista->lineaTraza[j].ALUSrc == lineasControlDadas[i].ALUSrc || lineasControlDadas[i].ALUSrc == 'x' || lista->lineaTraza[j].ALUSrc == 'x')
        {
            //printf("ALUSrc : - ");
            aux[j].ALUSrc = '-';
            contador++;
        }
        else
        {
            //printf("ALUSrc : %c ",lineasControlDadas[i].ALUSrc);
            aux[j].ALUSrc = lineasControlDadas[i].ALUSrc;
        }

        if (lista->lineaTraza[j].RegWrite == lineasControlDadas[i].RegWrite || lineasControlDadas[i].RegWrite == 'x' || lista->lineaTraza[j].RegWrite == 'x')
        {
            //printf("RegWrite : - ");
            aux[j].RegWrite = '-';
            contador++;
        }
        else
        {
            //printf("RegWrite : %c ",lineasControlDadas[i].RegWrite);
            aux[j].RegWrite = lineasControlDadas[i].RegWrite;
        }

        if (contador == 9)
        {
            strcpy(aux[j].Estado , "Correcto");
        }
        else
        {
            strcpy(aux[j].Estado , "Error");
        }
        contador = 0;
    }

    archivo = fopen("Salida.out", "w"); // Abrimos le archivo en modo escritura y que se cree si no exite el archivo nombrado
    
    fprintf(archivo, "Estado       RegDst    Jump    Branch     MemRead   MemToReg   ALUOp   MemWrite   ALUSrc   RegWrite ");
    fprintf(archivo, "\n");
    int z;

    for (z = 0 ; z < lista->largo ; z++)
    {
        //fprintf(archivo, "%c   %c   %c   %c   %c   %s   %c   %c   %c",aux[z].Estado,aux[z].RegDst,aux[z].Jump,aux[z].Branch, aux[z].MemRead, aux[z].MemToReg,aux[z].ALUOp,aux[z].MemWrite,aux[z].ALUSrc,aux[z].RegWrite);
        if ((strcmp(aux[z].Estado ,"Error") == 0))
        {
            fprintf(archivo,"%s\t\t",aux[z].Estado );
            fprintf(archivo,"%c\t",aux[z].RegDst);
            fprintf(archivo,"%c\t",aux[z].Jump);
            fprintf(archivo," %c\t",aux[z].Branch);
            fprintf(archivo,"    %c\t",aux[z].MemRead);
            fprintf(archivo,"  \t%c\t",aux[z].MemToReg);
            fprintf(archivo," %s\t",aux[z].ALUOp);
            fprintf(archivo,"  %c\t",aux[z].MemWrite);
            fprintf(archivo,"    %c\t",aux[z].ALUSrc);
            fprintf(archivo,"      %c",aux[z].RegWrite);
            fprintf(archivo,"\n");
        }
        else
        {
            fprintf(archivo,"%s\t",aux[z].Estado );
            fprintf(archivo,"\n");
        }
    }
    fclose(archivo); // Cerramos el archivo
}

// Lineas de control para las funciones

/*
- Entrada: Funcion que recibe como parametro el nombre de la instruccion y el PC.
- Salida: Se encarga de entregar la linea de control correspondiente al nombre de la instruccion dada.
- Procedimiento: Se encarga de verificar el nombre de la instruccion y otorgarle las lienas de control que le corresponden.
 */

LineaDeControl* asignarLineasDeControl (char* instruccion, int PC)
{
    LineaDeControl* aux = (LineaDeControl*)malloc(sizeof(LineaDeControl));
    aux->ALUOp = (char*)malloc(sizeof(char)*2);

    if (
        !strcmp(instruccion,"add") ||
        !strcmp(instruccion,"sub") ||
        !strcmp(instruccion,"mul") ||
        !strcmp(instruccion,"div")
        ){
            aux->PC = PC;
            aux->RegDst = '1';
            aux->Jump = '0';
            aux->Branch = '0';
            aux->MemRead = '0';
            aux->MemToReg = '0';
            strcpy(aux->ALUOp , "10");
            aux->MemWrite = '0';
            aux->ALUSrc = '0';
            aux->RegWrite = '1';
    }

    else if (!strcmp(instruccion,"addi"))
    {
            aux->PC = PC;
            aux->RegDst = '0';
            aux->Jump = '0';
            aux->Branch = '0';
            aux->MemRead = '0';
            aux->MemToReg = '0';
            strcpy(aux->ALUOp , "00");
            aux->MemWrite = '0';
            aux->ALUSrc = '1';
            aux->RegWrite = '1';
    }

    else if (!strcmp(instruccion,"subi"))
    {
            aux->PC = PC;
            aux->RegDst = '0';
            aux->Jump = '0';
            aux->Branch = '0';
            aux->MemRead = '0';
            aux->MemToReg = '0';
            strcpy(aux->ALUOp , "01");
            aux->MemWrite = '0';
            aux->ALUSrc = '1';
            aux->RegWrite = '1';
    }

    else if (
        !strcmp(instruccion,"beq")
        ){
            aux->PC = PC;
            aux->RegDst = 'x';
            aux->Jump = '0';
            aux->Branch = '1';
            aux->MemRead = '0';
            aux->MemToReg = 'x';
            strcpy(aux->ALUOp , "01");
            aux->MemWrite = '0';
            aux->ALUSrc = '0';
            aux->RegWrite = '0';
    }

    else if (
        !strcmp(instruccion,"j")
        ){
            aux->PC = PC;
            aux->RegDst = 'x';
            aux->Jump = '1';
            aux->Branch = 'x';
            aux->MemRead = '0';
            aux->MemToReg = 'x';
            strcpy(aux->ALUOp , "xx");
            aux->MemWrite = '0';
            aux->ALUSrc = 'x';
            aux->RegWrite = '0';
    }

    else if (
        !strcmp(instruccion,"lw")
        ){
            aux->PC = PC;
            aux->RegDst = '0';
            aux->Jump = '0';
            aux->Branch = '0';
            aux->MemRead = '1';
            aux->MemToReg = '1';
            strcpy(aux->ALUOp , "00");
            aux->MemWrite = '0';
            aux->ALUSrc = '1';
            aux->RegWrite = '1';
    }

    else if (
        !strcmp(instruccion,"sw")
        ){
            aux->PC = PC;
            aux->RegDst = 'x';
            aux->Jump = '0';
            aux->Branch = '0';
            aux->MemRead = '0';
            aux->MemToReg = 'x';
            strcpy(aux->ALUOp , "00");
            aux->MemWrite = '1';
            aux->ALUSrc = '1';
            aux->RegWrite = '0';
    }

    return aux;
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