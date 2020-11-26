/*
 * utn.h
 *
 *  Created on: 2020/10/12
 *      Author: PC
 */

#ifndef UTN_H_
#define UTN_H_

float utn_getFloat(char *mensaje, char *mensajeError, float *pResultado,int reintentos,float min, float max);
int utn_getNumero(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int minimo,int maximo);
int utn_getNombre(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite);
int utn_getString(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite);
int utn_getCuit(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limit);
int esUnNombreValido(char* cadena,int limite);
int ordenar(int array[], int len);
int esNumerica(char* cadena, int limite);
int isValidCuit(char* cadena);
#endif /* UTN_H_ */
