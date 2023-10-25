/*Biblioteca personal que permite verificar los datos ingresados por usuario,
teniendo un menor margen de error.*/

#include <time.h>
#include <string.h>
#include <ctype.h>

#ifndef VALIDACIONES_H
#define VALIDACIONES_H

int validarInt(char id[]);

int validarFloat(char flotante[])

//Recibe un string que contiene una fecha en formato DDMMYYYY
//chequea si esa fecha es una fecha válida, teniendo en cuenta cantidad de dias por mes y años bisiestos.
//devuelve 1 si es válida, 0 si no lo es.
int validarFecha(char fecha[]);

int validarTexto (char texto[]);

int validarMayus (char formato[]);


#endif