/*
 * controller.c
 *
 *  Created on: 2020/11/20
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

/** \brief Carga los datos de los clientes desde el archivo data.csv (modo texto).
 *
 * \param path char* direccion donde se encuentra el archivo
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int controller_clienteLoadFromText(char* path , LinkedList* this)
{
    int retorno = -1;

    FILE* pFile = fopen(path,"r");
    if(pFile !=NULL)
    {
    	parser_clienteFromText(pFile,this);
    	retorno = 0;
    }
    fclose(pFile);

    return retorno;
}
/** \brief Guarda los datos de los clientes en el archivo clientes.txt (modo texto).
 *
 * \param path char* direccion donde se encuentra el archivo
 * \param pArrayListEmployee LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */

int controller_clienteSaveAsText(char* path , LinkedList* this)
{
	int retorno = -1;
	Cliente* bufferCliente;
	FILE* pFile;
	int auxId;
	char auxNombre[SIZECLIENTE];
	char auxApellido[SIZECLIENTE];
	int auxCuit;

	if(path != NULL && this != NULL)
	{
		pFile = fopen(path,"w");
		{
			if(pFile != NULL)
			{
				for(int i = 0; i < ll_len(this); i++)
				{
					bufferCliente = (Cliente*)ll_get(this,i);
					if(cliente_getId(bufferCliente,&auxId )== 0  &&
					   cliente_getNombre(bufferCliente,auxNombre) == 0 &&
					   cliente_getApellido(bufferCliente,auxApellido) == 0 &&
					   cliente_getCuit(bufferCliente,&auxCuit) == 0 )
					{
						fprintf(pFile,"%d, %s, %s, %d\n",auxId, auxNombre, auxApellido,auxCuit);
					}

				}
				retorno = 0;
				fclose(pFile);
			}
		}
	}
	 return retorno;
}

/** \brief Guarda los datos de las ventas en el archivo ventas.txt (modo texto).
 *
 * \param path char* direccion donde se encuentra el archivo
 * \param pArrayListEmployee LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */

int controller_ventaSaveAsText(char* path , LinkedList* this)
{
	int retorno = -1;
	Venta* bufferVenta;
	FILE* pFile;
	int auxIdVenta;
	int auxIdCliente;
	char auxNombreArchivo[SIZEVENTAS];
	int auxCantidad;
	int auxZona;
	int auxEstado;

	if(path != NULL && this != NULL)
	{
		pFile = fopen(path,"w");
		{
			if(pFile != NULL)
			{
				for(int i = 0; i < ll_len(this); i++)
				{
					bufferVenta = (Venta*)ll_get(this,i);
					if(venta_getIdVenta(bufferVenta,&auxIdVenta )== 0  &&
					   venta_getIdCliente(bufferVenta,&auxIdCliente )== 0  &&
					   venta_getNombreArchivo(bufferVenta,auxNombreArchivo) == 0 &&
					   venta_getCantidadAfiches(bufferVenta,&auxCantidad) == 0 &&
					   venta_getZona(bufferVenta,&auxZona) == 0 &&
					   venta_getEstadoCobranza(bufferVenta,&auxEstado) == 0 )
					{
						fprintf(pFile,"%d, %d, %s, %d, %d, %d\n",
								auxIdVenta, auxIdCliente, auxNombreArchivo,auxCantidad,auxZona, auxEstado );
					}

				}
				retorno = 0;
				fclose(pFile);
			}
		}
	}
	 return retorno;
}

/** \brief Guarda los datos de los clientes en el archivo data.bin (modo binario).
 *
 * \param path char* direccion donde se encuentra el archivo
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int controller_clienteSaveAsBinary(char* path , LinkedList* this)
{
	FILE* pFile;
	Cliente* bufferCliente;
	int retorno = -1;

	if(path != NULL && this != NULL)
	{
		pFile = fopen(path,"wb");
		if(pFile != NULL)
		{
			for(int i = 0; i < ll_len(this); i++)
			{
				bufferCliente = (Cliente*)ll_get(this,i);
				fwrite(bufferCliente, sizeof(Cliente), 1, pFile);
			}
			retorno = 0;
		}
		fclose(pFile);
	}
    return retorno;
}

/** \brief Alta de clientes
 *
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int controller_addCliente(LinkedList* this)
{
	int retorno = -1;

	Cliente* bufferCliente = cliente_new();
	int bufferId;
	char bufferNombre[SIZECLIENTE];
	char bufferApellido[SIZECLIENTE];
	int bufferCuit;

	if(this != NULL)
	{
		if((utn_getNombre("\nIngrese el nombre del cliente: ", "\nEse no es un nombre valido\n", bufferNombre, 2,SIZECLIENTE) == 0) &&
		   (utn_getNombre("\nIngrese el apellido del cliente: ", "\nEse no es un nombre valido\n", bufferApellido, 2,SIZECLIENTE) == 0) &&
		   (utn_getNumero("\nIngrese el cuit del cliente: ", "\nEse no es un cuit valido\n", &bufferCuit, 2,0,999999999) == 0))
		{

			if(controller_asignarIdCliente(this, &bufferId) == 0 &&
			   cliente_setId(bufferCliente, bufferId)==0 &&
			   cliente_setNombre(bufferCliente, bufferNombre)==0 &&
			   cliente_setApellido(bufferCliente, bufferApellido)==0 &&
			   cliente_setCuit(bufferCliente, bufferCuit)==0)

			{
				if(ll_contains(this, &bufferCuit) == 0)
				{
					printf("\nEl cliente dado de alta tiene el ID: %d", bufferId);
					ll_add(this, bufferCliente);
					retorno = 0;
				}
				else
				{
					printf("\nError: Ya existe un cliente con el cuit %d .", bufferCuit);
				}
			}
		}
		else
		{
			printf("\nSurgio un error durante la alta\n");
		}
	}

    return retorno;
}
int controller_venderAfiches(LinkedList* this, LinkedList* this2 )
{
	int retorno = -1;
	Venta* bufferVenta = venta_new();
	int auxIdCliente;
	int clienteAlAgregarVenta;
	int auxIdVenta;
	int auxCantidad;
	char bufferNombreArchivo[SIZEVENTAS];
	int auxZona;

	if(this != NULL && this2 != NULL)
	{
		if((controller_printClientes(this) == 0) &&
			utn_getNumero("\nIngrese el ID al que le quiere asignar afiches ", "\nEse no es un id valido\n",
						 &auxIdCliente, 2,1,99999) == 0 )
		{
			clienteAlAgregarVenta =controller_buscarClientePorId(this, auxIdCliente);
			if(clienteAlAgregarVenta != -1)
			{
				if(utn_getNombre("\nIngrese el nombre del afiche: ", "\nEse no es un nombre valido\n", bufferNombreArchivo, 2,SIZECLIENTE) == 0 &&
				   utn_getNumero("\nIngrese la cantidad de afiches: ", "\nEsa no es una cantidad valida\n", &auxCantidad, 2,0,100) == 0 &&
				   utn_getNumero("\nIngrese la zona donde se pegaran los afiches:\n1-CABA\n2-ZONA SUR\n3-ZONA OESTE\n",
						      "\nEsa no es una zona valido\n", &auxZona, 2, 1, 3) == 0 &&
				   controller_asignarIdVenta(this2, &auxIdVenta) == 0 &&
				   venta_setIdCliente(bufferVenta, clienteAlAgregarVenta)==0 &&
				   venta_setIdVenta(bufferVenta, auxIdVenta) == 0 &&
				   venta_setCantidadAfiches(bufferVenta, auxCantidad) == 0 &&
				   venta_setNombreArchivo(bufferVenta, bufferNombreArchivo)==0 &&
				   venta_setZona(bufferVenta, auxZona)==0 &&
				   venta_setEstadoCobranza(bufferVenta, SINCOBRAR)==0)
				{
					printf("\nLa venta dada de alta tiene el ID: %d", auxIdVenta);
					ll_add(this2, bufferVenta);
					retorno = 0;
				}

			}
			else
			{
				printf("\nEse cliente no existe");
			}
		}
	}

	return retorno;
}


int controller_printClientes(LinkedList* this)
{
	int retorno = -1;
	int len;
	Cliente* bufferCliente;
	int auxId;
	char auxNombre[SIZECLIENTE];
	char auxApellido[SIZECLIENTE];
	int auxCuit;

	if(this != NULL)
	{
		len = ll_len(this);
		printf("\n\n ID   NOMBRE    APELLIDO   CUIT ");
		for(int i = 0; i < len; i++)
		{
			bufferCliente = (Cliente*) ll_get(this, i);
			cliente_getId(bufferCliente, &auxId);
			cliente_getNombre(bufferCliente, auxNombre);
			cliente_getApellido(bufferCliente, auxApellido);
			cliente_getCuit(bufferCliente, &auxCuit);
			printf("\n%d- %s  -   %s  -    %d  ", auxId, auxNombre, auxApellido, auxCuit);
		}
		retorno = 0;
	}

	return retorno;
}
int controller_saveOneClientAsText(char* path , LinkedList* this)
{
	int retorno = -1;
	int len;
	if(path != NULL && this != NULL)
	{
	//	for(int i =)
	}

	return retorno;
}
/** \brief Busca el proximo id en la lista
 *
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \return int  el indice deseado o -1 si hay error
 *
 */
int controller_encontrarIdMaximoCliente (LinkedList* this, int* id)
{
	int retorno = -1;
	int len;
	Cliente* bufferCliente;
	int auxId;
	int maximoId;

	if(this != NULL)
	{
		len = ll_len(this);
		for(int i = 0; i < len; i++)
		{
			bufferCliente = (Cliente*) ll_get(this, i);
			cliente_getId(bufferCliente, &auxId);
			if(auxId > maximoId || i == 0)
			{
				 maximoId = auxId;

			}
			*id = maximoId;
			retorno = 0;
		}
	}

	return retorno;
}

int controller_asignarIdCliente(LinkedList* this, int* id)
{
	int retorno = -1;
	int auxId;

	if(this != NULL && controller_encontrarIdMaximoCliente(this, &auxId) == 0)
	{
		auxId++;
		*id = auxId;
		retorno = 0;
	}

	return retorno;
}

int controller_encontrarIdMaximoVenta (LinkedList* this, int* id)
{
	int retorno = -1;
	int len;
	Venta* bufferVenta;
	int auxId;
	int maximoId;

	if(this != NULL)
	{
		len = ll_len(this);
		for(int i = 0; i < len; i++)
		{
			bufferVenta = (Venta*) ll_get(this, i);
			venta_getIdVenta(bufferVenta, &auxId);
			if(auxId > maximoId || i == 0)
			{
				 maximoId = auxId;

			}
			*id = maximoId;
			retorno = 0;
		}
	}

	return retorno;
}

int controller_asignarIdVenta(LinkedList* this, int* id)
{
	int retorno = -1;
	int auxId;

	if(this != NULL && controller_encontrarIdMaximoVenta(this, &auxId) == 0)
	{
		auxId++;
		*id = auxId;
		retorno = 0;
	}

	return retorno;
}
int controller_buscarClientePorId(LinkedList* this, int id)
{
	int retorno = -1;
	int len;
	Cliente* bufferCliente;
	int auxId;

	if(this != NULL)
	{
		len = ll_len(this);
		for(int i = 0; i < len; i++)
		{
			bufferCliente = (Cliente*) ll_get (this, i);
			cliente_getId(bufferCliente, &auxId);
			if(auxId == id)
			{
				retorno = i;
				break;
			}
		}
	}

	return retorno;
}



