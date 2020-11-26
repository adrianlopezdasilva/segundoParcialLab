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

/** \brief Realize un informe de cuantas ventas cobradas tiene cada cliente y guarda la informacion en el archivo cobrados.txt(modo texto)
 *
 * \param path char* direccion dodse encuentra el archivo
 * \param this1 LinkedList* es donde esta contenida la direccion de memoria de la lista de los clientes
 * \param this2 LinkedList* es donde esta contenida la direccion de memoria de la lista de las ventas
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int informe_informeCobros(char* path,LinkedList* this1, LinkedList* this2)
{
	int retorno = -1;
	int len;
	FILE* pFile;
	Cliente* bufferCliente;
	int auxId;
	char auxNombre[SIZECLIENTE];
	char auxApellido[SIZECLIENTE];
	char auxCuit[SIZECUIT];
	int cantidadCobrados;

	if(this1 != NULL && this2 != NULL)
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
			len = ll_len(this1);
			printf("\n\n ID   NOMBRE  \t  APELLIDO       CUIT   TOTAL COBRADO");
			for(int i = 0; i < len; i++)
			{
				bufferCliente = (Cliente*) ll_get(this1, i);

				if(cliente_getId(bufferCliente, &auxId)== 0 &&
				   cliente_getNombre(bufferCliente, auxNombre) == 0 &&
				   cliente_getApellido(bufferCliente, auxApellido) == 0 &&
				   cliente_getCuit(bufferCliente, auxCuit) == 0 )
				{
					cantidadCobrados = informe_contadorVentasCobradas(this2, auxId);
					printf("\n%d- %s  - %s  -    %s  - %d ", auxId, auxNombre, auxApellido, auxCuit, cantidadCobrados);
					fprintf(pFile,"%d,%s,%s,%s,%d\n",auxId, auxNombre, auxApellido,auxCuit, cantidadCobrados);
				}
			}
		retorno = 0;
		fclose(pFile);
		}
	}
	return retorno;
}

/** \brief Acumula la cantidad de ventas cobradas que tiene cada cliente y las devuelve por valor
 *
 * \param this1 LinkedList* es donde esta contenida la direccion de memoria de la lista de las ventas
 * \param idCliente int el id del cliente al cual se le van a asociar las ventas cobradas
 * \return int el contador de ventas cobradas de cada cliente
 *
 */
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
			if(bufferVenta != NULL &&
			   venta_getIdCliente(bufferVenta, &auxIdCliente)== 0 &&
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

/** \brief Realize un informe de cuantas ventas adeudadas tiene cada cliente y guarda la informacion en el archivo a_cobrar.txt(modo texto)
 *
 * \param path char* direccion dodse encuentra el archivo
 * \param this1 LinkedList* es donde esta contenida la direccion de memoria de la lista de los clientes
 * \param this2 LinkedList* es donde esta contenida la direccion de memoria de la lista de las ventas
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int informe_informeDeudas(char* path,LinkedList* this1, LinkedList* this2)
{
	int retorno = -1;
	int len;
	FILE* pFile;
	Cliente* bufferCliente;
	int auxId;
	char auxNombre[SIZECLIENTE];
	char auxApellido[SIZECLIENTE];
	char auxCuit[SIZECUIT];
	int cantidadDeudas;

	if(this1 != NULL && this2 != NULL)
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
		len = ll_len(this1);
		printf("\n\n ID   NOMBRE  \t    APELLIDO \t       CUIT   TOTAL ADEUDADO");
		for(int i = 0; i < len; i++)
		{
			bufferCliente = (Cliente*) ll_get(this1, i);

			if(cliente_getId(bufferCliente, &auxId)== 0 &&
			   cliente_getNombre(bufferCliente, auxNombre) == 0 &&
			   cliente_getApellido(bufferCliente, auxApellido) == 0 &&
			   cliente_getCuit(bufferCliente, auxCuit) == 0 )
			{
				cantidadDeudas = informe_contadorVentasAdeudadas(this2, auxId);
				printf("\n%d- %s  -   %s  -    %s  - %d ", auxId, auxNombre, auxApellido, auxCuit, cantidadDeudas);
				fprintf(pFile,"%d,%s,%s,%s,%d\n",auxId, auxNombre, auxApellido,auxCuit, cantidadDeudas);
			}
		}
		retorno = 0;
		fclose(pFile);
		}
	}
	return retorno;
}

/** \brief Acumula la cantidad de ventas adeudadas que tiene cada cliente y las devuelve por valor
 *
 * \param this1 LinkedList* es donde esta contenida la direccion de memoria de la lista de las ventas
 * \param idCliente int el id del cliente al cual se le van a asociar las ventas adeudads
 * \return int el contador de ventas adeudadas de cada cliente
 *
 */
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

/** \brief Informa cual es la venta realizada que contenga la mayor cantidad de afiches vendidos
 *
 * \param this1 LinkedList* es donde esta contenida la direccion de memoria de la lista de los clientes
 * \param this2 LinkedList* es donde esta contenida la direccion de memoria de la lista de las ventas
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int informe_ventaConMayorAfiches(LinkedList* this1, LinkedList* this2)
{
	int retorno = -1;
	int len;
	Venta* bufferVenta;
	Cliente* bufferCliente;
	int auxEstado;
	int maximoVentas;
	int auxCantidadVendidos;
	int auxIdVenta;
	int auxIdCliente;
	char auxCuit[SIZECUIT];

	if(this1 != NULL && this2 != NULL)
	{
		len = ll_len(this1);
		for(int i = 0; i< len; i++)
		{
			bufferVenta = (Venta*) ll_get(this2, i);
			if(venta_getEstadoCobranza(bufferVenta, &auxEstado) == 0 &&
			   auxEstado == COBRADA  &&
			   venta_getCantidadAfiches(bufferVenta, &auxCantidadVendidos) == 0 &&
			   (auxCantidadVendidos >  maximoVentas || i == 0 ))
			{
				maximoVentas = auxCantidadVendidos;
				if(venta_getIdVenta(bufferVenta, &auxIdVenta) == 0 &&
				   venta_getIdCliente(bufferVenta, &auxIdCliente) == 0)
				{
					bufferCliente =  cliente_devolverClientePorId(this1, auxIdCliente);
					if(bufferCliente != NULL &&
					   cliente_getCuit(bufferCliente, auxCuit) == 0)
					{
						continue;
					}
				}
			}
		}
		retorno = 0;
		printf("\nLa venta con mas afiches vendidos es de: %d afiches en el ID: %d y el cuit del cliente es:%s\n",
				maximoVentas, auxIdVenta, auxCuit);
	}
	return retorno;
}

int informe_clinteMayorOMenorAfiches(LinkedList* this1, LinkedList* this2,int criterio)
{
	int retorno = -1;
	LinkedList* auxList = NULL;
	Cliente* bufferCliente;
	int len;
	int acumulador = 0;
	int bufferId;
	int auxCantidad = 0;
	int idAMostrar;

	if(this1 != NULL && this2 != NULL && (criterio == 1 || criterio == 2))
	{
		len = ll_len(this1);
		auxList = ll_filter(this2,venta_buscarVentasCobradas);
		for(int i = 0; i < len; i++)
		{
			bufferCliente = (Cliente*) ll_get(this1,i);
			cliente_getId(bufferCliente, &bufferId);
			acumulador = ll_reduceIntArg(auxList, venta_ventasDeUnCliente, &bufferId);
			if( (acumulador > auxCantidad && criterio == 1) || (acumulador < auxCantidad && criterio == 2) || i == 0 )
			{
				auxCantidad = acumulador;
				idAMostrar = bufferId;
			}
		}
		retorno = 0;
		printf("\nEs el ID: %d con %d ventas\n", idAMostrar, auxCantidad);
	}

	return retorno;
}

int informe_clinteMayorOMenorAfiches2(LinkedList* this1,LinkedList* this2 )
{
	int retorno = -1;
	Cliente* bufferCliente;
	LinkedList* auxList = NULL;
	int auxId;
	int acumulador = 0;
	int bufferId;
	int minimo;
	int idAMostrar;


	if(this1 != NULL && this2 != NULL)
	{
		auxList = ll_filter(this2,venta_buscarVentasCobradas);
		for(int i = 0; i < ll_len(this1); i++)

		{
			bufferCliente = (Cliente*) ll_get(this1,i);
			cliente_getId(bufferCliente, &auxId);
			acumulador = ll_reduceIntArg(auxList, venta_ventasDeUnCliente, &bufferId);
			{
				if(i == 0 || acumulador < minimo)
				{
					minimo = acumulador;
					retorno = 0;
					idAMostrar = auxId;
				}
			}
		}
		printf("\nEs el ID: %d con %d ventas\n", idAMostrar, minimo);
	}
	return retorno;


}
/** \brief Menu de estadisticas
 *
 * \param this1 LinkedList* es donde esta contenida la direccion de memoria de la lista de los clientes
 * \param this2 LinkedList* es donde esta contenida la direccion de memoria de la lista de las ventas
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int informe_estadisticas(LinkedList* this1, LinkedList* this2)
{
	int opcionEstadisticas;
	int retorno = -1;
	if(this1 != NULL && this2 != NULL)
	{
		do
		{
			if(utn_getNumero("\n\nMenu de estadisticas"
				 "\n1. Cliente al que se le vendio mas afiches."
				 "\n2. Cliente al que se le vendio menos afiches."
				 "\n3. Venta con mas afiches vendidos"
				 "\n4. Salir\n","Error,opcion invalida\n",&opcionEstadisticas, 5, 1, 4)== 0)
			{
				switch(opcionEstadisticas)
				{
				case 1:
						if(informe_clinteMayorOMenorAfiches(this1, this2, opcionEstadisticas) == 0)
						{
							printf("\nInforme realizado extiosamente \n");
						}
						 break;
				case 2:
						if(informe_clinteMayorOMenorAfiches(this1, this2, opcionEstadisticas) == 0)
						{
							printf("\nInforme realizado extiosamente \n");
						}
						 break;
				case 3:
						if(informe_ventaConMayorAfiches(this1, this2) == 0)
						{
						  printf("\nInforme realizado extiosamente \n");
						}
						 break;
				}
			}
		}while(opcionEstadisticas != 4);
		retorno = 0;
	}
	return retorno;
}


