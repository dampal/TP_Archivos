#define FILENAME "propiedades.dat"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

typedef struct Propiedad {
    int id;
    char fecha_ingreso[9];
    char zona[30];
    char ciudad_barrio[30];
    int dormitorios;
    int banos;
    float superficie_total;
    float superficie_cubierta;
    float precio;
    char moneda[6];
    char tipo_propiedad[15];
    char operacion[20];
    char fecha_salida[9];
    int flag_activo;
} propiedad_t;

//(PUNTO 4) Crea el archivo 'propiedades.dat'
/*crea o sobreescribe el existente
si no, tira error y termina la ejecución del programa.*/
FILE * crearDat(){
    FILE * propiedades;
    char opcion;
    do {
        printf ("%cDesea crear un nuevo archivo o sobrescribirlo?(S/N): ",168);
        scanf("%c", &opcion);
        fflush(stdin);
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
    return NULL;
}

//(PUNTO 5) Listado del contenido del archivo
/*imprime una propiedad con el formato correspondiente.*/
char elegirPropiedad() {
    char opcion;
    printf("Tipo de propiedad:\n[C]. Casa\n[D]. Departamento\n[P]. PH\n");
    printf ("Seleccione el tipo de propiedad: ");
    scanf (" %c", &opcion);
    fflush(stdin);
    opcion = tolower (opcion);
    while (opcion != 'c' && opcion !='d' && opcion !='p'){
        printf("Opci%cn inv%clida. Por favor, ingrese una opci%cn v%clida (C/D/P): ", 162,160,162,160);
        scanf(" %c", &opcion);
        fflush(stdin);
        opcion = tolower (opcion);
    }
    return opcion;
}

void imprimirEncabezado(){
    printf("ID %c Ingreso %c       Zona       %c  Ciudad/Barrio  %c Dormitorios %c Ba%cos %c Sup.Total %c Sup.Cubierta %c  Precio  %c Moneda %c Propiedad %c     Operaci%cn     %c Salida %c Activo\n",\
            124,124,124,124,124,164,124,124,124,124,124,124,162,124,124);
}

void imprimirPropiedad(propiedad_t prop){
     printf("%-3d%c%-9s%c%-18s%c%-17s%c%-13d%c%-7d%c%-11.2f%c%-14.2f%c%-10.2f%c%-8s%c%-11s%c%-19s%c%-8s%c%-7d\n",
           prop.id,124, prop.fecha_ingreso,124, prop.zona,124, prop.ciudad_barrio,124, prop.dormitorios,124, prop.banos,124,
           prop.superficie_total,124, prop.superficie_cubierta,124, prop.precio,124, prop.moneda,124, prop.tipo_propiedad,124,
           prop.operacion,124, prop.fecha_salida,124, prop.flag_activo);
}
void listarDat(FILE* propiedades){
    char opcion, op, fecha_inicio[9], fecha_fin[9];
    int aux_fecha, aux_inicio, aux_fin;
    propiedad_t prop;
    fseek(propiedades, 0, SEEK_END);
    int total = ftell(propiedades) / sizeof(propiedad_t);
    printf ("-----------------Listado-----------------\n");
    printf ("[a]. Listar todas las propiedades.\n");
    printf ("[b]. Listar solo las propiedades activas.\n");
    printf ("[c]. Listar un tipo propiedad.\n");
    printf ("[d]. Listar en un rango de tiempo.\n");
    scanf (" %c", &opcion);
    opcion = tolower(opcion);
    fflush (stdin);
    switch (opcion){
        case 'a': //todas las propiedades
            imprimirEncabezado();
            for (int i = 1; i < total; i++){
                fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
                fread(&prop, sizeof(propiedad_t), 1, propiedades);
                imprimirPropiedad(prop);
            }
            break;
        case 'b': //solo las activas
            imprimirEncabezado();
            for (int i = 1; i < total; i++){
                fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
                fread(&prop, sizeof(propiedad_t), 1, propiedades);
                if (prop.flag_activo == 1){
                    imprimirPropiedad(prop);
                }
            }
            break;
        case 'c': //un tipo de propiedad
            op = elegirPropiedad();
            imprimirEncabezado();
            for (int i = 1; i <= total; i++){
                fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
                fread(&prop, sizeof(propiedad_t),1, propiedades);
                if (strcmp(prop.tipo_propiedad, "Casa") == 0 && op == 'c'){
                    imprimirPropiedad(prop);
                } else if (strcmp(prop.tipo_propiedad, "PH") == 0 && op == 'p'){
                    imprimirPropiedad(prop);
                } else if (strcmp(prop.tipo_propiedad, "Departamento") == 0 && op == 'd') {
                    imprimirPropiedad(prop);
                }
            }
            break;
        case 'd': //un rango de tiempo
            printf("Ingrese la fecha m%cnima (formato: DDMMYYYY): ", 161);
            scanf("%8s", fecha_inicio);
            fflush(stdin);
            while (!validarFecha(fecha_inicio)) {
                printf("Opción inválida. Por favor, ingrese una fecha con formato DDMMYYYY: ");
                scanf(" %8s", fecha_inicio);
                fflush(stdin);
            }
            aux_inicio = convertirFecha(fecha_inicio);
            printf("Ingrese la fecha m%cxima (formato: DDMMYYYY): ", 160);
            scanf("%8s", fecha_fin);
            fflush(stdin);
            while (!validarFecha(fecha_fin)) {
                printf("Opción inválida. Por favor, ingrese una fecha con formato DDMMYYYY: ");
                scanf(" %8s", fecha_fin);
                fflush(stdin);
            }
            aux_fin = convertirFecha (fecha_fin);
            imprimirEncabezado();
            for (int i = 0; i < total; i++){
                fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
                fread(&prop, sizeof(propiedad_t),1, propiedades);
                aux_fecha = convertirFecha(prop.fecha_ingreso);
                if (aux_inicio <= aux_fecha && aux_fin >= aux_fecha){
                    imprimirPropiedad(prop);
                }
            }
            break;
        default:
            printf("Opci%cn inv%clida. Int%cntelo de nuevo.\n", 162, 160, 130);
            break;
    }
}

//(PUNTO 1) Impresion con formato del menu principal.
void mostrarMenu(){
    printf ("--------Men%c Inicial--------\n",163);
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
    fflush (stdin);
    while (!validarInt(num)) {
        printf("Opción inválida. Por favor, ingrese un número entero: ");
        scanf(" %5s", num);
        fflush (stdin);
    }
    return atoi(num);
}
char elegirMoneda(){
    char opcion;
    printf("Moneda de la propiedad:\n[A]. ARS\n[U]. USD\n");
    printf ("Seleccione el tipo de moneda: ");
    scanf (" %c", &opcion);
    fflush(stdin);
    opcion = tolower (opcion);
    while (opcion != 'a' && opcion !='u'){
        printf("Opci%cn inv%clida. Por favor, ingrese una opci%cn v%clida (A/U): ", 162,160,162,160);
        scanf(" %c", &opcion);
        fflush(stdin);
        opcion = tolower (opcion);
    }
    return opcion;
}
char elegirOperacion() {
    char opcion;
    printf("Tipo de operacion:\n[V]. Venta\n[A]. Alquiler\n[T]. Alquiler Temporal\n");
    printf ("Seleccione el tipo de operaci%cn: ", 162);
    scanf (" %c", &opcion);
    opcion = tolower (opcion);
    while (opcion != 'a' && opcion !='v' && opcion !='t'){
        printf("Opci%cn inv%clida. Por favor, ingrese una opci%cn v%clida (V/A/T): ", 162,160,162,160);
        scanf(" %c", &opcion);
        opcion = tolower (opcion);
    }
    return opcion;
}

void altaPropiedad(FILE* propiedades){
    char num[20], fecha[9], letra[30];
    propiedad_t nuevo;
    propiedad_t dato;
    propiedad_t vacio = {0,"0","0","0",0,0,0,0,0,"0","0","0","0",0};
    int id = 0, totalReg = 0, resul;
    printf ("---------------Alta---------------\n");
    id = ingresoID(num);
    do {
        fseek(propiedades, 0, SEEK_END);
        totalReg = ftell(propiedades) / sizeof(propiedad_t);
        if (id <= totalReg){
            fseek (propiedades, (id-1)*sizeof(propiedad_t), SEEK_SET);
            fread (&dato, sizeof(propiedad_t), 1, propiedades);
            if (dato.id != 0){
                printf("La posici%cn %d ya est%c ocupada.\n", 162, id, 160);
                id = ingresoID(num);
            } else {
                nuevo.id = id;
            }
        } else {
            int filasInt = id - totalReg;
            fseek(propiedades, 0, SEEK_END);
            for (int i = 0; i < filasInt ; i++){
                fwrite(&vacio, sizeof(propiedad_t),1,propiedades);
            }
            nuevo.id = id;
        }
    } while (dato.id !=0 && id <= totalReg);

    printf("Ingrese la fecha de ingreso(formato: DDMMYYYY): ");
    scanf("%8s", fecha);
    fflush(stdin);
    while (!validarFecha(fecha) && !compararFecha(fecha)) {
        printf("Opción inválida. Por favor, ingrese una fecha con formato DDMMYYYY: ");
        scanf(" %8s", fecha);
        fflush(stdin);
    }
    strcpy(nuevo.fecha_ingreso, fecha);

    printf ("Ingrese la zona de la propiedad: ");
    gets(letra);
    fflush(stdin);
    while (!validarTexto(letra)){
        printf("Opci%cn inv%clida. Por favor, ingrese una zona v%clida: ", 162,160, 160);
        gets(letra);
        fflush(stdin);
    }
    validarMayus(letra);
    strcpy(nuevo.zona, letra);

    printf ("Ingrese la ciudad/barrio de la propiedad: ");
    gets(letra);
    fflush(stdin);
    while (!validarTexto(letra)){
        printf("Opci%cn inv%clida. Por favor, ingrese una ciudad/barrio v%clida: ", 162,160, 160);
        gets(letra);
        fflush(stdin);
    }
    validarMayus(letra);
    strcpy(nuevo.ciudad_barrio, letra);

    printf ("Ingrese la cantidad de dormitorios de la propiedad: ");
    scanf (" %19s", num);
    fflush(stdin);
    while (!validarInt (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese una cantidad v%clida: ", 162,160, 160);
        scanf(" %19s", num);
        fflush(stdin);
    }
    int dormi = atoi(num);
    nuevo.dormitorios = dormi;

    printf ("Ingrese la cantidad de ba%cos de la propiedad: ",164);
    scanf (" %19s", num);
    fflush(stdin);
    while (!validarInt (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese una cantidad v%clida: ", 162,160, 160);
        scanf(" %19s", num);
        fflush(stdin);
    }
    int bano = atoi(num);
    nuevo.banos = bano;

    printf ("Ingrese la superficie total de la propiedad: ");
    scanf (" %19s", num);
    fflush(stdin);
    while (!validarFloat (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese una superficie v%clida(agregando '.'): ", 162,160, 160);
        scanf(" %19s", num);
        fflush(stdin);
    }
    float s_total = atof(num);
    nuevo.superficie_total = s_total;

    printf ("Ingrese la superficie cubierta de la propiedad: ");
    scanf (" %19s", num);
    fflush(stdin);
    while (!validarFloat (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese una superficie v%clida(agregando '.'): ", 162,160, 160);
        scanf(" %19s", num);
        fflush(stdin);
    }
    float s_cub = atof(num);
    nuevo.superficie_cubierta = s_cub;

    printf ("Ingrese el valor de la propiedad: ");
    scanf (" %19s", num);
    fflush(stdin);
    while (!validarFloat (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese un valor v%clida(agregando '.'): ", 162,160, 160);
        scanf(" %19s", num);
        fflush(stdin);
    }
    float precio = atof(num);
    nuevo.precio = precio;
    char opcionMoneda = elegirMoneda();
    if (opcionMoneda == 'a') {
    strcpy(nuevo.moneda, "PESOS");
    } else {
    strcpy(nuevo.moneda, "USD");
    }
    char opcionPropiedad = elegirPropiedad();
    if (opcionPropiedad == 'c'){
        strcpy (nuevo.tipo_propiedad, "Casa");
    } else if (opcionPropiedad == 'd') {
        strcpy (nuevo.tipo_propiedad, "Depto.");
    } else {
        strcpy (nuevo.tipo_propiedad, "PH");
    }
    char opcionOperacion = elegirOperacion();
    if (opcionOperacion == 'v'){
        strcpy (nuevo.operacion, "Venta");
    } else if (opcionOperacion == 'a') {
        strcpy (nuevo.operacion, "Alquiler");
    } else {
        strcpy (nuevo.operacion, "Alquiler temporal");
    }
    fflush(stdin);

    //Guardo el nuevo struct en el lugar que corresponda
    /*si todo esta ok, la propiedad queda activa*/
    nuevo.flag_activo = 1;
    fseek (propiedades, (id-1)*sizeof(propiedad_t), SEEK_SET);
    fwrite(&nuevo, sizeof(propiedad_t), 1, propiedades);
    printf("Propiedad agregada exitosamente.\n");
}

//(PUNTO 7) Busqueda de datos
/*muestra un submenu de opciones.
busca propiedades por ID o por operacion y luego tipo de propiedad.
emite los datos encontrados, o un mensaje si no se encuentra nada.*/
void buscarPorID(FILE * propiedades){
    int nReg = 0, aux_id = 0;
    char id[6];
    propiedad_t busqueda;

    aux_id = ingresoID(id);

    fseek(propiedades, 0, SEEK_END);
    nReg = ftell(propiedades)/sizeof(propiedad_t);

    if (aux_id <= nReg){
        fseek(propiedades,(aux_id-1)*sizeof(propiedad_t),SEEK_SET);

        fread(&busqueda,sizeof(propiedad_t),1,propiedades);

        if (busqueda.id == aux_id){
            imprimirPropiedad(busqueda);
        } else {
            printf ("Error, el registro est%c vac%co.\n",131,161);}
    } else {
        printf ("Error, no existe el ID ingresado\n");
        }
}
void buscarPorOp(FILE * propiedades){
    char operacion, propiedad;
    propiedad_t regBuscar,regArchivo;

    operacion = elegirOperacion();
    if (operacion == 'v'){
        strcpy (regArchivo.operacion, "Venta");
    } else if (operacion == 'a') {
        strcpy (regArchivo.operacion, "Alquiler");
    } else {
        strcpy (regArchivo.operacion, "Alquiler temporal");
    }
    fseek(propiedades,0,SEEK_SET);
    printf ("Filtro por Operaci%cn\n",162);
    while (fread(&regBuscar, sizeof(propiedad_t), 1, propiedades) == 1) {
        if (strcmp(regBuscar.operacion, regArchivo.operacion) == 0) {
            imprimirPropiedad(regBuscar);
        }
    }

    propiedad = elegirPropiedad();
    if (propiedad == 'c'){
        strcpy (regArchivo.tipo_propiedad, "Casa");
    } else if (propiedad == 'd') {
        strcpy (regArchivo.tipo_propiedad, "Depto.");
    } else {
        strcpy (regArchivo.tipo_propiedad, "PH");
    }
    fseek(propiedades,0,SEEK_SET);
    printf ("Filtro por Operaci%cn y por Propiedad\n",162);
    while (fread(&regBuscar, sizeof(propiedad_t), 1, propiedades) == 1) {
        if (strcmp(regBuscar.operacion, regArchivo.operacion) == 0 && strcmp(regBuscar.tipo_propiedad, regArchivo.tipo_propiedad) == 0) {
            imprimirPropiedad(regBuscar);
        }
    }
}
void buscarPropiedad(FILE* propiedades){
    char subopcion;
    printf ("---------------B%csqueda---------------\n", 163);
    printf ("Seleccione m%ctodo de b%csqueda:\n",130,163);
    printf ("[a]. B%csqueda por ID.\n",163);
    printf ("[b]. B%csqueda por Operaci%cn.\n",163,162);
    do{
        scanf (" %c",&subopcion);
        fflush(stdin);
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
}

//(PUNTO 8) Modificar datos
/*Permite modificar ciudad/barrio, precio o fecha de salida.
Con la modificacion de la fecha de salida se modifica la baja logica
Se validan las entradas del usuario y se pide una confirmación antes de modificar el registro.*/

//VER INGRESO DE FECHA DE SALIDA CON BAJA FISICA
void modificarPropiedad(FILE* propiedades){
    char num[20], letra[30], opcion, fecha[9];
    propiedad_t prop;
    printf ("------------Modificar------------\n");
    int id = ingresoID(num);
    fseek (propiedades, (id-1)*sizeof (propiedad_t), SEEK_SET);
    fread (&prop, sizeof(propiedad_t), 1, propiedades);
    printf ("Usted va a modificar la siguiente propiedad:\n");
    imprimirPropiedad(prop);
    printf("Ingrese que modificacion desea hacer:\n[a]. Ciudad/barrio.\n[b]. Precio.\n[c]. Fecha de salida.\n");
    scanf(" %c", &opcion);
    fflush(stdin);
    opcion = tolower (opcion);
    switch (opcion){
    case 'a':
        printf ("Ingrese la nueva ciudad/barrio de la propiedad: ");
        gets(letra);
        while (!validarTexto(letra)){
            printf("Opci%cn inv%clida. Por favor, ingrese una ciudad/barrio v%clida: ", 162,160, 160);
            gets(letra);
        }
        validarMayus(letra);
        strcpy(prop.ciudad_barrio, letra);
        fseek (propiedades, (id-1)*sizeof(propiedad_t), SEEK_SET);
        fwrite(&prop, sizeof(propiedad_t), 1, propiedades);
        printf("Modificaci%cn exitosa.\n",162);
        break;
    case 'b':
        printf ("Ingrese el precio de la propiedad: ");
        scanf (" %19s", num);
        while (!validarFloat(num)){
            printf("Opci%cn inv%clida. Por favor, ingrese un precio v%clido(agregando '.'): ", 162,160, 160);
            scanf(" %19s", num);
        }
        float precio_nuevo = atof(num);
        prop.precio = precio_nuevo;
        fseek (propiedades, (id-1)*sizeof(propiedad_t), SEEK_SET);
        fwrite(&prop, sizeof(propiedad_t), 1, propiedades);
        printf("Modificaci%cn exitosa.\n",162);
        break;
    case 'c':
        printf("Ingrese la fecha de salida(formato: DDMMYYYY): ");
        scanf("%8s", fecha);
        fflush(stdin);
        while (!validarFecha(fecha) && !compararFecha(fecha)) {
            printf("Opción inválida. Por favor, ingrese una fecha con formato DDMMYYYY: ");
            scanf(" %8s", fecha);
            fflush(stdin);
        }
        strcpy(prop.fecha_salida, fecha);
        fseek (propiedades, (id-1)*sizeof(propiedad_t), SEEK_SET);
        fwrite(&prop, sizeof(propiedad_t), 1, propiedades);
        printf("Modificaci%cn exitosa.\n",162);
        break;
    default:
        printf("Opci%cn inv%clida. Int%cntelo de nuevo.\n", 162, 160, 130);
        break;
    }
}

int main(){
    printf("%cBienvenido a Inmobiliaria Bub%c!\n", 173, 163);
    FILE* propiedades = crearDat();
    fflush(stdin);
    FILE* bajasXyz = NULL;
    while(1){
        mostrarMenu();
        char input = getchar();
        input = tolower(input);
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
                //bajaLogica(propiedades);
                break;
            case 'f':
                //bajasXyz = bajaFisica(propiedades);
                break;
            case 'g':
                //listarXyz(bajasXyz);
                break;
            case 'h':
            //cerrar el archivo y salir del programa
                fclose (propiedades);
                printf("Gracias por confiar en Inmobiliaria Bub%c. Saliendo del programa...\n",163);
                exit(0);
            default:
                printf("Opci%cn inv%clida. Int%cntelo de nuevo.\n", 162, 160, 130);
        }
    }
    return 0;
}
