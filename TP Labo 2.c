#define FILENAME "propiedades.dat"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

//(PUNTO 4) Crea el archivo propiedades.dat
//crea o sobreescribe el existente
//si no, tira error y termina la ejecución del programa.
FILE* crearDat(){
    char opcion;
    do {
        printf ("¿Desea crear un nuevo archivo o sobrescribirlo?(S/N): ");
        scanf("%c", &opcion);

        if (tolower (opcion) == 's'){
            //crea/sobreescribe el archivo
            propiedades = fopen ("propiedades.dat", "w+b");
            if (propiedades == NULL){
                printf ("Error en la apertura del archivo\n");
                exit (1);
            }
            printf ("Archivo creado o sobrescrito exitosamente.\n");
        } else if (tolower (opcion) == 'n'){
            //Abrir el archivo existente
            propiedades = fopen ("propiedades.dat", "rb+");
            if (propiedades == NULL){
                printf ("Error en la apertura del archivo\n");
                exit (1);
            }
            printf ("Archivo abierto exitosamente.\n");
        } else {
            printf ("Opci%cn inv%clida.\n", 162,160);
            exit (1;)
        }
        return propiedades;
    } while (tolower (opcion) != 's' || tolower (opcion) !='n');
}

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

//(PUNTO 1) Impresion con formato del menu principal.
void mostrarMenu(){
    printf ("--------Menú Inicial--------\n");
    printf ("[a]. Listar propiedades.\n");
    printf ("[b]. Alta de una propiedad.\n");
    printf ("[c]. Buscar propiedad.\n");
    printf ("[d]. Modificar propiedades.\n");
    printf ("[e]. Baja logica de una propiedad.\n");
    printf ("[f]. Baja fisica de una propiedad.\n");
    printf ("[g]. Listar baja fisica de propiedades.\n");
    printf ("[h]. Salir.\n");
    
}

//inserta una propiedad nueva en el archivo propiedades, en la posicion de ID correspondiente.
//valida la entrada de cada campo, y pide entradas nuevas hasta que sea correcta.
//llena los IDs entre el ultimo registro lleno y el nuevo con registros vacíos.
void altaPropiedad(FILE* propiedades){
    //esperando a sol
}

//busca una propiedad en el archivo segun ID.
//cambia el campo "fecha de salida" por la fecha actual.
//cambia el campo "activo" a cero.
//NO ESTOY SEGURO DE QUE ESTO ES LO QUE QUIERA LA PROFE
void bajaLogica(FILE* propiedades){
    //franco???
}

buscarPorID(propiedades){
    //franco
}

buscarPorOp(propiedades){
    //franco
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
        char input = getchar();
        switch (input) {
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
            //cerrar el archivo y salir del programa
                fclose (propiedades);
                printf("Gracias por confiar en Inmobiliaria Bubu\n");
                exit(0);
            default:
                printf("Opci%cn inv%clida. Int%cntelo de nuevo.\n", 162, 160, 130);
        }   
    }
    return 0;
}