//Desarollo de las funciones propias para la libreria 'validaciones.h'

/*Si con el número de id ingresado existe un registro de datos cargado,
se debe emitir un mensaje de error y pedir un nuevo número de id.
El acceso de comprobación debe ser directo.*/
int validarInt (char num[]){
    for(int i=0; i<strlen(num); i++){
        if(!isdigit(num[i])){
            return 0;
        }
    }
    return 1;    
}

int validarFloat(char flotante[]){
    int cantPuntos = 0;
    for(int i=0; i<strlen(flotante); i++){
        if(flotante[i] == '.'){
                cantPuntos++;
            }
        if((!isdigit(flotante[i]) && flotante[i] != '.') || cantPuntos>1){
            return 0;
        }
    }
    return 1;   
}

//Recibe un string que contiene una fecha en formato DDMMYYYY
//chequea si esa fecha es una fecha válida, teniendo en cuenta cantidad de dias por mes y años bisiestos.
//devuelve 1 si es válida, 0 si no lo es.
int validarFecha(char fecha[]){
    if(atoi(fecha)<10000000 && atoi(fecha)>9999999){
        int dd,mm,yy;
        dd = (fecha[0]-48)*10 + (fecha[1]-48);
        mm = (fecha[2]-48)*10 + (fecha[3]-48);
        yy = atoi(fecha+4);
        //chequea el año
        if(yy>=1900 && yy<=9999){
            //chequea meses
            if(mm>=1 && mm<=12){
                //chequea dias
                if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
                    return 1;
                else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
                    return 1;
                else if((dd>=1 && dd<=28) && (mm==2))
                    return 1;
                else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0)))  //chequea bisiestos
                    return 1;            
            }
            
        }
    }
    return 0;
}

//Chequea si el texto ingresado contiene caracteres que no sean texto, puntuación o espacios.
//En caso de encontrar caracteres invalidos, devuelve cero.
//Si es valido, devuelve 1.
int validarTexto (char texto[]){
    for(int j = 0; j < strlen(texto); j++){
        if(!isalpha(texto[j]) && !ispunct(texto[j]) && !isspace(texto[j])){
            return 0;
        }
    }
    return 1;
}

// Chequea que cada palabra del texto "formato" empiece con mayúscula.
// Cambia la primer letra de cada palabra a mayus en caso de que no lo sea. 
void validarMayus (char formato[]){
    
    if(islower(formato[0])){
        formato[0] = toupper(formato[0]);
    }
    
    for(int i = 1; i < strlen(formato); i++){
        if(islower(formato[i]) && !isalpha(formato[i-1])){
            formato[i] = toupper(formato[i]);
        }
    }
}

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
