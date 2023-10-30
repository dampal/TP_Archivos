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
    char fecha_salida[30];
    char zona[30];
    char ciudad_barrio[30];
    int dormitorios;
    int banos;
    float superficie_total;
    float superficie_cubierta;
    float precio;
    char moneda[6];
    char tipo_propiedad[30];
    char operacion[30];
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
            printf ("Opci%cn inv%alida.\n", 162,160);
            exit (1);
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

//(PUNTO 3) Validacion de los datos ingresados
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
        if (id <= totalReg){ //si es mas chico existe, busco donde esta
            fseek (propiedades, (id-1)*sizeof (propiedad_t), SEEK_SET);
            fread (&dato, sizeof(propiedad_t), 1, propiedades);
            if (dato.id !=0){
                printf("La posici%cn %d ya est%c ocupada.\n", 162, id, 160);
            } else { //q hago si el activo esta en 0?????????
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

    printf ("Ingrese la fecha actual: ");
    scanf ("%8s", fecha);
    while (!validarFecha (fecha)){
        printf("Opci%cn inv%clida. Por favor, ingrese una fecha con formato DDMMYYYY: ", 162,160);
        scanf(" %8s", fecha);
    }
    //VERIFICAR SI ES LA REAL CON LA FECHA DE LA COMPU
    nuevo.fecha_ingreso = fecha;

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
    nuevo.dormitorios = bano;

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
    nuevo.superficie_total = s_cub;

    printf ("Ingrese el valor de la propiedad: ");
    scanf (" %19s", num);
    while (!validarFloat (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese un valor v%clida(agregando '.'): ", 162,160, 160);
        scanf(" %19s", num);
    }
    float precio = atof(num);
    nuevo.superficie_total = precio;
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
    int nReg,aux;
    char opcion,id[6], cadAux[6] = "0";

    propiedad_t busqueda;

    aux = ingresoID(id);

    fseek(propiedades,0,SEEK_SET);
    nReg=ftell(propiedades)/sizeof(propiedad_t);

    if (id <= nReg){                                                            //si el id es valido y tiene un valor numerico, entonces ese registro no esta vacío
        fseek(propiedades,(aux-1)*sizeof(propiedad_t),SEEK_SET);

        fread(&busqueda,sizeof(propiedad_t),1,propiedades);

        if (strcmp(busqueda.fecha_salida, cadAux) == 0){
            printf ("Est%c seguro que quiere dar de baja a:\n",160);
            imprimirRegistro(busqueda);
            printf ("S/N\n");
            do{
                scanf (" %c",&opcion);
                opcion = tolower(opcion);

                if (opcion != 's' && opcion != 'n')
                    printf("La opci%cn es incorrecta, ingrese otra opci%cn.\n",162,162);

            } while (opcion != 's' && opcion != 'n');


            switch (opcion){
                case 's':
                    busqueda.flag_activo = 0;
                    fseek(propiedades, - sizeof(propiedad_t),SEEK_CUR);
                    fwrite(&busqueda,sizeof(propiedad_t),1,propiedades);

                    fseek(propiedades,0,SEEK_SET);

                    while (fread(&busqueda, sizeof(propiedad_t), 1, propiedades) == 1) {
                        if (busqueda.flag_activo == 1) {
                            imprimirRegistro(busqueda);
                        }
                    }

                    break;
                case 'n':
                    printf ("La baja ha sido cancelada con %cxito\n",130);
                    break;

            }


        } else {
            printf ("Error, el registro ya tiene una fecha de salida\n",131,161);}


    } else {
        printf ("Error, no existe el ID ingresado\n");}

}

buscarPorID(propiedades){

    int nReg,aux;
    char id[6];

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
            imprimirRegistro(busqueda);
        } else {
            printf ("Error, el registro est%c vac%co\n",131,161);}



    } else {
    printf ("Error, no existe el ID ingresado\n");}

}

void buscarPorOp(FILE * propiedades){

    int flag1 = 0, flag2 = 0;
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
    fflush(stdin);


    printf ("Filtro por Operaci%cn\n",162);
    imprimirEncabezado();

    while (fread(&regBuscar, sizeof(propiedad_t), 1, propiedades) == 1) {
        if (strcmp(regBuscar.operacion, regArchivo.operacion) == 0) {
            imprimirPropiedad(regBuscar);
            flag1 = 1;
        }
    }


    if (flag1 == 1){

        propiedad = elegirPropiedad();

        if (propiedad == 'c'){
            strcpy (regArchivo.tipo_propiedad, "Casa");
        } else if (propiedad == 'd') {
            strcpy (regArchivo.tipo_propiedad, "Depto.");
        } else {
            strcpy (regArchivo.tipo_propiedad, "PH");
        }

        fseek(propiedades,0,SEEK_SET);
        fflush(stdin);

        printf ("Filtro por Operaci%cn y por Propiedad\n",162);
        imprimirEncabezado();

        while (fread(&regBuscar, sizeof(propiedad_t), 1, propiedades) == 1) {
            if (strcmp(regBuscar.operacion, regArchivo.operacion) == 0 && strcmp(regBuscar.tipo_propiedad, regArchivo.tipo_propiedad) == 0) {
                imprimirPropiedad(regBuscar);
                flag2 = 1;
            }
        }


        if (flag2 == 0){
            printf ("No se hallaron resultados en b%csqueda por Propiedad\n",163);
        }


    } else { printf ("No se encontr%c la Operaci%cn a buscar\n",162,162); }

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

    int nReg,aux;
    char id[6];
    propiedad_t busqueda;
    propiedad_t vacio = {0,'0','0','0',0,0,0,0,0,'0','0','0','0',0};

    FILE * pArchivoBajas;
    pArchivoBajas = fopen("propiedades_bajas_<fecha>.xyz","a+");

    aux = ingresoID(id);

    if(pArchivoBajas != NULL){

            fseek(pArchivoBajas,0,SEEK_SET);

            fseek(propiedades,0,SEEK_SET);
            nReg=ftell(propiedades)/sizeof(propiedad_t);

            if (id <= nReg){
                fseek(propiedades,(aux-1)*sizeof(propiedad_t),SEEK_SET);

                fread(&busqueda,sizeof(propiedad_t),1,propiedades);

                fprintf(pArchivoBajas, "%5d%9s%30s%30s%2d%2d%10.2f%10.2f%10.2f%5s%13s%19s\n",\
                    busqueda.id, busqueda.fecha_ingreso, busqueda.zona, busqueda.ciudad_barrio, busqueda.dormitorios,\
                    busqueda.banos, busqueda.superficie_total, busqueda.superficie_cubierta, busqueda.precio, busqueda.moneda,\
                    busqueda.tipo_propiedad, busqueda.operacion, busqueda.fecha_salida, busqueda.flag_activo);


                fseek(propiedades, - sizeof(propiedad_t),SEEK_CUR);
                fwrite(&vacio,sizeof(propiedad_t),1,propiedades);

                return pArchivoBajas;

            } else {
                printf ("Error, no existe el ID ingresado\n");}



    fclose(pArchivo);

    } else printf("Error en la apertura del archivo!");




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
