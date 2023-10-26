#define FILENAME "propiedades.dat"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

typedef struct Propiedad {
    int id;
    char fecha_ingreso[10];
    char zona[20];
    char ciudad_barrio[20];
    int dormitorios;
    int banos;
    float superficie_total;
    float superficie_cubierta;
    float precio;
    char moneda[6];
    char tipo_propiedad[20];
    char operacion[20];
    char fecha_salida[20];
    int flag_activo;
} propiedad_t

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
            return propiedades;
        } else if (tolower (opcion) == 'n'){
            //Abrir el archivo existente
            propiedades = fopen ("propiedades.dat", "rb+");
            if (propiedades == NULL){
                printf ("Error en la apertura del archivo\n");
                exit (1);
            }
            printf ("Archivo abierto exitosamente.\n");
            return propiedades;
        } else {
            printf ("Opci%cn inv%clida.\n", 162,160);
        }
    } while (tolower (opcion) != 's' || tolower (opcion) !='n');
}

//(PUNTO 5) Listado del contenido del archivo
/*imprime una propiedad con el formato correspondiente.*/
void imprimirPropiedad(FILE* propiedades, propiedad_t propiedad, int total, char opcion){
    printf("ID\tFecha de ingreso\tZona\tCiudad/Barrio\tDormitorios\tBa%cos\tSup. total\tSup. Cubierta\tPrecio\tMoneda\tOperacion\tActivo\n",164);
    fseek(propiedades, 0, SEEK_END);
    switch (opcion){
    case 'a': //todas las propiedades
        for (int i = 0; i <= total; i++){
            fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
            fread(&prop, sizeof(propiedad_t),1,);
            printf("%-5d%-9s%-20s%-20s%-2d%-2d%-10.2f%-10.2f%-10.2f%-5s%-13s%-19s\n", prop.id, prop.fecha_ingreso, prop.zona, prop.ciudad_barrio, prop.dormitorios, prop.banos, prop.superficie_total, prop.superficie_cubierta, prop.precio, prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fecha_salida, prop.flag_activo);
        }
        break;
    case 'b': //solo las activas
        for (int i = 0; i <= total; i++){
            fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
            fread(&prop, sizeof(propiedad_t),1,);
            if (prop.flag_activo == 1){
            printf("%-5d%-9s%-20s%-20s%-2d%-2d%-10.2f%-10.2f%-10.2f%-5s%-13s%-19s\n", prop.id, prop.fecha_ingreso, prop.zona, prop.ciudad_barrio, prop.dormitorios, prop.banos, prop.superficie_total, prop.superficie_cubierta, prop.precio, prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fecha_salida, prop.flag_activo);
            }
        }
        break;
    case 'c': //un tipo de propiedad
        for (int i = 0; i <= total; i++){
            fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
            fread(&prop, sizeof(propiedad_t),1,);
            if (strcmp(prop.tipo_propiedad, "Casa") == 0 || strcmp(prop.tipo_propiedad, "PH") == 0 || strcmp(prop.tipo_propiedad, "Departamento") == 0){
            printf("%-5d%-9s%-20s%-20s%-2d%-2d%-10.2f%-10.2f%-10.2f%-5s%-13s%-19s\n", prop.id, prop.fecha_ingreso, prop.zona, prop.ciudad_barrio, prop.dormitorios, prop.banos, prop.superficie_total, prop.superficie_cubierta, prop.precio, prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fecha_salida, prop.flag_activo);
            }
        }
        break;
    case 'd': //un rango de tiempo
        char fecha_inicio[9], fecha_fin[9];
        printf("Ingrese la fecha minima (formato: DDMMYYYY): ");
        scanf("%8s", fecha_inicio);
        while (!validarFecha(fecha_inicio)) {
            printf("Opción inválida. Por favor, ingrese una fecha con formato DDMMYYYY: ");
            scanf(" %8s", fecha_inicio);
        }
        printf("Ingrese la fecha maxima (formato: DDMMYYYY): ");
        scanf("%8s", fecha_fin);
        while (!validarFecha(fecha_fin)) {
            printf("Opción inválida. Por favor, ingrese una fecha con formato DDMMYYYY: ");
            scanf(" %8s", fecha_fin);
        }
        for (int i = 0; i <= total; i++){
            fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
            fread(&prop, sizeof(propiedad_t),1,);
            if (atoi(fecha_inicio) >= prop.fecha_ingreso && atoi(fecha_fin) <= prop.fecha_ingreso){
            printf("%-5d%-9s%-20s%-20s%-2d%-2d%-10.2f%-10.2f%-10.2f%-5s%-13s%-19s\n", prop.id, prop.fecha_ingreso, prop.zona, prop.ciudad_barrio, prop.dormitorios, prop.banos, prop.superficie_total, prop.superficie_cubierta, prop.precio, prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fecha_salida, prop.flag_activo);
            }
        }
    default:
        printf("Opci%cn inv%clida. Int%cntelo de nuevo.\n", 162, 160, 130);
        break;
    }
}
void listarDat(FILE* propiedades){
    propiedad_t prop;
    fseek(propiedades, 0, SEEK_END);
    int total = ftell(propiedades) / sizeof(propiedad_t);
    while (1){
        printf ("-----------------Listado-----------------\n");
        printf ("[a]. Listar todas las propiedades.\n");
        printf ("[b]. Listar solo las propiedades activas.\n");
        printf ("[c]. Listar un tipo propiedad.\n");
        printf ("[d]. Listar en un rango de tiempo.\n");
        char opcion = getchar();    
        imprimirPropiedad(prop, total, opcion);
    }
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

//(PUNTO 3) Validacion de los datos ingresados
//(PUNTO 6) Alta de una propiedad
/*inserta una propiedad nueva en el archivo propiedades, en la posicion de ID correspondiente.
valida la entrada de cada campo, y pide entradas nuevas hasta que sea correcta.
llena los IDs entre el ultimo registro lleno y el nuevo con registros vacíos.*/
int ingresoID(char num[]) {
    printf("Ingrese el ID de la propiedad: ");
    scanf("%5s", num);
    while (!validarInt(num)) {
        printf("Opción inválida. Por favor, ingrese un número entero: ");
        scanf(" %5s", num);
    }
    return atoi(num); 
}
void elegirMoneda(propiedad_t propiedad){
    char opcion;
    printf("Moneda de la propiedad:\n[A]. ARS\n[U]. USD\n");
    printf ("Seleccione el tipo de moneda: ");
    scanf (" %c", &opcion);
    opcion = tolower (opcion);
    while (opcion != 'a' && opcion !='u'){
        printf("Opci%cn inv%clida. Por favor, ingrese una opci%cn v%clida (A/U): ", 162,160,162,160);
        scanf(" %c", &opcion);
        opcion = tolower (opcion);
    }
    if (opcion == 'a'){
        strcpy (nuevo.moneda, "PESOS");
    } else {
        strcpy (nuevo.moneda, "USD");
    }
}
void elegirPropiedad(propiedad_t propiedad) { 
    char opcion;
    printf("Tipo de propiedad:\n[C]. Casa\n[D]. Departamento\n[P]. PH\n");
    printf ("Seleccione el tipo de propiedad: ");
    scanf (" %c", &opcion);
    opcion = tolower (opcion);
    while (opcion != 'c' && opcion !='d' && opcion !='p'){
        printf("Opci%cn inv%clida. Por favor, ingrese una opci%cn v%clida (C/D/P): ", 162,160,162,160);
        scanf(" %c", &opcion);
        opcion = tolower (opcion);
    }
    if (opcion == 'c'){
        strcpy (propiedad.tipo_propiedad, "Casa");
    } else if (opcion == 'd') {
        strcpy (propiedad.tipo_propiedad, "Departamento");
    } else {
        strcpy (propiedad.tipo_propiedad, "PH");
    }
}
void elegirOperacion(propiedad_t propiedad) {
    char opcion;
    printf("Tipo de operacion:\n[V]. Venta\n[A]. Alquiler\n[T]. Alquiler Temporal\n");
    printf ("Seleccione el tipo de propiedad: ");
    scanf (" %c", &opcion);
    opcion = tolower (opcion);
    while (opcion != 'a' && opcion !='v' && opcion !='t'){
        printf("Opci%cn inv%clida. Por favor, ingrese una opci%cn v%clida (V/A/T): ", 162,160,162,160);
        scanf(" %c", &opcion);
        opcion = tolower (opcion);
    }
    if (opcion == 'v'){
        strcpy (propiedad.operacion, "Venta");
    } else if (opcion == 'a') {
        strcpy (propiedad.operacion, "Alquiler");
    } else {
        strcpy (propiedad.operacion, "Alquiler temporal");
    }
}

void altaPropiedad(FILE* propiedades){
    char num[20], fecha[9], letra[20];
    propiedad_t nuevo;
    propiedad_t dato;
    int id;
    do {
        id=ingresoID(num);
        fseek(propiedades, 0, SEEK_END);
        int totalReg = ftell(propiedades) / sizeof(propiedad_t);
        if (id <= totalReg){
            fseek (propiedades, (id-1)*sizeof (propiedad_t), SEEK_SET);
            fread (&dato, sizeof(propiedad_t), 1, propiedades);
            if (dato.id !=0){
                printf("La posici%cn %d ya est%c ocupada.\n", 162, id, 160);
            } else {
                nuevo.id = id;
            }
        } else {
            int filasInt = id - totalReg;
            propiedad_t vacio = {0,'0','0','0',0,0,0,0,0,'0','0','0'}
            fseek(propiedades, 0, SEEK_END);
            for (int i=0; i < filasInt ; i++){
                fwrite(&vacio, sizeof(propiedad_t),1,propiedades);
            }
            nuevo.id=id;
        }
    } while (dato.id !=0 && id <= totalReg);

    //verifico que la fecha no sea mayor a la actual
    time_t tiempo_actual;
    struct tm fecha_actual;
    struct tm fecha_ingresada;

    //obtengo la fecha actual y la guardo
    time(&tiempo_actual);
    tm.fecha_actual = localtime(&tiempo_actual);

    printf("Ingrese la fecha actual (formato: DDMMYYYY): ");
    scanf("%8s", fecha);
    while (!validarFecha(fecha)) {
        printf("Opción inválida. Por favor, ingrese una fecha con formato DDMMYYYY: ");
        scanf(" %8s", fecha);
    }
    //guardo lo que ingreso en los campos
    int dd= (fecha[0]-48)*10 + (fecha[1]-48);
    int mm = (fecha[2]-48)*10 + (fecha[3]-48);
    fecha_ingresada.tm_year = atoi(fecha + 4);
    fecha_ingresada.tm_mon = mm;
    fecha_ingresada.tm_mday = dd;
    //VER COMPARACION DE LAS FECHAS

    printf ("Ingrese la zona de la propiedad: ");
    scanf (" %19s", letra);
    while (!validarTexto(letra)){
        printf("Opci%cn inv%clida. Por favor, ingrese una zona v%clida: ", 162,160, 160);
        scanf(" %19s", letra);
    }
    validarMayus(letra);
    strcpy(nuevo.zona, letra);

    printf ("Ingrese la ciudad/barrio de la propiedad: ");
    scanf (" %19s", letra);
    while (!validarTexto(letra)){
        printf("Opci%cn inv%clida. Por favor, ingrese una ciudad/barrio v%clida: ", 162,160, 160);
        scanf(" %19s", letra);
    }
    validarMayus(letra);
    strcpy(nuevo.ciudad_barrio, letra);

    printf ("Ingrese la cantidad de dormitorios de la propiedad: ");
    scanf (" %19s", num);
    while (!validarInt (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese una cantidad v%clida: ", 162,160, 160);
        scanf(" %19s", num);
    }
    int dormi = atoi(num);
    nuevo.dormitorios = dormi;

    printf ("Ingrese la cantidad de ba%cos de la propiedad: ",164);
    scanf (" %19s", num);
    while (!validarInt (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese una cantidad v%clida: ", 162,160, 160);
        scanf(" %19s", num);
    }
    int bano = atoi(num);
    nuevo.banos = bano;

    printf ("Ingrese la superficie total de la propiedad: ");
    scanf (" %19s", num);
    while (!validarFloat (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese una superficie v%clida(agregando '.'): ", 162,160, 160);
        scanf(" %19s", num);
    }
    float s_total = atof(num);
    nuevo.superficie_total = s_total;

    printf ("Ingrese la superficie cubierta de la propiedad: ");
    scanf (" %19s", num);
    while (!validarFloat (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese una superficie v%clida(agregando '.'): ", 162,160, 160);
        scanf(" %19s", num);
    }
    float s_cub = atof(num);
    nuevo.superficie_cubierta = s_cub;

    printf ("Ingrese el valor de la propiedad: ");
    scanf (" %19s", num);
    while (!validarFloat (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese un valor v%clida(agregando '.'): ", 162,160, 160);
        scanf(" %19s", num);
    }
    float precio = atof(num);
    nuevo.precio = precio;
    elegirMoneda(nuevo);
    elegirPropiedad(nuevo);
	elegirOperacion(nuevo);

    //Guardo el nuevo struct en el lugar que corresponda
    /*si todo esta ok, la propiedad queda activa*/
    nuevo.flag_activo=1;
    fseek (propiedades, (id-1)*sizeof(propiedad_t), SEEK_SET);
    fwrite(&nuevo, sizeof(propiedad_t), 1, propiedades);
    printf("Propiedad agregada exitosamente.\n");
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

//(PUNTO 7) Busqueda de datos
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

//(PUNTO 8) Modificar datos
//muestra un submenu con opciones.
//modifica ciudad/barrio, precio, o fecha de salida->(validar fecha y tambien modificar la baja logica).
//siempre validando la entrada del usuario (con id) segun el campo modificado.
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
                printf("Gracias por confiar en Inmobiliaria Bubú. Saliendo del programa...\n");
                exit(0);
            default:
                printf("Opci%cn inv%clida. Int%cntelo de nuevo.\n", 162, 160, 130);
        }   
    }
    return 0;
}