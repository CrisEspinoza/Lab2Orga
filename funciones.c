#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "struct.h"


int INTRUCCIONESEJECUTADAS = 0;
int BANDERA = 0;

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
        printf("El registro %s es : %d\n", registroMars[j],info->registros[j] );    
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
    informacion->buffer = (Buffer*)malloc(sizeof(Buffer)*5);

    for (i = 0; i < cantidadLineas; i++)
    {
        informacion->instrucciones[i].instruccion = (char*)malloc(sizeof(char)*100);
        informacion->instrucciones[i].lineaDeControl = (LineaDeControl*)malloc(sizeof(LineaDeControl));
        informacion->instrucciones[i].lineaDeControl->ALUOp = (char*)malloc(sizeof(char)*100);
        informacion->instrucciones[i].rt = (char*)malloc(sizeof(char)*10);
        informacion->instrucciones[i].rs = (char*)malloc(sizeof(char)*10);
        informacion->instrucciones[i].rd = (char*)malloc(sizeof(char)*10);
        informacion->hazarDato = (char*)malloc(sizeof(char)*100);
        informacion->hazarControl = (char*)malloc(sizeof(char)*100);
    }

    for (i = 0; i < cantidadLineas; i++)
    {
        informacion->etiqueta[i].label = (char*)malloc(sizeof(char)*50);
    }

    for (i = 0; i < 5; i++)
    {
        informacion->buffer[i].instruccion = (Instruccion*)malloc(sizeof(Instruccion)); 
        informacion->buffer[i].instruccion->instruccion = (char*)malloc(sizeof(char)*100);
        informacion->buffer[i].instruccion->rt = (char*)malloc(sizeof(char)*100);
        informacion->buffer[i].instruccion->rd = (char*)malloc(sizeof(char)*100);
        informacion->buffer[i].instruccion->rs = (char*)malloc(sizeof(char)*100);   
        informacion->buffer[i].muxRegDs = (char*)malloc(sizeof(char)*100);      
        informacion->buffer[i].lineaDeControl = (LineaDeControl*)malloc(sizeof(LineaDeControl));
        informacion->buffer[i].lineaDeControl->ALUOp = (char*)malloc(sizeof(char)*10);
        informacion->buffer[i].register1 = (char*)malloc(sizeof(char)*100);        
        informacion->buffer[i].register2 = (char*)malloc(sizeof(char)*100);
        informacion->buffer[i].address = (char*)malloc(sizeof(char)*100);
        informacion->buffer[i].writeDataMem = (char*)malloc(sizeof(char)*100);
        informacion->buffer[i].writeRegister = (char*)malloc(sizeof(char)*100);
        informacion->buffer[i].rt = (char*)malloc(sizeof(char)*100);
        informacion->buffer[i].rd = (char*)malloc(sizeof(char)*100);
        informacion->buffer[i].rs = (char*)malloc(sizeof(char)*100);
        iniciarBuffer(&informacion->buffer[i]);
    }
}

LineaDeControl* resetearLineasControl(LineaDeControl* lineaDeControl)
{
    lineaDeControl->RegDst = '0';
    lineaDeControl->Jump = '0';
    lineaDeControl->Branch = '0';
    lineaDeControl->MemRead = '0';
    lineaDeControl->MemToReg = '0';
    strcpy(lineaDeControl->ALUOp , "00");
    lineaDeControl->MemWrite = '0';
    lineaDeControl->ALUSrc = '0';
    lineaDeControl->RegWrite = '0';

    return lineaDeControl;
}

Instruccion* inicializarIntrucciones(Instruccion* instruccion)
{
    instruccion->instruccion = "vacio";
    instruccion->rs = "";
    instruccion->rt = "";
    instruccion->rd = "";

    return instruccion;
}

void iniciarBuffer(Buffer* buffer)
{
    buffer->instruccion = inicializarIntrucciones(buffer->instruccion);
    buffer->lineaDeControl = resetearLineasControl(buffer->lineaDeControl);
    buffer->register1 = "";
    buffer->register2 = "";
    buffer->writeRegister = "";
    buffer->rd = "";
    buffer->rt = "";
    buffer->rs = "";
    buffer->muxRegDs = "";
    buffer->readData1Id = 0;
    buffer->readData2Id = 0;
    buffer->signoExtendido = 0; 
    buffer->posRegistro = 0;   
    buffer->ALU = 0;
    buffer->address = "";
    buffer->writeDataMem = "";
    buffer->readData1Mem = 0;
    buffer->writeDataWb = 0;
    buffer->zero = 0;
    buffer->aluResult = 0;
    buffer->addPc = 0;
    buffer->estado = 0;    
}

void mostrarBuffer(Buffer* buffer)
{
    printf("Entre a la cuncion \n");
    int j;
    for (j = 0; j < 4; j++)
    {
        printf("%s\n",buffer[j].instruccion->instruccion);
        printf("Los registros que estan en instruccion");
        printf("%s\n",buffer[j].instruccion->rs);
        printf("%s\n",buffer[j].instruccion->rt);
        printf("%s\n",buffer[j].instruccion->rd);
        printf("%s\n",buffer[j].muxRegDs);
        printf("Se acabo lo anterior\n");
        printf("%s\n",buffer[j].writeRegister);
        printf("%s\n",buffer[j].register1);
        printf("%s\n",buffer[j].rd);
        printf("%s\n",buffer[j].rt);
        printf("%s\n",buffer[j].rs);
        printf("%d\n",buffer[j].posRegistro);
        printf("%s\n",buffer[j].register2);
        printf("%d\n",buffer[j].readData1Id);
        printf("%d\n",buffer[j].readData2Id);
        printf("%d\n",buffer[j].signoExtendido);   
        printf("%d\n",buffer[j].ALU);
        printf("%s\n",buffer[j].address);
        printf("%s\n",buffer[j].writeDataMem);
        printf("%d\n",buffer[j].readData1Mem);
        printf("%d\n",buffer[j].estado);
        printf("%d\n",buffer[j].writeDataWb);
        printf("%d\n",buffer[j].zero);
        printf("%d\n",buffer[j].aluResult);
        printf("%d\n",buffer[j].addPc); 
        printf("Linas de control \n");
        printf("\n");
        printf("RegDst : %c ",buffer[j].lineaDeControl->RegDst);
        printf("Jump : %c ",buffer[j].lineaDeControl->Jump);
        printf("Branch : %c ",buffer[j].lineaDeControl->Branch);
        printf("MemRead : %c ",buffer[j].lineaDeControl->MemRead);
        printf("MemToReg : %c ",buffer[j].lineaDeControl->MemToReg);
        printf("ALUOp : %s ",buffer[j].lineaDeControl->ALUOp);
        printf("MemWrite : %c ",buffer[j].lineaDeControl->MemWrite);
        printf("ALUSrc : %c ",buffer[j].lineaDeControl->ALUSrc);
        printf("RegWrite : %c \n",buffer[j].lineaDeControl->RegWrite);
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

void mostrarLineasControl(LineaDeControl* aux)
{ 
    printf("Lineas de control \n");
    printf("RegDst : %c ",aux->RegDst);
    printf("Jump : %c ",aux->Jump);
    printf("Branch : %c ",aux->Branch);
    printf("MemRead : %c ",aux->MemRead);
    printf("MemToReg : %c ",aux->MemToReg);
    printf("ALUOp : %s ",aux->ALUOp);
    printf("MemWrite : %c ",aux->MemWrite);
    printf("ALUSrc : %c ",aux->ALUSrc);
    printf("RegWrite : %c \n",aux->RegWrite);
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros rs y rt y realizando la suma de ellos 
y asi guardando el resultado en rd.
 */

void add(Informacion *informacion, Instruccion *instruccion, int PC,int etapa) // listo 
{           
    int posrt;
    int posrs;
    int posrd;

    posrt = obtenerPosicionReg(instruccion->rt);
    posrs = obtenerPosicionReg(instruccion->rs);
    posrd = obtenerPosicionReg(instruccion->rd);

    
    if(etapa == 1) // ETAPA IF buffers[0] = IF/ID
    {   
        informacion->buffer[0].estado = 1;
        informacion->buffer[0].instruccion = instruccion;
        informacion->buffer[0].addPc = PC;

        printf("Instruccion IF/ID: %s \n", informacion->buffer[0].instruccion->instruccion);
    }

    else if(etapa == 2) //ETAPA ID buffers[1] = ID/EX
    {
        informacion->buffer[1] = informacion->buffer[0];
        // Etapa nueva 
        informacion->buffer[0].estado = 0;
        informacion->buffer[1].muxRegDs = informacion->buffer[1].instruccion->rd;
        informacion->buffer[1].rs = informacion->buffer[1].instruccion->rs;
        informacion->buffer[1].rt = informacion->buffer[1].instruccion->rt;
        informacion->buffer[1].rd = informacion->buffer[1].instruccion->rd;
        informacion->buffer[1].lineaDeControl = asignarLineasDeControl(informacion->buffer[1].instruccion->instruccion);
        informacion->buffer[1].writeRegister = informacion->buffer[0].instruccion->rd;
        informacion->buffer[1].readData1Id = informacion->registros[posrs];
        informacion->buffer[1].readData2Id = informacion->registros[posrt];

        printf("Instruccion ID/EX: %s %s %s %s \n", informacion->buffer[1].instruccion->instruccion,informacion->buffer[1].instruccion->rd , informacion->buffer[1].instruccion->rs, 
            informacion->buffer[1].instruccion->rt);
        printf("Instruccion ID/EX: %d %d \n", informacion->buffer[1].readData1Id , informacion->buffer[1].readData2Id);
        mostrarLineasControl(informacion->buffer[1].lineaDeControl);

    }
 
    else if(etapa == 3) //ETAPA EX buffers[2] = EX/MEM
    {   
        informacion->buffer[2] = informacion->buffer[1];
        informacion->buffer[1].estado = 0;
        // Etapa nueva 
        informacion->buffer[2].aluResult = informacion->buffer[2].readData1Id + informacion->buffer[2].readData2Id;

        printf("Instruccion EX/MEM: %s %s %s %s \n", informacion->buffer[2].instruccion->instruccion,informacion->buffer[2].instruccion->rd , informacion->buffer[2].instruccion->rs, 
            informacion->buffer[2].instruccion->rt);
        printf("Instruccion EX/MEM: Resultado: %d \n", informacion->buffer[2].aluResult);
        mostrarLineasControl(informacion->buffer[2].lineaDeControl);
    }

    else if(etapa == 4) //ETAPA MEM buffers[3] = MEM/WB
    {
        informacion->buffer[3] = informacion->buffer[2];
        informacion->buffer[2].estado = 0;
        //Etapa nueva         
        informacion->buffer[3].writeDataWb = informacion->buffer[3].aluResult;

        printf("Instruccion MEM/WB: %s %s %s %s \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rd , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->rt);
        printf("Instruccion MEM/WB: Resultado: %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].writeDataWb);
        mostrarLineasControl(informacion->buffer[3].lineaDeControl);
    }

    else if(etapa == 5) //ETAPA WB
    {
        informacion->buffer[4] = informacion->buffer[3];
        // Etapa nueva
        informacion->buffer[3].estado = 0;
        informacion->registros[posrd] = informacion->buffer[3].writeDataWb;
        printf("Instruccion WB: Numero a guardar: %d \n", informacion->buffer[3].writeDataWb);
        printf("Instruccion WB: Resultado: %d \n", informacion->registros[posrd]);

    }   
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros rs y rt y realizando la resta de ellos 
y asi guardando el resultado en rd.
 */

void sub(Informacion *informacion, Instruccion *instruccion, int PC,int etapa) // listo 
{           
    int posrt;
    int posrs;
    int posrd;

    posrt = obtenerPosicionReg(instruccion->rt);
    posrs = obtenerPosicionReg(instruccion->rs);
    posrd = obtenerPosicionReg(instruccion->rd);

    
    if(etapa == 1) // ETAPA IF buffers[0] = IF/ID
    {   
        informacion->buffer[0].estado = 1;
        informacion->buffer[0].instruccion = instruccion;
        informacion->buffer[0].addPc = PC;

        printf("Instruccion IF/ID: %s \n", informacion->buffer[0].instruccion->instruccion);
    }

    else if(etapa == 2) //ETAPA ID buffers[1] = ID/EX
    {
        informacion->buffer[1] = informacion->buffer[0];
        informacion->buffer[0].estado = 0;
        // Etapa nueva 
        informacion->buffer[1].muxRegDs = informacion->buffer[1].instruccion->rd;
        informacion->buffer[1].rs = informacion->buffer[1].instruccion->rs;
        informacion->buffer[1].rt = informacion->buffer[1].instruccion->rt;
        informacion->buffer[1].rd = informacion->buffer[1].instruccion->rd;
        informacion->buffer[1].lineaDeControl = asignarLineasDeControl(informacion->buffer[1].instruccion->instruccion);
        informacion->buffer[1].writeRegister = informacion->buffer[0].instruccion->rd;
        informacion->buffer[1].readData1Id = informacion->registros[posrs];
        informacion->buffer[1].readData2Id = informacion->registros[posrt];

        printf("Instruccion ID/EX: %s %s %s %s \n", informacion->buffer[1].instruccion->instruccion,informacion->buffer[1].instruccion->rd , informacion->buffer[1].instruccion->rs, 
            informacion->buffer[1].instruccion->rt);
        printf("Instruccion ID/EX: %d %d \n", informacion->buffer[1].readData1Id , informacion->buffer[1].readData2Id);
        mostrarLineasControl(informacion->buffer[1].lineaDeControl);

    }
 
    else if(etapa == 3) //ETAPA EX buffers[2] = EX/MEM
    {   
        informacion->buffer[2] = informacion->buffer[1];
        informacion->buffer[1].estado = 0;
        // Etapa nueva 
        informacion->buffer[2].aluResult = informacion->buffer[2].readData1Id - informacion->buffer[2].readData2Id;

        printf("Instruccion EX/MEM: %s %s %s %s \n", informacion->buffer[2].instruccion->instruccion,informacion->buffer[2].instruccion->rd , informacion->buffer[2].instruccion->rs, 
            informacion->buffer[2].instruccion->rt);
        printf("Instruccion EX/MEM: Resultado: %d \n", informacion->buffer[2].aluResult);
        mostrarLineasControl(informacion->buffer[2].lineaDeControl);
    }

    else if(etapa == 4) //ETAPA MEM buffers[3] = MEM/WB
    {
        informacion->buffer[3] = informacion->buffer[2];
        informacion->buffer[2].estado = 0;
        //Etapa nueva         
        informacion->buffer[3].writeDataWb = informacion->buffer[3].aluResult;

        printf("Instruccion MEM/WB: %s %s %s %s \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rd , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->rt);
        printf("Instruccion MEM/WB: Resultado: %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].writeDataWb);
        mostrarLineasControl(informacion->buffer[3].lineaDeControl);
    }

    else if(etapa == 5) //ETAPA WB
    {
        informacion->buffer[4] = informacion->buffer[3];
        // Etapa nueva
        informacion->buffer[3].estado = 0;
        informacion->registros[posrd] = informacion->buffer[3].writeDataWb;
        printf("Instruccion WB: Numero a guardar: %d \n", informacion->buffer[3].writeDataWb);
        printf("Instruccion WB: Resultado: %d \n", informacion->registros[posrd]);
    }   
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros rs y rt y realizando la multiplicacíon de ellos 
y asi guardando el resultado en rd.
 */

void mul(Informacion *informacion, Instruccion *instruccion, int PC,int etapa)
{           
    int posrt;
    int posrs;
    int posrd;

    posrt = obtenerPosicionReg(instruccion->rt);
    posrs = obtenerPosicionReg(instruccion->rs);
    posrd = obtenerPosicionReg(instruccion->rd);

    
    if(etapa == 1) // ETAPA IF buffers[0] = IF/ID
    {   
        informacion->buffer[0].instruccion = instruccion;
        informacion->buffer[0].addPc = PC;
        informacion->buffer[0].estado = 1;

        printf("Instruccion IF/ID: %s \n", informacion->buffer[0].instruccion->instruccion);
    }

    else if(etapa == 2) //ETAPA ID buffers[1] = ID/EX
    {
        informacion->buffer[1] = informacion->buffer[0];
        informacion->buffer[0].estado = 0;
        // Etapa nueva 
        informacion->buffer[1].muxRegDs = informacion->buffer[1].instruccion->rd;
        informacion->buffer[1].rs = informacion->buffer[1].instruccion->rs;
        informacion->buffer[1].rt = informacion->buffer[1].instruccion->rt;
        informacion->buffer[1].rd = informacion->buffer[1].instruccion->rd;
        informacion->buffer[1].lineaDeControl = asignarLineasDeControl(informacion->buffer[1].instruccion->instruccion);
        informacion->buffer[1].writeRegister = informacion->buffer[0].instruccion->rd;
        informacion->buffer[1].readData1Id = informacion->registros[posrs];
        informacion->buffer[1].readData2Id = informacion->registros[posrt];

        printf("Instruccion ID/EX: %s %s %s %s \n", informacion->buffer[1].instruccion->instruccion,informacion->buffer[1].instruccion->rd , informacion->buffer[1].instruccion->rs, 
            informacion->buffer[1].instruccion->rt);
        printf("Instruccion ID/EX: %d %d \n", informacion->buffer[1].readData1Id , informacion->buffer[1].readData2Id);
        mostrarLineasControl(informacion->buffer[1].lineaDeControl);

    }
 
    else if(etapa == 3) //ETAPA EX buffers[2] = EX/MEM
    {   
        informacion->buffer[2] = informacion->buffer[1];
        informacion->buffer[1].estado = 0;
        // Etapa nueva 
        informacion->buffer[2].aluResult = informacion->buffer[2].readData1Id * informacion->buffer[2].readData2Id;

        printf("Instruccion EX/MEM: %s %s %s %s \n", informacion->buffer[2].instruccion->instruccion,informacion->buffer[2].instruccion->rd , informacion->buffer[2].instruccion->rs, 
            informacion->buffer[2].instruccion->rt);
        printf("Instruccion EX/MEM: Resultado: %d \n", informacion->buffer[2].aluResult);
        mostrarLineasControl(informacion->buffer[2].lineaDeControl);
    }

    else if(etapa == 4) //ETAPA MEM buffers[3] = MEM/WB
    {
        informacion->buffer[3] = informacion->buffer[2];
        informacion->buffer[2].estado = 0;
        //Etapa nueva         
        informacion->buffer[3].writeDataWb = informacion->buffer[3].aluResult;

        printf("Instruccion MEM/WB: %s %s %s %s \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rd , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->rt);
        printf("Instruccion MEM/WB: Resultado: %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].writeDataWb);
        mostrarLineasControl(informacion->buffer[3].lineaDeControl);
    }

    else if(etapa == 5) //ETAPA WB
    {
        informacion->buffer[4] = informacion->buffer[3];
        informacion->buffer[3].estado = 0;
        // Etapa nueva
        informacion->registros[posrd] = informacion->buffer[3].writeDataWb;

        printf("Instruccion WM: %s %s %s %s \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rd , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->rt);
        printf("Instruccion WM: Resultado: %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].writeDataWb);
        printf("El nuevo registor es :%d\n", informacion->registros[posrd]);
        mostrarLineasControl(informacion->buffer[3].lineaDeControl);
    }   
}

void vacio(Informacion *informacion, Instruccion *instruccion, int PC,int etapa)
{           
    if(etapa == 1) // ETAPA IF buffers[0] = IF/ID
    {   
        //resetearBuffer(&informacion->buffer[0]);
        informacion->buffer[0].instruccion = instruccion;
        informacion->buffer[0].addPc = PC;
        informacion->buffer[0].estado = 1;
        printf("Instruccion IF/ID: %s \n", informacion->buffer[0].instruccion->instruccion);
    }

    else if(etapa == 2) //ETAPA ID buffers[1] = ID/EX
    {
        informacion->buffer[1] = informacion->buffer[0];
        informacion->buffer[0].estado = 0;
        // Etapa nueva 
        informacion->buffer[1].muxRegDs = "";
        informacion->buffer[1].rs = "";
        informacion->buffer[1].rt = "";
        informacion->buffer[1].rd = "";
        informacion->buffer[1].lineaDeControl = asignarLineasDeControl(informacion->buffer[1].instruccion->instruccion);
        informacion->buffer[1].writeRegister = "";
        informacion->buffer[1].readData1Id = 0;
        informacion->buffer[1].readData2Id = 0;

        printf("Instruccion ID/EX: %s \n", informacion->buffer[1].instruccion->instruccion);

    }
 
    else if(etapa == 3) //ETAPA EX buffers[2] = EX/MEM
    {   
        informacion->buffer[2] = informacion->buffer[1];
        informacion->buffer[1].estado = 0;
        // Etapa nueva 
        informacion->buffer[2].aluResult = 0;

        printf("Instruccion EX/MEM: %s \n", informacion->buffer[2].instruccion->instruccion);
    }

    else if(etapa == 4) //ETAPA MEM buffers[3] = MEM/WB
    {
        informacion->buffer[3] = informacion->buffer[2];
        informacion->buffer[2].estado = 0;
        //Etapa nueva         
        informacion->buffer[3].writeDataWb = 0;
        
        printf("Instruccion MEM/WB: %s \n", informacion->buffer[3].instruccion->instruccion);
    }

    else if(etapa == 5) //ETAPA WB
    {
        informacion->buffer[4] = informacion->buffer[3];
        informacion->buffer[3].estado = 0;
        // Etapa nueva
        printf("Instruccion WB: %s \n", informacion->buffer[3].instruccion->instruccion);
    }   
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros rs y rt y realizando la division de ellos 
y asi guardando el resultado en rd.
 */

void division(Informacion *informacion, Instruccion *instruccion, int PC,int etapa)
{           
    int posrt;
    int posrs;
    int posrd;

    posrt = obtenerPosicionReg(instruccion->rt);
    posrs = obtenerPosicionReg(instruccion->rs);
    posrd = obtenerPosicionReg(instruccion->rd);

    
    if(etapa == 1) // ETAPA IF buffers[0] = IF/ID
    {   
        informacion->buffer[0].instruccion = instruccion;
        informacion->buffer[0].addPc = PC;
        informacion->buffer[0].estado = 1;

        printf("Instruccion IF/ID: %s \n", informacion->buffer[0].instruccion->instruccion);
    }

    else if(etapa == 2) //ETAPA ID buffers[1] = ID/EX
    {
        informacion->buffer[1] = informacion->buffer[0];
        informacion->buffer[0].estado = 0;
        // Etapa nueva 
        informacion->buffer[1].muxRegDs = informacion->buffer[1].instruccion->rd;
        informacion->buffer[1].rs = informacion->buffer[1].instruccion->rs;
        informacion->buffer[1].rt = informacion->buffer[1].instruccion->rt;
        informacion->buffer[1].rd = informacion->buffer[1].instruccion->rd;
        informacion->buffer[1].lineaDeControl = asignarLineasDeControl(informacion->buffer[1].instruccion->instruccion);
        informacion->buffer[1].writeRegister = informacion->buffer[0].instruccion->rd;
        informacion->buffer[1].readData1Id = informacion->registros[posrs];
        informacion->buffer[1].readData2Id = informacion->registros[posrt];

        printf("Instruccion ID/EX: %s %s %s %s \n", informacion->buffer[1].instruccion->instruccion,informacion->buffer[1].instruccion->rd , informacion->buffer[1].instruccion->rs, 
            informacion->buffer[1].instruccion->rt);
        printf("Instruccion ID/EX: %d %d \n", informacion->buffer[1].readData1Id , informacion->buffer[1].readData2Id);
        mostrarLineasControl(informacion->buffer[1].lineaDeControl);

    }
 
    else if(etapa == 3) //ETAPA EX buffers[2] = EX/MEM
    {   
        informacion->buffer[2] = informacion->buffer[1];
        informacion->buffer[1].estado = 0;
        // Etapa nueva 
        informacion->buffer[2].aluResult = informacion->buffer[2].readData1Id / informacion->buffer[2].readData2Id;

        printf("Instruccion EX/MEM: %s %s %s %s \n", informacion->buffer[2].instruccion->instruccion,informacion->buffer[2].instruccion->rd , informacion->buffer[2].instruccion->rs, 
            informacion->buffer[2].instruccion->rt);
        printf("Instruccion EX/MEM: Resultado: %d \n", informacion->buffer[2].aluResult);
        mostrarLineasControl(informacion->buffer[2].lineaDeControl);
    }

    else if(etapa == 4) //ETAPA MEM buffers[3] = MEM/WB
    {
        informacion->buffer[3] = informacion->buffer[2];
        informacion->buffer[2].estado = 0;
        //Etapa nueva         
        informacion->buffer[3].writeDataWb = informacion->buffer[3].aluResult;

        printf("Instruccion MEM/WB: %s %s %s %s \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rd , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->rt);
        printf("Instruccion MEM/WB: Resultado: %d %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].writeDataWb);
        mostrarLineasControl(informacion->buffer[3].lineaDeControl);
    }

    else if(etapa == 5) //ETAPA WB
    {
        informacion->buffer[4] = informacion->buffer[3];
        informacion->buffer[3].estado = 0;
        // Etapa nueva
        informacion->registros[posrd] = informacion->buffer[3].writeDataWb;

        printf("Instruccion WM: %s %s %s %s \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rd , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->rt);
        printf("Instruccion WM: Resultado: %d %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].writeDataWb);
        printf("El nuevo registor es :%d\n", informacion->registros[posrd]);
        mostrarLineasControl(informacion->buffer[3].lineaDeControl);
    }   
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros rs y inmediato y realizando la resta de ellos 
y asi guardando el resultado en rd.
 */


void subi(Informacion *informacion, Instruccion *instruccion, int PC,int etapa)
{           
    int posrt;
    int posrs;

    posrt = obtenerPosicionReg(instruccion->rt);
    posrs = obtenerPosicionReg(instruccion->rs);

    
    if(etapa == 1) // ETAPA IF buffers[0] = IF/ID
    {   
        informacion->buffer[0].instruccion = instruccion;
        informacion->buffer[0].addPc = PC;
        informacion->buffer[0].estado = 1;

        printf("Instruccion IF/ID: %s \n", informacion->buffer[0].instruccion->instruccion);
    }

    else if(etapa == 2) //ETAPA ID buffers[1] = ID/EX
    {
        informacion->buffer[1] = informacion->buffer[0];
        informacion->buffer[0].estado = 0;
        // Etapa nueva 
        informacion->buffer[1].muxRegDs = informacion->buffer[1].instruccion->rd;
        informacion->buffer[1].rs = informacion->buffer[1].instruccion->rs;
        informacion->buffer[1].rt = informacion->buffer[1].instruccion->rt;        
        informacion->buffer[1].rd = informacion->buffer[1].instruccion->rt;
        informacion->buffer[1].signoExtendido = informacion->buffer[1].instruccion->inmediato;
        informacion->buffer[1].lineaDeControl = asignarLineasDeControl(informacion->buffer[1].instruccion->instruccion);
        informacion->buffer[1].writeRegister = informacion->buffer[0].instruccion->rt;
        informacion->buffer[1].readData1Id = informacion->registros[posrs];

        printf("Instruccion ID/EX: %s %s %s %d \n", informacion->buffer[1].instruccion->instruccion,informacion->buffer[1].instruccion->rt , informacion->buffer[1].instruccion->rs, 
            informacion->buffer[1].instruccion->inmediato);
        printf("Instruccion ID/EX: %d %d \n", informacion->buffer[1].readData1Id , informacion->buffer[1].signoExtendido);
        mostrarLineasControl(informacion->buffer[1].lineaDeControl);

    }
 
    else if(etapa == 3) //ETAPA EX buffers[2] = EX/MEM
    {   
        informacion->buffer[2] = informacion->buffer[1];
        informacion->buffer[1].estado = 0;
        // Etapa nueva 
        informacion->buffer[2].aluResult = informacion->buffer[2].readData1Id - informacion->buffer[2].signoExtendido;

        printf("Instruccion EX/MEM: %s %s %s %d \n", informacion->buffer[2].instruccion->instruccion,informacion->buffer[2].instruccion->rt , informacion->buffer[2].instruccion->rs, 
            informacion->buffer[2].instruccion->inmediato);
        printf("Instruccion EX/MEM: Resultado: %d \n", informacion->buffer[2].aluResult);
        mostrarLineasControl(informacion->buffer[2].lineaDeControl);
    }

    else if(etapa == 4) //ETAPA MEM buffers[3] = MEM/WB
    {
        informacion->buffer[3] = informacion->buffer[2];
        informacion->buffer[2].estado = 0;
        //Etapa nueva         
        informacion->buffer[3].writeDataWb = informacion->buffer[3].aluResult;

        printf("Instruccion MEM/WB: %s %s %s %d \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rt , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->inmediato);
        printf("Instruccion MEM/WB: Resultado: %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].writeDataWb);
        mostrarLineasControl(informacion->buffer[3].lineaDeControl);
    }

    else if(etapa == 5) //ETAPA WB
    {
        informacion->buffer[4] = informacion->buffer[3];
        informacion->buffer[3].estado = 0;       
         // Etapa nueva
        informacion->registros[posrt] = informacion->buffer[3].writeDataWb;

        printf("Instruccion WM: %s %s %s %d \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rt , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->inmediato);
        printf("Instruccion WM: Resultado: %d %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].writeDataWb);
        printf("El nuevo registor es :%d\n", informacion->registros[posrt]);
        mostrarLineasControl(informacion->buffer[3].lineaDeControl);
    }   
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros rs y inmediato y realizando la suma de ellos 
y asi guardando el resultado en rd.
 */

void addi(Informacion *informacion, Instruccion *instruccion, int PC,int etapa)
{           
    int posrt;
    int posrs;

    posrt = obtenerPosicionReg(instruccion->rt);
    posrs = obtenerPosicionReg(instruccion->rs);

    
    if(etapa == 1) // ETAPA IF buffers[0] = IF/ID
    {   
        informacion->buffer[0].instruccion = instruccion;
        informacion->buffer[0].addPc = PC;
        informacion->buffer[0].estado = 1;

        printf("Instruccion IF/ID: %s \n", informacion->buffer[0].instruccion->instruccion);
    }

    else if(etapa == 2) //ETAPA ID buffers[1] = ID/EX
    {
        informacion->buffer[1] = informacion->buffer[0];
        informacion->buffer[0].estado = 0;
        // Etapa nueva 
        informacion->buffer[1].muxRegDs = informacion->buffer[1].instruccion->rd;
        informacion->buffer[1].rs = informacion->buffer[1].instruccion->rs;
        informacion->buffer[1].rt = informacion->buffer[1].instruccion->rt;        
        informacion->buffer[1].rd = informacion->buffer[1].instruccion->rt;
        informacion->buffer[1].signoExtendido = informacion->buffer[1].instruccion->inmediato;
        informacion->buffer[1].lineaDeControl = asignarLineasDeControl(informacion->buffer[1].instruccion->instruccion);
        informacion->buffer[1].writeRegister = informacion->buffer[0].instruccion->rt;
        informacion->buffer[1].readData1Id = informacion->registros[posrs];

        printf("Instruccion ID/EX: %s %s %s %d \n", informacion->buffer[1].instruccion->instruccion,informacion->buffer[1].instruccion->rt , informacion->buffer[1].instruccion->rs, 
            informacion->buffer[1].instruccion->inmediato);
        printf("Instruccion ID/EX: %d %d \n", informacion->buffer[1].readData1Id , informacion->buffer[1].signoExtendido);
        mostrarLineasControl(informacion->buffer[1].lineaDeControl);

    }
 
    else if(etapa == 3) //ETAPA EX buffers[2] = EX/MEM
    {   
        informacion->buffer[2] = informacion->buffer[1];
        informacion->buffer[1].estado = 0;
        // Etapa nueva 
        informacion->buffer[2].aluResult = informacion->buffer[2].readData1Id + informacion->buffer[2].signoExtendido;

        printf("Instruccion EX/MEM: %s %s %s %d \n", informacion->buffer[2].instruccion->instruccion,informacion->buffer[2].instruccion->rt , informacion->buffer[2].instruccion->rs, 
            informacion->buffer[2].instruccion->inmediato);
        printf("Instruccion EX/MEM: Resultado: %d \n", informacion->buffer[2].aluResult);
        mostrarLineasControl(informacion->buffer[2].lineaDeControl);
    }

    else if(etapa == 4) //ETAPA MEM buffers[3] = MEM/WB
    {
        informacion->buffer[3] = informacion->buffer[2];
        informacion->buffer[2].estado = 0;
        //Etapa nueva         
        informacion->buffer[3].writeDataWb = informacion->buffer[3].aluResult;

        printf("Instruccion MEM/WB: %s %s %s %d \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rt , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->inmediato);
        printf("Instruccion MEM/WB: Resultado: %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].writeDataWb);
        mostrarLineasControl(informacion->buffer[3].lineaDeControl);
    }

    else if(etapa == 5) //ETAPA WB
    {
        informacion->buffer[4] = informacion->buffer[3];
        informacion->buffer[3].estado = 0;
        // Etapa nueva
        informacion->registros[posrt] = informacion->buffer[3].writeDataWb;

        printf("Instruccion WM: %s %s %s %d \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rt , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->inmediato);
        printf("Instruccion WM: Resultado: %d %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].writeDataWb);
        printf("El nuevo registor es :%d\n", informacion->registros[posrt]);
        mostrarLineasControl(informacion->buffer[3].lineaDeControl);
    }   
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: Entrega el valor de donde debe realizar el salto la funcion.
- Procedimiento: Se encarga de concatenar el nombre del label con un ':', para que asi luego ocupe el llamado a la funcion 
buscarPosicionEtiqueta y entregue el numero de donde se encuentra
 */

int jump(Informacion *informacion, Instruccion *instruccion, int PC, int etapa)
{   

    if(etapa == 1) // ETAPA IF buffers[0] = IF/ID
    {   
        informacion->buffer[0].instruccion = instruccion;
        informacion->buffer[0].addPc = PC;
        informacion->buffer[0].estado = 1;

        printf("Instruccion IF/ID: %s \n", informacion->buffer[0].instruccion->instruccion);
    }

    else if(etapa == 2) //ETAPA ID buffers[1] = ID/EX
    {
        informacion->buffer[1] = informacion->buffer[0];
        informacion->buffer[0].estado = 0;
        // Etapa nueva 
        informacion->buffer[1].rs = informacion->buffer[1].instruccion->rs;
        informacion->buffer[1].rt = informacion->buffer[1].instruccion->rt;        
        informacion->buffer[1].rd = informacion->buffer[1].instruccion->rt;
        char *etiqueta = (char*)malloc(sizeof(char)*100);
        strcpy(etiqueta,informacion->buffer[1].instruccion->rd);
        strcat(etiqueta,":");
        INTRUCCIONESEJECUTADAS = buscarPosicionEtiqueta(etiqueta, informacion);

    }
 
    else if(etapa == 3) //ETAPA EX buffers[2] = EX/MEM
    {   
        informacion->buffer[2] = informacion->buffer[1];
        informacion->buffer[1].estado = 0;
    }

    else if(etapa == 4) //ETAPA MEM buffers[3] = MEM/WB
    {
        informacion->buffer[3] = informacion->buffer[2];
        informacion->buffer[2].estado = 0;
    }

    else if(etapa == 5) //ETAPA WB
    {
        informacion->buffer[4] = informacion->buffer[3];
        informacion->buffer[3].estado = 0;
    } 
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: Entrega un 1 si se cumple la condicion y un 0 si esta no se cumple.
- Procedimiento: Se encarga de verificar si la condición de los registro se cumple o no, para asi tomar la decision
del valor a que retornara.
 */

int beq(Informacion *informacion, Instruccion *instruccion, int PC, int etapa)
{            
    int posrt;
    int posrs;
    int posrd;

    
    if(etapa == 1) // ETAPA IF buffers[0] = IF/ID
    {   
        informacion->buffer[0].instruccion = instruccion;
        informacion->buffer[0].addPc = PC;
        informacion->buffer[0].estado = 1;

        printf("Instruccion IF/ID: %s \n", informacion->buffer[0].instruccion->instruccion);
    }

    else if(etapa == 2) //ETAPA ID buffers[1] = ID/EX
    {
        informacion->buffer[1] = informacion->buffer[0];
        informacion->buffer[0].estado = 0;        
        // Etapa nueva 
        printf("%d %d \n", posrt,posrs );
        informacion->buffer[1].rs = informacion->buffer[1].instruccion->rs;
        informacion->buffer[1].rt = informacion->buffer[1].instruccion->rt;        
        informacion->buffer[1].rd = informacion->buffer[1].instruccion->rd;
        posrt = obtenerPosicionReg(informacion->buffer[1].rt);
        posrs = obtenerPosicionReg(informacion->buffer[1].rs); 
        informacion->buffer[1].lineaDeControl = asignarLineasDeControl(informacion->buffer[1].instruccion->instruccion);
        informacion->buffer[1].readData1Id = informacion->registros[posrs];
        informacion->buffer[1].readData2Id = informacion->registros[posrt];

        printf("Instruccion ID/EX: %s %s %s %d \n", informacion->buffer[1].instruccion->instruccion,informacion->buffer[1].instruccion->rt , informacion->buffer[1].instruccion->rs, 
            informacion->buffer[1].instruccion->inmediato);
    }
 
    else if(etapa == 3) //ETAPA EX buffers[2] = EX/MEM
    {   
        informacion->buffer[2] = informacion->buffer[1];
        informacion->buffer[1].estado = 0;
        // Etapa nueva 
        printf("%d \n", informacion->buffer[2].readData1Id );
        printf("%d \n", informacion->buffer[2].readData2Id );
        informacion->buffer[2].zero = informacion->buffer[2].readData1Id - informacion->buffer[2].readData2Id;

        printf("Instruccion EX/MEM: %s %s %s %d \n", informacion->buffer[2].instruccion->instruccion,informacion->buffer[2].instruccion->rt , informacion->buffer[2].instruccion->rs, 
            informacion->buffer[2].instruccion->inmediato);
        printf("El resultado de zero es : %d , el resultado de rd es : %d \n", informacion->buffer[2].zero, posrd );
    }

    else if(etapa == 4) //ETAPA MEM buffers[3] = MEM/WB
    {
        printf("PREDICION DEL BEQ :O :O :O :O :O :O :O \n");
        informacion->buffer[3] = informacion->buffer[2];
        informacion->buffer[2].estado = 0;
        //Etapa nueva         
        if (informacion->buffer[3].zero == 0 )
        {
            char *etiqueta = (char*)malloc(sizeof(char)*100);
            strcpy(etiqueta,informacion->buffer[3].instruccion->rd);
            strcat(etiqueta,":");
            posrd = buscarPosicionEtiqueta(etiqueta, informacion);
            INTRUCCIONESEJECUTADAS = posrd;
            resetearBuffer(informacion,0);
            resetearBuffer(informacion,1);
            informacion->hazarControl = "H.C";
        }
        
        printf("Instruccion MEM/WB: %s %s %s %d \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rt , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->inmediato);
    }

    else if(etapa == 5) //ETAPA WB
    {
        informacion->buffer[4] = informacion->buffer[3];
        informacion->buffer[3].estado = 0;
    }  
}

/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros inmediato y la direccion, para asi luego buscar
el valor del registro con dicho valor y asi guardarlo en el registro correspondiente.
 */

void lw(Informacion *informacion, Instruccion *instruccion, int PC,int etapa)
{           
    int posrt;
    int posrs;

    posrt = obtenerPosicionReg(instruccion->rt);
    posrs = obtenerPosicionReg(instruccion->rs);

    
    if(etapa == 1) // ETAPA IF buffers[0] = IF/ID
    {   
        informacion->buffer[0].instruccion = instruccion;
        informacion->buffer[0].addPc = PC;
        informacion->buffer[0].estado = 1;

        printf("Instruccion IF/ID: %s \n", informacion->buffer[0].instruccion->instruccion);
    }

    else if(etapa == 2) //ETAPA ID buffers[1] = ID/EX
    {
        informacion->buffer[1] = informacion->buffer[0];
        informacion->buffer[0].estado = 0;
        // Etapa nueva 
        informacion->buffer[1].muxRegDs = informacion->buffer[1].instruccion->rt;
        informacion->buffer[1].rs = informacion->buffer[1].instruccion->rs;
        informacion->buffer[1].rt = informacion->buffer[1].instruccion->rt;        
        informacion->buffer[1].rd = informacion->buffer[1].instruccion->rt;
        informacion->buffer[1].signoExtendido = informacion->buffer[1].instruccion->inmediato;
        informacion->buffer[1].lineaDeControl = asignarLineasDeControl(informacion->buffer[1].instruccion->instruccion);
        informacion->buffer[1].writeRegister = informacion->buffer[1].instruccion->rt;
        informacion->buffer[1].readData1Id = informacion->registros[posrs];
        //informacion->buffer[0].instruccion = resetearInstruccion(informacion->buffer[0].instruccion);

        printf("Instruccion ID/EX: %s %s %s %d \n", informacion->buffer[1].instruccion->instruccion,informacion->buffer[1].instruccion->rt , informacion->buffer[1].instruccion->rs, 
            informacion->buffer[1].instruccion->inmediato);
        printf("Instruccion ID/EX: %d %d \n", informacion->buffer[1].readData1Id , informacion->buffer[1].signoExtendido);
        mostrarLineasControl(informacion->buffer[1].lineaDeControl);
    }
 
    else if(etapa == 3) //ETAPA EX buffers[2] = EX/MEM
    {   
        informacion->buffer[2] = informacion->buffer[1];
        informacion->buffer[1].estado = 0;
        // Etapa nueva 
        informacion->buffer[2].aluResult = informacion->buffer[2].readData1Id + (informacion->buffer[2].signoExtendido/4);

        printf("Instruccion EX/MEM: %s %s %s %d \n", informacion->buffer[2].instruccion->instruccion,informacion->buffer[2].instruccion->rt , informacion->buffer[2].instruccion->rs, 
            informacion->buffer[2].instruccion->inmediato);
        printf("Instruccion EX/MEM: Resultado: %d \n", informacion->buffer[2].aluResult);
        mostrarLineasControl(informacion->buffer[2].lineaDeControl);
    }

    else if(etapa == 4) //ETAPA MEM buffers[3] = MEM/WB
    {
        informacion->buffer[3] = informacion->buffer[2];
        informacion->buffer[2].estado = 0;
        //Etapa nueva         
        informacion->buffer[3].writeDataWb = informacion->memoria[informacion->buffer[3].aluResult];

        printf("Instruccion MEM/WB: %s %s %s %d \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rt , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->inmediato);
        printf("Instruccion MEM/WB: Resultado: %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].writeDataWb);
        mostrarLineasControl(informacion->buffer[3].lineaDeControl);
    }

    else if(etapa == 5) //ETAPA WB
    {
        informacion->buffer[4] = informacion->buffer[3];
        informacion->buffer[3].estado = 0;
        // Etapa nueva
        informacion->registros[posrt] = informacion->buffer[3].writeDataWb;

        printf("Instruccion WM: Resultado: %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].writeDataWb);
        printf("El nuevo registor es :%d\n", informacion->registros[posrt]);
    }   
}


/*
- Entrada: Funcion que recibe como parametro un puntero a la estructura informacion y la instruccion que se desea trabajar.
- Salida: -
- Procedimiento: Modifica el puntero a la estructura informacion, tomando los registros inmediato y la direccion, para asi luego buscar
el valor del registro con dicho valor y asi guardarlo en la memoria correspondiente.
 */


void sw(Informacion *informacion, Instruccion *instruccion, int PC,int etapa)
{           
    int posRegistro;
    int posrs;

    posrs = obtenerPosicionReg(instruccion->rs);

    if(etapa == 1) // ETAPA IF buffers[0] = IF/ID
    {   
        informacion->buffer[0].instruccion = instruccion;
        informacion->buffer[0].addPc = PC;
        informacion->buffer[0].estado = 1;

        printf("Instruccion IF/ID: %s \n", informacion->buffer[0].instruccion->instruccion);
    }

    else if(etapa == 2) //ETAPA ID buffers[1] = ID/EX
    {
        informacion->buffer[1] = informacion->buffer[0];
        informacion->buffer[0].estado = 0;
        // Etapa nueva 
        informacion->buffer[1].muxRegDs = informacion->buffer[1].instruccion->rt;
        informacion->buffer[1].rs = informacion->buffer[1].instruccion->rs;
        informacion->buffer[1].rt = informacion->buffer[1].instruccion->rt;        
        informacion->buffer[1].rd = informacion->buffer[1].instruccion->rt;
        informacion->buffer[1].signoExtendido = informacion->buffer[1].instruccion->inmediato;
        informacion->buffer[1].lineaDeControl = asignarLineasDeControl(informacion->buffer[1].instruccion->instruccion);
        informacion->buffer[1].writeRegister = informacion->buffer[0].instruccion->rt;
        informacion->buffer[1].readData1Id = informacion->registros[posrs];

        printf("Instruccion ID/EX: %s %s %s %d \n", informacion->buffer[1].instruccion->instruccion,informacion->buffer[1].instruccion->rt , informacion->buffer[1].instruccion->rs, 
            informacion->buffer[1].instruccion->inmediato);
        printf("Instruccion ID/EX: %d %d \n", informacion->buffer[1].readData1Id , informacion->buffer[1].signoExtendido);
        mostrarLineasControl(informacion->buffer[1].lineaDeControl);
    }
 
    else if(etapa == 3) //ETAPA EX buffers[2] = EX/MEM
    {   
        informacion->buffer[2] = informacion->buffer[1];
        informacion->buffer[1].estado = 0;
        // Etapa nueva 
        informacion->buffer[2].aluResult = informacion->buffer[2].readData1Id + (informacion->buffer[2].signoExtendido/4);
        informacion->buffer[2].posRegistro = obtenerPosicionReg(informacion->buffer[2].instruccion->rt);

        printf("Instruccion EX/MEM: %s %s %s %d \n", informacion->buffer[2].instruccion->instruccion,informacion->buffer[2].instruccion->rt , informacion->buffer[2].instruccion->rs, 
            informacion->buffer[2].instruccion->inmediato);
        printf("Instruccion EX/MEM: Resultado: %d \n", informacion->buffer[2].aluResult);
        mostrarLineasControl(informacion->buffer[2].lineaDeControl);
    }

    else if(etapa == 4) //ETAPA MEM buffers[3] = MEM/WB
    {
        informacion->buffer[3] = informacion->buffer[2];
        informacion->buffer[2].estado = 0;
        //Etapa nueva         
        informacion->memoria[informacion->buffer[3].aluResult] = informacion->registros[informacion->buffer[3].posRegistro];

        printf("Instruccion MEM/WB: %s %s %s %d \n", informacion->buffer[3].instruccion->instruccion,informacion->buffer[3].instruccion->rt , informacion->buffer[3].instruccion->rs, 
            informacion->buffer[3].instruccion->inmediato);
        printf("Instruccion MEM/WB: Resultado: %d %d %d \n", informacion->buffer[3].aluResult,informacion->buffer[3].posRegistro,informacion->registros[informacion->buffer[3].posRegistro]);   
        mostrarLineasControl(informacion->buffer[3].lineaDeControl);
    }

    else if(etapa == 5) //ETAPA WB
    {
        informacion->buffer[4] = informacion->buffer[3];
        informacion->buffer[3].estado = 0;
        //No ocupe esta etapa
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

LineaDeControl* asignarLineasDeControl (char* instruccion)
{
    LineaDeControl* aux = (LineaDeControl*)malloc(sizeof(LineaDeControl));
    aux->ALUOp = (char*)malloc(sizeof(char)*10);

    if (
        !strcmp(instruccion,"add") ||
        !strcmp(instruccion,"sub") ||
        !strcmp(instruccion,"mul") ||
        !strcmp(instruccion,"div")
        ){
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

    else if (!strcmp(instruccion,"vacio"))
    {
            aux->RegDst = '0';
            aux->Jump = '0';
            aux->Branch = '0';
            aux->MemRead = '0';
            aux->MemToReg = '0';
            strcpy(aux->ALUOp , "00");
            aux->MemWrite = '0';
            aux->ALUSrc = '0';
            aux->RegWrite = '0';
    }

    else if (!strcmp(instruccion,"subi"))
    {
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

int is_nop(Informacion* informacion)
{
    printf("%s Buffer 1 : %s - buffer 2 : %s \n",informacion->buffer[1].instruccion->instruccion ,informacion->buffer[1].rd, informacion->buffer[0].instruccion->rs);
    printf("%s Buffer 1 : %s - buffer 2 : %s \n",informacion->buffer[1].instruccion->instruccion ,informacion->buffer[1].rd, informacion->buffer[0].instruccion->rt);
    printf("%d %d \n", informacion->buffer[0].addPc , informacion->buffer[1].addPc );

    printf("%d %d \n", informacion->buffer[1].addPc , INTRUCCIONESEJECUTADAS);
    printf("%s %s \n", informacion->buffer[1].instruccion->instruccion , informacion->buffer[0].instruccion->instruccion);
    
    if( (informacion->buffer[1].lineaDeControl->MemRead == '1' )  &&
        ( strcmp(informacion->buffer[1].rd , informacion->instrucciones[INTRUCCIONESEJECUTADAS].rs ) == 0 || 
        strcmp( informacion->buffer[1].rd , informacion->instrucciones[INTRUCCIONESEJECUTADAS].rt ) == 0 ) )  
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

void hazarDatoEx( Informacion* informacion ) 
{
    printf("\n");
    printf("\n");
    printf("1 %s\n", informacion->buffer[2].rd);
    printf("2 %s\n", informacion->buffer[2].rt);
    printf("3 %s\n", informacion->buffer[1].rs);    
    printf("4 %s\n", informacion->buffer[1].rt);
    printf("\n");
    printf("\n");

    if ( informacion->buffer[2].lineaDeControl->RegWrite == '1' && strcmp(informacion->buffer[2].rd , informacion->buffer[1].rs) == 0  )
    {
        printf("\n");
        printf("\n");
        printf("ACA ACA ACA ACA ACA ACA ACA ACA \n");
        printf("\n");
        printf("\n");
        informacion->hazarDato = informacion->buffer[2].rd; 
        informacion->buffer[1].readData1Id = informacion->buffer[2].aluResult;

    }

    if ( informacion->buffer[2].lineaDeControl->RegWrite == '1' && strcmp(informacion->buffer[2].rd , informacion->buffer[1].rt) == 0 )
    {
        printf("\n");
        printf("\n");
        printf("ACA ACA ACA ACA ACA ACA ACA ACA \n");
        printf("\n");
        printf("\n");
        informacion->hazarDato = informacion->buffer[2].rd; 
        informacion->buffer[1].readData1Id = informacion->buffer[2].aluResult;

    }
}

void hazarDatoMEM( Informacion* informacion ) 
{
    printf("\n");
    printf("\n");
    printf("1 %s\n", informacion->buffer[3].rd);
    printf("2 %s\n", informacion->buffer[3].rt);
    printf("3 %s\n", informacion->buffer[1].rs);    
    printf("4 %s\n", informacion->buffer[1].rt);
    printf("\n");
    printf("\n");

    if (informacion->buffer[3].lineaDeControl->RegWrite == '1' && strcmp(informacion->buffer[3].rd , informacion->buffer[1].rs ) == 0 )
    {
        printf("\n");
        printf("\n");
        printf("ACA ACA ACA ACA ACA ACA ACA ACA \n");
        printf("\n");
        printf("\n");
        informacion->hazarDato = informacion->buffer[3].rd; 

        if(informacion->buffer[3].lineaDeControl->MemRead == '1')
        {
            printf("Entre aca 3 !!!!!!!!!!!!!!!!!!!!!!\n");
            informacion->buffer[1].readData1Id = informacion->buffer[3].readData1Mem;
        }

        else
        {
            printf("Entre aca 4 !!!!!!!!!!!!!!!!!!!!!!\n");
            informacion->buffer[1].readData1Id = informacion->buffer[3].aluResult;
        }

    }

    if (informacion->buffer[3].lineaDeControl->RegWrite == '1' && strcmp(informacion->buffer[3].rd , informacion->buffer[1].rt ) == 0 )
    {
        printf("\n");
        printf("\n");
        printf("ACA ACA ACA ACA ACA ACA ACA ACA \n");
        printf("\n");
        printf("\n");
        informacion->hazarDato = informacion->buffer[3].rd; 

        if(informacion->buffer[3].lineaDeControl->MemRead == '1' )
        {
            printf("Entre aca 3 !!!!!!!!!!!!!!!!!!!!!!\n");
            informacion->buffer[1].readData1Id = informacion->buffer[3].readData1Mem;
        }

        else
        {
            printf("Entre aca 4 !!!!!!!!!!!!!!!!!!!!!!\n");
            informacion->buffer[1].readData1Id = informacion->buffer[3].aluResult;
        }
    }

}

Instruccion* resetearInstruccion(Instruccion* instruccion)
{
    instruccion->instruccion = "vacio";
    instruccion->rs = "" ;
    instruccion->rt = "" ;
    instruccion->rd = "" ;
}

void resetearBuffer(Informacion* informacion, int i)
{
    informacion->buffer[i].instruccion = resetearInstruccion(informacion->buffer[i].instruccion);
    informacion->buffer[i].lineaDeControl = resetearLineasControl(informacion->buffer[i].lineaDeControl);
    informacion->buffer[i].addPc = 0;
    informacion->buffer[i].posRegistro = 0;
    informacion->buffer[i].readData1Id = 0;
    informacion->buffer[i].readData2Id = 0;
    informacion->buffer[i].signoExtendido= 0;
    informacion->buffer[i].zero = 0;
    informacion->buffer[i].aluResult = 0;
    informacion->buffer[i].readData1Mem = 0;
    informacion->buffer[i].ALU = 0;
    informacion->buffer[i].writeDataWb = 0;
    informacion->buffer[i].rs = "" ;
    informacion->buffer[i].rt = "";
    informacion->buffer[i].register1 = "";
    informacion->buffer[i].writeRegister = "";
    informacion->buffer[i].writeDataMem = "";
    informacion->buffer[i].address = "" ;
    informacion->buffer[i].register2 = "";
    informacion->buffer[i].rd = "";
    informacion->buffer[i].muxRegDs = "";
}

int chequearBuffer(Informacion* informacion)
{
    int i;

    for ( i = 0 ; i < 4 ; i++) 
    {
        printf("%s\n", informacion->buffer[i].instruccion->instruccion);
        if ( strcmp(informacion->buffer[i].instruccion->instruccion,"vacio") != 0 )
        {
            printf("Entre aca \n");
            return 1;
        }
    }
    return 0;
}

void pipeLine(Informacion *informacion)
{
    int i = 0;
    int ciclo = 1;
    int nubes = 0;

    Instruccion* nob = (Instruccion*)malloc(sizeof(Informacion));
    nob->instruccion = (char*)malloc(sizeof(char)*100);
    nob->rd = (char*)malloc(sizeof(char)*100);
    nob->rs = (char*)malloc(sizeof(char)*100);
    nob->rt = (char*)malloc(sizeof(char)*100);
    nob->lineaDeControl = (LineaDeControl*)malloc(sizeof(LineaDeControl));
    nob = inicializarIntrucciones(nob);

    printf("%d\n", informacion->cantidadDeInstrucciones);
    do
    {
        printf("\n");
        printf("\n");
        printf("Estamos en el ciclo numero : %d \n", ciclo );
        printf("\n");
        printf("\n");

        if (informacion->buffer[3].estado == 1)
        {
            printf("Entre a WM\n");
            etapaWB(informacion,INTRUCCIONESEJECUTADAS);
        }

        if (informacion->buffer[2].estado == 1)
        {
            printf("Entre a MEM\n");
            hazarDatoMEM(informacion);  
            etapaMEM(informacion,INTRUCCIONESEJECUTADAS);        
        }

        if (informacion->buffer[1].estado == 1)
        {
            printf("Entre a EX\n");
            hazarDatoEx(informacion);
            etapaEX(informacion,INTRUCCIONESEJECUTADAS);            
        }

        if (informacion->buffer[0].estado == 1)
        {            
            printf("Entre a ID\n");
            etapaID(informacion,INTRUCCIONESEJECUTADAS);
        }

        if (informacion->cantidadDeInstrucciones > INTRUCCIONESEJECUTADAS)
        {
            printf("%s\n",  informacion->instrucciones[INTRUCCIONESEJECUTADAS] );
            printf("Entre a IF\n");
            if (is_nop(informacion) == 1 )
            {
                etapaIF(informacion,nob,INTRUCCIONESEJECUTADAS);
            }

            else if ( strcmp(informacion->buffer[1].instruccion->instruccion , "j" ) == 0 )
            {
                etapaIF(informacion,nob,INTRUCCIONESEJECUTADAS);
                informacion->hazarControl = "H.C" ;
            }

            else
            {
                printf("%d\n", i);
                etapaIF(informacion,&informacion->instrucciones[INTRUCCIONESEJECUTADAS],INTRUCCIONESEJECUTADAS);
                INTRUCCIONESEJECUTADAS++;
            }
        }

        else if (informacion->cantidadDeInstrucciones <= INTRUCCIONESEJECUTADAS)
        {
            etapaIF(informacion,nob,INTRUCCIONESEJECUTADAS);
            INTRUCCIONESEJECUTADAS++;
        }
        
        escribirArchivoTraza(informacion ,ciclo);
        escribirArchivoHazar(informacion,ciclo);
        ciclo++;
    }while( chequearBuffer(informacion) != 0 );
}

void etapaIF(Informacion *info, Instruccion *instruccion , int PC)
{   

    //Instruccion 1
    if(!strcmp(instruccion->instruccion,"add"))
    {
        add(info,instruccion,PC, 1);
    }
    
    //Instruccion 2
    else if(!strcmp(instruccion->instruccion,"sub"))
    {
        sub(info,instruccion,PC, 1);
    }

    //Instruccion 2
    else if(!strcmp(instruccion->instruccion,"mul"))
    {
        mul(info,instruccion,PC, 1);
    }

    //Instruccion 2
    else if(!strcmp(instruccion->instruccion,"div"))
    {
        division(info,instruccion,PC, 1);
    }

    else if(!strcmp(instruccion->instruccion,"subi"))
    {
        subi(info,instruccion,PC, 1);
    }

    else if(!strcmp(instruccion->instruccion,"addi"))
    {
        addi(info,instruccion,PC, 1);
    }

    //Instruccion 3
    else if(!strcmp(instruccion->instruccion,"j"))
    {
        jump(info,instruccion,PC,1);
    }

    //Instruccion 4
    else if(!strcmp(instruccion->instruccion,"beq"))
    {
        beq(info,instruccion,PC,1);
    }

    //Instruccion 7
    else if(!strcmp(instruccion->instruccion,"sw"))
    {
        sw(info,instruccion,PC, 1);
    }

    //Instruccion 8
    else if(!strcmp(instruccion->instruccion,"lw"))
    {
        lw(info,instruccion,PC, 1);
    }

    else if(!strcmp(instruccion->instruccion,"vacio"))
    {
        vacio(info,instruccion,PC, 1);
    }
}

void etapaID(Informacion *info, int PC)
{   
    if(!strcmp(info->buffer[0].instruccion->instruccion,"add"))
    {
        add(info,info->buffer[0].instruccion,PC, 2);
    }

    //Instruccion 2
    else if(!strcmp(info->buffer[0].instruccion->instruccion,"mul"))
    {
        mul(info,info->buffer[0].instruccion,PC,2);
    }

    //Instruccion 2
    else if(!strcmp(info->buffer[0].instruccion->instruccion,"sub"))
    {
        sub(info,info->buffer[0].instruccion,PC,2);
    }

    //Instruccion 2
    else if(!strcmp(info->buffer[0].instruccion->instruccion,"div"))
    {
        division(info,info->buffer[0].instruccion,PC,2);
    }


    //Instruccion 3
    else if(!strcmp(info->buffer[0].instruccion->instruccion,"j"))
    {
        jump(info,info->buffer[0].instruccion,PC,2);
    }

    //Instruccion 4
    else if(!strcmp(info->buffer[0].instruccion->instruccion,"beq"))
    {
        beq(info,info->buffer[0].instruccion,PC,2);
    }

    //Instruccion 7
    else if(!strcmp(info->buffer[0].instruccion->instruccion,"sw"))
    {
        sw(info,info->buffer[0].instruccion,PC,2);
    }

    //Instruccion 8
    else if(!strcmp(info->buffer[0].instruccion->instruccion,"lw"))
    {
        lw(info,info->buffer[0].instruccion,PC,2);
    }

    //Instruccion 9
    else if(!strcmp(info->buffer[0].instruccion->instruccion,"addi"))
    {
        addi(info,info->buffer[0].instruccion,PC, 2);
    }

    //Instruccion 2
    else if(!strcmp(info->buffer[0].instruccion->instruccion,"subi"))
    {
        subi(info,info->buffer[0].instruccion,PC,2);
    }

    else if(!strcmp(info->buffer[0].instruccion->instruccion,"vacio"))
    {
        vacio(info,info->buffer[0].instruccion,PC, 2);
    }
}

void etapaEX(Informacion *info, int PC)
{
    if(!strcmp(info->buffer[1].instruccion->instruccion,"add"))
    {
        add(info,info->buffer[1].instruccion,PC, 3);
    }

    //Instruccion 1
    else if(!strcmp(info->buffer[1].instruccion->instruccion,"mul"))
    {
        mul(info,info->buffer[1].instruccion,PC,3);
    }

    //Instruccion 3
    else if(!strcmp(info->buffer[1].instruccion->instruccion,"j"))
    {
        jump(info,info->buffer[1].instruccion,PC,3);
    }

    //Instruccion 4
    else if(!strcmp(info->buffer[1].instruccion->instruccion,"beq"))
    {
        beq(info,info->buffer[1].instruccion,PC,3);
        
    }

    //Instruccion 5
    else if(!strcmp(info->buffer[1].instruccion->instruccion,"div"))    
    {
        division(info,info->buffer[1].instruccion,PC,3);
    }
    //Instruccion 6
    else if(!strcmp(info->buffer[1].instruccion->instruccion,"sub"))
    {
        sub(info,info->buffer[1].instruccion,PC,3);
    }

    //Instruccion 7
    else if(!strcmp(info->buffer[1].instruccion->instruccion,"sw"))
    {
        sw(info,info->buffer[1].instruccion,PC,3);
    }

    //Instruccion 8
    else if(!strcmp(info->buffer[1].instruccion->instruccion,"lw"))
    {
        lw(info,info->buffer[1].instruccion,PC,3);
    }

    //Instruccion 9
    else if(!strcmp(info->buffer[1].instruccion->instruccion,"addi"))
    {
        addi(info,info->buffer[1].instruccion,PC, 3);
    }

    //Instruccion 1
    else if(!strcmp(info->buffer[1].instruccion->instruccion,"subi"))
    {
        subi(info,info->buffer[1].instruccion,PC,3);
    }

    else if(!strcmp(info->buffer[1].instruccion->instruccion,"vacio"))
    {
        vacio(info,info->buffer[1].instruccion,PC, 3);
    }
}

void etapaMEM(Informacion *info, int PC)
{
    if(!strcmp(info->buffer[2].instruccion->instruccion,"add"))
    {
        add(info,info->buffer[2].instruccion,PC, 4);
    }

    //Instruccion 2
    else if(!strcmp(info->buffer[2].instruccion->instruccion,"mul"))
    {
        mul(info,info->buffer[2].instruccion,PC,4);
    }

    //Instruccion 2
    else if(!strcmp(info->buffer[2].instruccion->instruccion,"j"))
    {
        jump(info,info->buffer[2].instruccion,PC,4);
    }

    //Instruccion 4
    else if(!strcmp(info->buffer[2].instruccion->instruccion,"beq"))
    {
        beq(info,info->buffer[2].instruccion,PC,4);
    }

    //Instruccion 5
    else if(!strcmp(info->buffer[2].instruccion->instruccion,"sub"))
    {
        sub(info,info->buffer[2].instruccion,PC,4);
    }

    //Instruccion 6
    else if(!strcmp(info->buffer[2].instruccion->instruccion,"div"))
    {
        division(info,info->buffer[2].instruccion,PC,4);
    }

    //Instruccion 7
    else if(!strcmp(info->buffer[2].instruccion->instruccion,"sw"))
    {
        sw(info,info->buffer[2].instruccion,PC,4);
    }

    //Instruccion 8
    else if(!strcmp(info->buffer[2].instruccion->instruccion,"lw"))
    {
        lw(info,info->buffer[2].instruccion,PC,4);
    }

    //Instruccion 9
    else if(!strcmp(info->buffer[2].instruccion->instruccion,"addi"))
    {
        addi(info,info->buffer[2].instruccion,PC, 4);
    }

    //Instruccion 2
    else if(!strcmp(info->buffer[2].instruccion->instruccion,"subi"))
    {
        subi(info,info->buffer[2].instruccion,PC,4);
    }

    else if(!strcmp(info->buffer[2].instruccion->instruccion,"vacio"))
    {
        vacio(info,info->buffer[2].instruccion,PC, 4);
    }
}

void etapaWB(Informacion *info, int PC)
{
    if(!strcmp(info->buffer[3].instruccion->instruccion,"add"))
    {
        add(info,info->buffer[3].instruccion,PC, 5);
    }

    //Instruccion 2
    else if(!strcmp(info->buffer[3].instruccion->instruccion,"mul"))
    {
        mul(info,info->buffer[3].instruccion,PC,5);
    }

    //Instruccion 3
    else if(!strcmp(info->buffer[3].instruccion->instruccion,"j"))
    {
        jump(info,info->buffer[3].instruccion,PC,5);
    }

    //Instruccion 3
    else if(!strcmp(info->buffer[3].instruccion->instruccion,"beq"))
    {
        beq(info,info->buffer[3].instruccion,PC,5);
        
    }

    //Instruccion 5
    else if(!strcmp(info->buffer[3].instruccion->instruccion,"sub"))
    {
        sub(info,info->buffer[3].instruccion,PC,5);
    }

    //Instruccion 6
    else if(!strcmp(info->buffer[3].instruccion->instruccion,"div"))
    {
        division(info,info->buffer[3].instruccion,PC,5);
    }

    //Instruccion 7
    else if(!strcmp(info->buffer[3].instruccion->instruccion,"sw"))
    {
        sw(info,info->buffer[3].instruccion,PC,5);
    }

    //Instruccion 8
    else if(!strcmp(info->buffer[3].instruccion->instruccion,"lw"))
    {
        lw(info,info->buffer[3].instruccion,PC,5);
    }

    //Instruccion 9
    else if(!strcmp(info->buffer[3].instruccion->instruccion,"addi"))
    {
        addi(info,info->buffer[3].instruccion,PC, 5);
    }

    //Instruccion 2
    else if(!strcmp(info->buffer[3].instruccion->instruccion,"subi"))
    {
        subi(info,info->buffer[3].instruccion,PC,5);
    }

    else if(!strcmp(info->buffer[3].instruccion->instruccion,"vacio"))
    {
        vacio(info,info->buffer[3].instruccion,PC, 5);
    }
}

void escribirArchivoHazar(Informacion* informacion, int ciclo)
{
    FILE* archivo = fopen("salida2.csv" , "a");
    int i;

    if (ciclo == 1)
    {
        fprintf (archivo, "%s ; %s ; %s \n", "Etapas","Hazar de datos","Hazar de control");
    }

    fprintf(archivo, " %d ; %s ; %s ", ciclo, informacion->hazarDato, informacion->hazarControl );

    fprintf(archivo, "\n");

    informacion->hazarDato = "";
    informacion->hazarControl = "";

    fclose(archivo);
}

void escribirArchivoTraza(Informacion* informacion, int ciclo) 
{ 
    FILE *archivo = fopen("salida1.csv", "a"); 

    int i ;
    if (ciclo == 1)
    {
        fprintf (archivo, "%s ; %s ;%s ;%s ;%s ;%s \n", "Etapas","IF","ID","EX","MEM","WB");
    }

    fprintf(archivo, " %d ;", ciclo );

    for (i = 0; i < 5; i++)
    {
        if  (
        !strcmp(informacion->buffer[i].instruccion->instruccion,"add") ||
        !strcmp(informacion->buffer[i].instruccion->instruccion,"sub") ||
        !strcmp(informacion->buffer[i].instruccion->instruccion,"mul") ||
        !strcmp(informacion->buffer[i].instruccion->instruccion,"div")
        )
        {
            fprintf (archivo, "%s %s %s %s ;",informacion->buffer[i].instruccion->instruccion,informacion->buffer[i].instruccion->rd, informacion->buffer[i].instruccion->rs ,
            informacion->buffer[i].instruccion->rt);
        }

        else if (
        !strcmp(informacion->buffer[i].instruccion->instruccion,"addi") ||
        !strcmp(informacion->buffer[i].instruccion->instruccion,"subi")
        )
        {
            fprintf (archivo, "%s %s %s %d ;",informacion->buffer[i].instruccion->instruccion,informacion->buffer[i].instruccion->rt, informacion->buffer[i].instruccion->rs ,
            informacion->buffer[i].instruccion->inmediato);
        }

        else if (!strcmp(informacion->buffer[i].instruccion->instruccion,"lw") || !strcmp(informacion->buffer[i].instruccion->instruccion,"sw") ) 
        {
            fprintf (archivo, "%s %s %d(%s) ;",informacion->buffer[i].instruccion->instruccion,informacion->buffer[i].instruccion->rt, informacion->buffer[i].instruccion->inmediato ,
            informacion->buffer[i].instruccion->rs);
        }

        else if (!strcmp(informacion->buffer[i].instruccion->instruccion,"j") ) 
        {
            fprintf (archivo, "%s %s ;",informacion->buffer[i].instruccion->instruccion,informacion->buffer[i].instruccion->rd);
        }

        else if (!strcmp(informacion->buffer[i].instruccion->instruccion,"beq") ) 
        {
            fprintf (archivo, "%s %s %s ;",informacion->buffer[i].instruccion->instruccion,informacion->buffer[i].instruccion->rs, informacion->buffer[i].instruccion->rt, 
                informacion->buffer[i].instruccion->rd);
        }

        else if (
        !strcmp(informacion->buffer[i].instruccion->instruccion,"vacio") 
        )
        {
            fprintf (archivo, " ;");
        }       
    }

    fprintf(archivo, "\n");

    fclose(archivo); 
} 