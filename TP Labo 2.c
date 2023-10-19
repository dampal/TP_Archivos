//cambio cambio 123
//franco estuvo aca

#define FILENAME "propiedades.dat"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "validaciones.h"

//Crea el archivo propiedades.dat
//si la creacion es exitosa, devuelve un puntero activo al archivo.
//si no, tira error y termina la ejecución del programa.
FILE* crearDat(MAX_PROPIEDADES){

}

//HOLAAAAAAAAAAAA

//imprime una propiedad con el formato correspondiente.
void imprimirPropiedad(FILE* propiedades){

}

//impresion con formato del archivo de propiedades.
void listarDat(){
    //USAR IMPRIMIRPROPIEDAD()
    //submenu
    //1. listar todos
    //2. solo los activos
    //3. un tipo de propiedad
    //4. un rango de tiempo (min, max)
}

//impresion con formato del menu principal.
void mostrarMenu(){

}

//pide una entrada al usuario y valida que sea un caracter ascii
//si es valido, lo devuelve.
char ingresarOpcion(){

}

//inserta una propiedad nueva en el archivo propiedades, en la posicion de ID correspondiente.
//valida la entrada de cada campo, y pide entradas nuevas hasta que sea correcta.
//llena los IDs entre el ultimo registro lleno y el nuevo con registros vacíos.
void altaPropiedad(FILE* propiedades){

}

//busca una propiedad en el archivo segun ID.
//cambia el campo "fecha de salida" por la fecha actual.
//cambia el campo "activo" a cero.
//NO ESTOY SEGURO DE QUE ESTO ES LO QUE QUIERA LA PROFE
void bajaLogica(FILE* propiedades){

}

buscarPorID(propiedades){

}

buscarPorOp(propiedades){

}

//muestra un submenu de opciones.
//busca propiedades por ID o por operacion y luego tipo de propiedad
//segun la entrada del usuario
//emite los datos encontrados, o un mensaje si no se encuentra nada.
void buscarPropiedad(FILE* propiedades){
    //aca mostramos menu y pedimos opciones
    buscarPorID(propiedades);
    //o
    buscarPorOp(propiedades);
}

//muestra un submenu con opciones.
//modifica ciudad, barrio, precio, o fecha de salida.
//siempre validando la entrada del usuario segun el campo modificado.
//pide una confirmación antes de modificar el registro.
void modificarPropiedad(FILE* propiedades){

}

//crea un archivo "propiedades_bajas_<fecha>.xyz" con la fecha actual.
//en este graba todas las propiedades inactivas de "propiedades"
//simultaneamente elimina esos registros de "propiedades"
//devuelve un puntero activo al archivo de bajas.
FILE* bajaFisica(FILE* propiedades){

}

//imprime los registros de bajasXyz con el formato correspondiente.
void listarXyz(FILE* bajasXyz){

}

int main(){
    FILE* propiedades = crearDat();
    FILE* bajasXyz = NULL;
    while(1){
        mostrarMenu();
        char input = ingresarOpcion();
        switch input{
            case 'a':
                listarDat(propiedades);
                break;
            case 'b':
                altaPropiedad(propiedades);
                break;
            case 'c':
                buscarPropiedad(propiedades);
                break;
            case 'd':
                modificarPropiedad(propiedades);
                break;
            case 'e':
                bajaLogica(propiedades);
                break;
            case 'f':
                bajasXyz = bajaFisica(propiedades);
                break;
            case 'g':
                listarXyz(bajasXyz);
                break;
            case 'h':
                exit(0);
            default:
                printf("poneme una letra válida flaco");

        }
    }
    return 0;
}
