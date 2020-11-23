/*
 * informes.c
 *
 *  Created on: 2020/11/22
 *      Author: PC
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "clientes.h"
#include "parser.h"
#include "Controller.h"
#include "ventas.h"
#include "utn.h"
#include "informes.h"

int informe_informeCobros(char* path,LinkedList* this1, LinkedList* this2)
{
	int retorno = -1;
	int len;
	FILE* pFile;
	Cliente* bufferCliente;
	int auxId;
	char auxNombre[SIZECLIENTE];
	char auxApellido[SIZECLIENTE];
	int auxCuit;
	int cantidadCobrados;

	if(this1 != NULL && this2 != NULL)
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
		len = ll_len(this1);
		printf("\n\n ID   NOMBRE    APELLIDO   CUIT   TOTAL COBRADO");
		for(int i = 0; i < len; i++)
		{
			bufferCliente = (Cliente*) ll_get(this1, i);

			if(cliente_getId(bufferCliente, &auxId)== 0 &&
			   cliente_getNombre(bufferCliente, auxNombre) == 0 &&
			   cliente_getApellido(bufferCliente, auxApellido) == 0 &&
			   cliente_getCuit(bufferCliente, &auxCuit) == 0 )
			{
				cantidadCobrados = informe_contadorVentasCobradas(this2, auxId);
				printf("\n%d- %s  -   %s  -    %d  - %d ", auxId, auxNombre, auxApellido, auxCuit, cantidadCobrados);
				fprintf(pFile,"%d, %s, %s, %d, %d\n",auxId, auxNombre, auxApellido,auxCuit, cantidadCobrados);
			}
		}
		retorno = 0;
		fclose(pFile);
		}
	}
	return retorno;
}

int informe_contadorVentasCobradas(LinkedList* this,int idCliente)
{
	int contadorCobrados = 0;
	int len;
	Venta* bufferVenta;
	int auxEstado;
	int auxIdCliente;

	if(this != NULL && idCliente > 0)
	{
		len = ll_len(this);
		for(int i = 0; i < len; i++)
		{
			bufferVenta = (Venta*) ll_get(this, i);
			if(venta_getIdCliente(bufferVenta, &auxIdCliente)== 0 &&
			   auxIdCliente == idCliente &&
			   venta_getEstadoCobranza(bufferVenta, &auxEstado) == 0 &&
			   auxEstado == COBRADA)
			{
				contadorCobrados++;
			}
		}
	}
	return contadorCobrados;
}

int informe_informeDeudas(char* path,LinkedList* this1, LinkedList* this2)
{
	int retorno = -1;
	int len;
	FILE* pFile;
	Cliente* bufferCliente;
	int auxId;
	char auxNombre[SIZECLIENTE];
	char auxApellido[SIZECLIENTE];
	int auxCuit;
	int cantidadDeudas;

	if(this1 != NULL && this2 != NULL)
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
		len = ll_len(this1);
		printf("\n\n ID   NOMBRE    APELLIDO   CUIT   TOTAL ADEUDADO");
		for(int i = 0; i < len; i++)
		{
			bufferCliente = (Cliente*) ll_get(this1, i);

			if(cliente_getId(bufferCliente, &auxId)== 0 &&
			   cliente_getNombre(bufferCliente, auxNombre) == 0 &&
			   cliente_getApellido(bufferCliente, auxApellido) == 0 &&
			   cliente_getCuit(bufferCliente, &auxCuit) == 0 )
			{
				cantidadDeudas = informe_contadorVentasAdeudadas(this2, auxId);
				printf("\n%d- %s  -   %s  -    %d  - %d ", auxId, auxNombre, auxApellido, auxCuit, cantidadDeudas);
				fprintf(pFile,"%d, %s, %s, %d, %d\n",auxId, auxNombre, auxApellido,auxCuit, cantidadDeudas);
			}
		}
		retorno = 0;
		fclose(pFile);
		}
	}
	return retorno;
}

int informe_contadorVentasAdeudadas(LinkedList* this,int idCliente)
{
	int contadorDeudas = 0;
	int len;
	Venta* bufferVenta;
	int auxEstado;
	int auxIdCliente;

	if(this != NULL && idCliente > 0)
	{
		len = ll_len(this);
		for(int i = 0; i < len; i++)
		{
			bufferVenta = (Venta*) ll_get(this, i);
			if(venta_getIdCliente(bufferVenta, &auxIdCliente)== 0 &&
			   auxIdCliente == idCliente &&
			   venta_getEstadoCobranza(bufferVenta, &auxEstado) == 0 &&
			   auxEstado == SINCOBRAR)
			{
				contadorDeudas++;
			}
		}
	}
	return contadorDeudas;
}
