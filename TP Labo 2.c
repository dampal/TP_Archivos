//cambio cambio 123

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

    int nReg,aux;
    char = id[6];

    propiedad_n busqueda;

    do{
        printf ("Ingrese el ID a buscar\n");
        scanf (" %s",id);

        if (validarInt(id) == 0){
            printf("Error, ingrese otro ID\n");
        }

    } while (validarInt(id) == 0);

    aux = atoi(id);

    fseek(propiedades,0,SEEK_END);
    nReg=ftell(propiedades)/sizeof(propiedad_n);

    if (id <= nReg){
        fseek(propiedades,(aux-1)*sizeof(propiedad_n),SEEK_SET);

        fread(&busqueda,sizeof(propiedad_n),1,propiedades);

        if (busqueda.id == aux){
            imprimirRegistro(busqueda)
        } else {
            printf ("Error, el registro est%c vac%co\n",131,161);}



    } else {
    printf ("Error, no existe el ID ingresado\n");}

}

buscarPorOp(propiedades){

    char * popcion = elegirOperacion();

    char tipoOperacion[50];
    char tipoPropiedad[50];
    printf("Ingrese el tipo de operación (Venta, Alquiler, Alquiler temporal): ");
    scanf("%s", tipoOperacion);
    printf("Ingrese el tipo de propiedad (PH, Departamento, Casa, ...): ");
    scanf("%s", tipoPropiedad);

    struct propiedad filtro;
    fseek(propiedades,0,SEEK_SET);


    printf ("Filtro por Operaci%cn\n",162);
    while (fread(&filtro, sizeof(struct filtro), 1, archivo) == 1) {
        if (strcmp(filtro.operacion, tipoOperacion) == 0) {
            imprimirRegistro(filtro);
        }
    }

    fseek(pArchivo,0,SEEK_SET);

    printf ("Filtro por Operaci%cn y por Propiedad\n",162);
    while (fread(&filtro, sizeof(struct filtro), 1, archivo) == 1) {
        if (strcmp(filtro.operacion, tipoOperacion) == 0 && strcmp(filtro.tipoPropiedad, tipoPropiedad) == 0) {
            imprimirRegistro(filtro);
        }
    }



}

//muestra un submenu de opciones.
//busca propiedades por ID o por operacion y luego tipo de propiedad
//segun la entrada del usuario
//emite los datos encontrados, o un mensaje si no se encuentra nada.
void buscarPropiedad(FILE* propiedades){

    char subopcion;
    printf ("Seleccione m%ctodo de b%csqueda:\n\n",130,163);
    printf ("[a]. B%csqueda por ID\n",163);
    printf ("[b]. B%csqueda por Operaci%cn\n",163,162);

    do{
        scanf (" %c",&subopcion);
        subopcion = tolower(subopcion);

        if (subopcion != 'a' && subopcion != 'b')
            printf("La opci%cn es incorrecta, ingrese otra opci%cn.\n",162,162);

    } while (subopcion != 'a' && subopcion != 'b');


    switch (subopcion){
        case 'a':
            buscarPorID(propiedades);
            break;
        case 'b':
            buscarPorOp(propiedades);
            break;

    }


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
