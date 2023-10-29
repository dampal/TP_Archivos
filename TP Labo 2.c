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

//FALTA LISTAR POR RANGO DE TIEMPO!!!!!!!!!!!!!!!!!!! (118-139)

void imprimirPropiedad(propiedad_t prop){
    printf("%5d %-11s%-30s%-22s%-2d%-2d%-5.2f%-5.2f%-8.2f%-6s%-12s%-18s%-11s%-2d\n",
           prop.id, prop.fecha_ingreso, prop.zona, prop.ciudad_barrio, prop.dormitorios, prop.banos,
           prop.superficie_total, prop.superficie_cubierta, prop.precio, prop.moneda, prop.tipo_propiedad,
           prop.operacion, prop.fecha_salida, prop.flag_activo);
}
void listarDat(FILE* propiedades){
    char opcion;
    propiedad_t prop;
    fseek(propiedades, 0, SEEK_END);
    int total = ftell(propiedades) / sizeof(propiedad_t);
    printf ("-----------------Listado-----------------\n");
    printf ("[a]. Listar todas las propiedades.\n");
    printf ("[b]. Listar solo las propiedades activas.\n");
    printf ("[c]. Listar un tipo propiedad.\n");
    printf ("[d]. Listar en un rango de tiempo.\n");
    scanf (" %c", &opcion);
    fflush (stdin);
    switch (opcion){
        case 'a': //todas las propiedades
            printf("ID\tIngreso\t\tZona\t\tCiudad/Barrio\tDorm.\tBa%cos Sup.Total Sup.Cubierta Precio Moneda Operaci%cn  Salida Activo\n", 164,162);
            for (int i = 1; i < total; i++){
                fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
                fread(&prop, sizeof(propiedad_t), 1, propiedades);
                imprimirPropiedad(prop);
            }
            break;
        case 'b': //solo las activas
            for (int i = 1; i <= total; i++){
                fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
                fread(&prop, sizeof(propiedad_t), 1, propiedades);
                if (prop.flag_activo == 1){
                    imprimirPropiedad(prop);
                }
            }
            break;
        case 'c': //un tipo de propiedad
            printf("Tipo de propiedad:\n[C]. Casa\n[D]. Departamento\n[P]. PH\n");
            printf ("Seleccione el tipo de propiedad: ");
            char op = getchar ();
            op = tolower (op);
            while (op != 'c' && op !='d' && op !='p'){
                printf("Opci%cn inv%clida. Por favor, ingrese una opci%cn v%clida (C/D/P): ", 162,160,162,160);
                scanf(" %c", &op);
                op = tolower (op);
            }
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
        /*case 'd': //un rango de tiempo
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
                imprimirPropiedad(prop);
                }
            }
            break;*/
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

//VER INGRESO DE FECHAS Y COMPARACION CON LA ACTUAL !!!!!!!!!!!!!!!!!!! (261-267)

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
void elegirMoneda(propiedad_t nuevo){
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
    if (opcion == 'a'){
        strcpy (nuevo.moneda, 'PESOS');
    } else {
        strcpy (nuevo.moneda, 'USD');
    }
}
void elegirPropiedad(propiedad_t nuevo) {
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
    if (opcion == 'c'){
        strcpy (nuevo.tipo_propiedad, 'Casa');
    } else if (opcion == 'd') {
        strcpy (nuevo.tipo_propiedad, 'Departamento');
    } else {
        strcpy (nuevo.tipo_propiedad, 'PH');
    }
}
void elegirOperacion(propiedad_t nuevo) {
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
        strcpy (nuevo.operacion, 'Venta');
    } else if (opcion == 'a') {
        strcpy (nuevo.operacion, 'Alquiler');
    } else {
        strcpy (nuevo.operacion, 'Alquiler temporal');
    }
}

void altaPropiedad(FILE* propiedades){
    char num[20], fecha[9], letra[30];
    propiedad_t nuevo;
    propiedad_t dato;
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
            propiedad_t vacio = {0,'0','0','0',0,0,0,0,0,'0','0','0','0',0};
            fseek(propiedades, 0, SEEK_END);
            for (int i = 1; i <= filasInt ; i++){
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
    scanf (" %29s", letra);
    fflush(stdin);
    while (!validarTexto(letra)){
        printf("Opci%cn inv%clida. Por favor, ingrese una zona v%clida: ", 162,160, 160);
        scanf(" %29s", letra);
        fflush(stdin);
    }
    validarMayus(letra);
    strcpy(nuevo.zona, letra);

    printf ("Ingrese la ciudad/barrio de la propiedad: ");
    scanf (" %29s", letra);
    fflush(stdin);
    while (!validarTexto(letra)){
        printf("Opci%cn inv%clida. Por favor, ingrese una ciudad/barrio v%clida: ", 162,160, 160);
        scanf(" %29s", letra);
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
    elegirMoneda(nuevo);
    elegirPropiedad(nuevo);
	elegirOperacion(nuevo);
	fflush(stdin);

    //Guardo el nuevo struct en el lugar que corresponda
    /*si todo esta ok, la propiedad queda activa*/
    nuevo.flag_activo = 1;
    fseek (propiedades, (id-1)*sizeof(propiedad_t), SEEK_SET);
    fwrite(&nuevo, sizeof(propiedad_t), 1, propiedades);
    printf("Propiedad agregada exitosamente.\n");
}

//busca una propiedad en el archivo segun ID.
//cambia el campo "fecha de salida" por la fecha actual.
//cambia el campo "activo" a cero.
//NO ESTOY SEGURO DE QUE ESTO ES LO QUE QUIERA LA PROFE
/*void bajaLogica(FILE* propiedades){
    //franco???
}

buscarPorID(propiedades){
    //franco
}

buscarPorOp(propiedades){
    //franco
}*/

//(PUNTO 7) Busqueda de datos
//muestra un submenu de opciones.
//busca propiedades por ID o por operacion y luego tipo de propiedad
//segun la entrada del usuario
//emite los datos encontrados, o un mensaje si no se encuentra nada.
/*void buscarPropiedad(FILE* propiedades){
    //aca mostramos menu y pedimos opciones
    buscarPorID(propiedades);
    //o
    buscarPorOp(propiedades);
}*/

//(PUNTO 8) Modificar datos
/*Permite modificar ciudad/barrio, precio o fecha de salida.
Con la modificacion de la fecha de salida se modifica la baja logica
Se validan las entradas del usuario y se pide una confirmación antes de modificar el registro.*/

//VER INGRESO DE FECHA DE SALIDA, VALIDACION DE FECHA Y ACTUAL!!!!!!!!!!!!!!!!!!!

/*void modificarPropiedad(FILE* propiedades){
    char num[20] letra[30];
    propiedad_t prop;
    printf ("------------Modificar------------\n");
    int id = ingresoID(num);
    fseek (propiedades, (id-1)*sizeof (propiedad_t), SEEK_SET);
    fread (&prop, sizeof(propiedad_t), 1, propiedades);
    printf("Ingrese que modificacion desea hacer:\n[a]. Ciudad/barrio.\n[b]. Precio.\n[c]. Fecha de salida.\n");
    char opcion = getchar();
    opcion = tolower (opcion);
    printf ("Usted va a modificar la siguiente propiedad:");
    imprimirPropiedad(prop);
    switch (opcion){
    case 'a':
        printf ("Ingrese la ciudad/barrio de la propiedad: ");
        scanf (" %29s", letra);
        while (!validarTexto(letra)){
            printf("Opci%cn inv%clida. Por favor, ingrese una ciudad/barrio v%clida: ", 162,160, 160);
            scanf(" %29s", letra);
        }
        validarMayus(letra);
        strcpy(prop.ciudad_barrio, letra);
        break;
    case 'b':
        printf ("Ingrese el precio de la propiedad: ");
        scanf (" %19s", num);
        while (!validarFloat(num)){
            printf("Opci%cn inv%clida. Por favor, ingrese un precio v%clido: ", 162,160, 160);
            scanf(" %19s", num);
        }
        float precio_nuevo = atof(num);
        prop.precio = precio_nuevo;
        break;
    case 'c':
        //VER FECHAS, INGRESO Y VALIDAR CON ACTUAL !!!!!!!!!!!!!!!
        break;
    default:
        printf("Opci%cn inv%clida. Int%cntelo de nuevo.\n", 162, 160, 130);
        break;
    }
    
}*/

//crea un archivo "propiedades_bajas_<fecha>.xyz" con la fecha actual.
//en este graba todas las propiedades inactivas de "propiedades"
//simultaneamente elimina esos registros de "propiedades"
//devuelve un puntero activo al archivo de bajas.
/*FILE* bajaFisica(FILE* propiedades){
    
}*/

//imprime los registros de bajasXyz con el formato correspondiente.
/*void listarXyz(FILE* bajasXyz){
    
}*/

int main(){
    printf("%cBienvenido a Inmobiliaria Bub%c!\n", 173, 163);
    FILE* propiedades = crearDat();
    fflush(stdin);
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
                //buscarPropiedad(propiedades);
                break;
            case 'd':
                //modificarPropiedad(propiedades);
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