/*Biblioteca personal que permite verificar los datos ingresados por usuario,
teniendo un menor margen de error.*/
#ifndef VALIDACIONES_H
#define VALIDACIONES_H

int validarID(int id);
int validarNumero (); //CHEQUEALO
int validarFecha(char fecha[]);
int validarTexto (char texto[]);
int validarPropiedad (char propiedad[]);
int validarOperacion (char operacion[]);
int validarMoneda (char moneda[]);
int validarPrimerMayus (char formato[]);

#endif