#define FILENAME "propiedades.dat"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

typedef struct Propiedad {
    int id;
    char fecha_ingreso[30];
    char zona[30];
    char ciudad_barrio[30];
    int dormitorios;
    int banos;
    float superficie_total;
    float superficie_cubierta;
    float precio;
    -char moneda[10];
    -char tipo_propiedad[30];
    -char operacion[30];
    //fecha de salida y 
    int flag_activo;
} propiedad_n

//(PUNTO 4) Crea el archivo 'propiedades.dat'
/*crea o sobreescribe el existente
si no, tira error y termina la ejecución del programa.*/
FILE* crearDat(){
    char opcion;
    do {
        printf ("¿Desea crear un nuevo archivo o sobrescribirlo?(S/N): ");
        scanf("%c", &opcion);

        if (tolower (opcion) == 's'){
            //Crea/sobreescribe el archivo
            propiedades = fopen ("propiedades.dat", "w+b");
            if (propiedades == NULL){
                printf ("Error en la apertura del archivo\n");
                exit (1);
            }
            printf ("Archivo creado o sobrescrito exitosamente.\n");
        } else if (tolower (opcion) == 'n'){
            //Abrir el archivo existente
            propiedades = fopen ("propiedades.dar", "rb+");
            if (propiedades == NULL){
                printf ("Error en la apertura del archivo\n");
                exit (1);
            }
            printf ("Archivo abierto exitosamente.\n");
        } else {
            printf ("Opci%dn inv%alida.\n", 162,160);
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
    ingresarOpcion();    
}
/*pide una entrada al usuario y valida que sea un caracter ascii
si es valido, lo devuelve.*/
char ingresarOpcion(){
    char opcion;
    printf ("Ingrese su opcion: ");
    scanf (" %c", &opcion);
    opcion = tolower (opcion);
    while (!validarOpcion(opcion)) {
        printf("Opci%dn inv%dlida. Por favor, ingrese una opci%dn v%dlida (a-h): ", 162,160,162,160);
        scanf(" %c", &opcion);
        opcion = tolower(opcion);
    }
    return opcion;
}

//(PUNTO 6) Alta de una propiedad
/*inserta una propiedad nueva en el archivo propiedades, en la posicion de ID correspondiente.
valida la entrada de cada campo, y pide entradas nuevas hasta que sea correcta.
llena los IDs entre el ultimo registro lleno y el nuevo con registros vacíos.*/
void altaPropiedad(FILE* propiedades){
    char num[20], fecha[20], letra[20];
    propiedad_n;

    printf ("Ingrese el ID de la propiedad: ");
    scanf ("%s", num);

    while (!validarInt (num)){
        printf("Opci%dn inv%dlida. Por favor, ingrese un n%dmero entero: ", 162,160,163);
        scanf(" %s", num);
    }
    int id = atoi(num);

    //voy al final y obtengo la cantidad de propiedades que guarde
    fseek(propiedades, 0, SEEK_END);
    int totalReg= ftell(propiedades) / sizeof(propiedad_n);
    //veo que el id este dentro del total de propiedades
    if (id <= totalReg){
        fseek (propiedades, (id-1)*sizeof (propiedad_n), SEEK_SET);
        propiedad_n dato;
        fread (&dato, sizeof(propiedad_n), 1, propiedades);
        //veo si hay datos o no
        if (dato.id != 0){
            printf("La posici%dn %d ya est%d ocupada.\n", 162, id, 160);
            //tengo que volver a pedir un nuevo id
        } else {
            propiedad_n.id=id;
        }
    } else {
        int filasInt = id - totalReg;
        propiedad_n vacio {0,'0','0','0',0,0,0,0,0,'0','0','0'}
        fseek(propiedades, 0, SEEK_END);
        for (int i=0; i < filasInt ; i++){
            fwrite(&vacio, sizeof(propiedad_n),1,propiedades);
        }
        propiedad_n.id=id;
    }

    printf ("Ingrese la fecha actual: ");
    scanf ("%s", fecha);
    while (!validarFecha (fecha)){
        printf("Opci%dn inv%dlida. Por favor, ingrese una fecha con formato DDMMYYYY: ", 162,160);
        scanf(" %s", fecha);
    }
    //VERIFICAR SI ES LA REAL CON LA FECHA DE LA COMPU
    propiedad_n.fecha_ingreso=fecha;

    printf ("Ingrese la zona de la propiedad: ");
    scanf (" %s", letra);
    while (!validarTexto(letra)){
        printf("Opci%dn inv%dlida. Por favor, ingrese una zona v%dlida: ", 162,160, 160);
        scanf(" %s", letra);
    }
    //CHEQUEAR QUE ESTE USADA BIEN LA FUNCION
    propiedad_n.zona = validarMayus(letra);

    printf ("Ingrese la ciudad/barrio de la propiedad: ");
    scanf (" %s", letra);
    while (!validarTexto(letra)){
        printf("Opci%dn inv%dlida. Por favor, ingrese una ciudad/barrio v%dlida: ", 162,160, 160);
        scanf(" %s", letra);
    }
    //CHEQUEAR QUE ESTE USADA BIEN LA FUNCION
    propiedad_n.ciudad_barrio = validarMayus(letra);

    printf ("Ingrese la cantidad de dormitorios de la propiedad: ");
    scanf (" %s", num);
    while (!validarInt (num)){
        printf("Opci%dn inv%dlida. Por favor, ingrese una cantidad v%dlida: ", 162,160, 160);
        scanf(" %s", num);
    }
    int dormi = atoi(num);
    propiedad_n.dormitorios = dormi;

    printf ("Ingrese la cantidad de ba%dos de la propiedad: ",164);
    scanf (" %s", num);
    while (!validarInt (num)){
        printf("Opci%dn inv%dlida. Por favor, ingrese una cantidad v%dlida: ", 162,160, 160);
        scanf(" %s", num);
    }
    int bano = atoi(num);
    propiedad_n.dormitorios = bano;

    printf ("Ingrese la superficie total de la propiedad: ");
    scanf (" %s", num);
    while (!validarFloat (num)){
        printf("Opci%dn inv%dlida. Por favor, ingrese una superficie v%dlida(agregando '.'): ", 162,160, 160);
        scanf(" %s", num);
    }
    float s_total = atoi(num);
    propiedad_n.superficie_total = s_total;

    printf ("Ingrese la superficie cubierta de la propiedad: ");
    scanf (" %s", num);
    while (!validarFloat (num)){
        printf("Opci%dn inv%dlida. Por favor, ingrese una superficie v%dlida(agregando '.'): ", 162,160, 160);
        scanf(" %s", num);
    }
    float s_cub = atoi(num);
    propiedad_n.superficie_total = s_cub;

    printf ("Ingrese el valor de la propiedad: ");
    scanf (" %s", num);
    while (!validarFloat (num)){
        printf("Opci%dn inv%dlida. Por favor, ingrese un valor v%dlida(agregando '.'): ", 162,160, 160);
        scanf(" %s", num);
    }
    float precio = atoi(num);
    propiedad_n.superficie_total = precio;

//FALTA MONEDA, PROPIEDAD Y OPERACION

    //guardo el nuevo struc en el lugar que corresponda
    /*si todo esta ok, la propiedad queda activa*/
    propiedad_n.flag_activo=1;
    fseek (propiedades, (id-1)*sizeof(struct Propiedad), SEEK_SET);
    fwrite(&propiedad_n, sizeof(struct Propiedad), 1, propiedades);
    printf("Propiedad agregada exitosamente.\n");
    

    char ciudad_barrio [30] = validarTexto();
    int dormitorios = validarNumero();
    int baños = validarNumero();
    float supTotal = validarNumero();
    float supCubierta = validarNumero();
    float precio = validarNumero();
    char moneda = validarMoneda();
    char propiedad = validarPropiedad();
    char operacion = validarOperacion();

    //Fecha de Salida
    //Activo
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
                printf("Gracias por confiar en Inmobiliaria Bubú. Saliendo del programa...\n");
                exit(0);
            default:
                printf("Opci%dn inv%dlida. Int%dntelo de nuevo.\n", 162, 160, 130);
        }   
    }
    return 0;
}