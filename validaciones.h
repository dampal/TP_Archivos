/*Biblioteca personal que permite verificar los datos ingresados por usuario,
teniendo un menor margen de error.*/

#include <time.h>
#include <string.h>
#include <ctype.h>

#ifndef VALIDACIONES_H
#define VALIDACIONES_H

int validarInt(char id[]);

int validarFloat(char flotante[])

int validarFecha(char fecha[]);

int validarTexto (char texto[]);

int validarMayus (char formato[]);


#endif