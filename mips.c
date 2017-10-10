#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "struct.h"
#include "funciones.c"
#include "lectura.c"

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