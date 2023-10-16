//Desarollo de las funciones propias para la libreria 'validaciones.h'

/*Si con el número de id ingresado existe un registro de datos cargado,
se debe emitir un mensaje de error y pedir un nuevo número de id.
El acceso de comprobación debe ser directo.*/
int validarID (int id){
    printf ("Ingresar el ID de la propiedad: ");
    scanf ("%d", &id);
    id = validarNumero(&id);
    if (fread (&id, sizeof(int), 1, propiedades) == id){
        return id;
    }else {
        printf("Intentelo de nuevo.\n");
        //ACA TENDRIA QUE VOLVER A RETOMAR ESTA FUNCION
    }
}

/*Si el número de id ingresado es negativo, se debe emitir un error y volver a pedir otro valor.
La misma validación debe realizarse para los valores flotantes y enteros.*/
int validarNumero (int *numero){
    while (*numero <= 0) {
        printf ("Por favor, ingrsese un n%dmero positivo: ", 163);
        scanf ("%d", numero);
        }
    return *numero;
}

int validarFecha(char fecha[]);
int validarTexto (char texto[]);
int validarPropiedad (char propiedad[]);
int validarOperacion (char operacion[]);
int validarMoneda (char moneda[]);
int validarPrimerMayus (char formato[]);

/*Tener en cuenta que en el caso de altas el campo activo siempre es 1
(o carácter que identifica el estar activo), en el alta, este campo no se ingresa por teclado. */

/*Debe controlar el error si el usuario ingresa una cadena o carácter cuando debe ser un número, o viceversa.*/

/*En el caso de los campos: tipo de propiedad, operación y moneda, observar que hay más de un tipo,
en éste caso se debe dar al usuario sólo las opciones para que elija y
evitar que ingrese el texto completo como forma de evitar errores de tipeo en el texto que se va a registrar.*/

/*Las cadenas deben respetar el formato, es decir, primera letra mayúscula y el resto en mínúscula.*/

/*En cada nuevo registro, antes de grabar en el archivo y una vez realizadas las primeras validaciones
y comprobaciones de errores, se debe tener en cuenta que:
-Los datos de fecha deben ser correctos, es decir que hay que considerar los rangos de días
(por ejemplo controlar los días número 31 respecto del ingreso del mes).
Controlar también los meses y los años. 
-La fecha de salida o egreso de la propiedad no puede ser mayor que la actual,
se debe controlar eso y si es necesario utilizar funciones de tiempo de C.*/
