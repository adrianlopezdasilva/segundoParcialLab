/*
 * ventas.h
 *
 *  Created on: 2020/11/20
 *      Author: PC
 */

#ifndef VENTAS_H_
#define VENTAS_H_
#define SIZEVENTAS 30;

typedef struct
{
	int idVentas;
	int idCliente;
	char nombreArchivo[30];
	int zona;
}Ventas;

#endif /* VENTAS_H_ */
