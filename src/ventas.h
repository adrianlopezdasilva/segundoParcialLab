/*
 * ventas.h
 *
 *  Created on: 2020/11/20
 *      Author: PC
 */

#ifndef VENTAS_H_
#define VENTAS_H_
#define SIZEVENTAS 30
#define SINCOBRAR 0
#define COBRADA 1

typedef struct
{
	int idVenta;
	int idCliente;
	int cantidad;
	char nombreArchivo[30];
	int zona;
	int estadoCobranza;
}Venta;

Venta* venta_new(void);
Venta* venta_newParametros(char* idVentaStr,char* idClienteStr, char* nombreArchivoStr,char* cantidadStr, char* zonaStr, char* estadoCobranzaStr);
void venta_delete(Venta* this);
int venta_setIdVenta(Venta* this,int idVenta);
int venta_getIdVenta(Venta* this,int* idVenta);
int venta_setIdCliente(Venta* this,int idCliente);
int venta_getIdCliente(Venta* this,int* idCliente);
int venta_setNombreArchivo(Venta* this,char* nombreArchivo);
int venta_getNombreArchivo(Venta* this,char* nombreArchivo);
int venta_setCantidadAfiches(Venta* this,int cantidad);
int venta_getCantidadAfiches(Venta* this,int* cantidad);
int venta_setZona(Venta* this,int zona);
int venta_getZona(Venta* this,int* zona);
int venta_setEstadoCobranza(Venta* this,int estadoCobranza);
int venta_getEstadoCobranza(Venta* this,int* estadoCobranza);
#endif /* VENTAS_H_ */
