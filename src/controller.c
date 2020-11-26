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

/** \brief Carga los datos de los clientes desde el archivo clientes.txt (modo texto).
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
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
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
	char auxCuit[SIZECUIT];

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
					   cliente_getCuit(bufferCliente,auxCuit) == 0 )
					{
						fprintf(pFile,"%d,%s,%s,%s\n",auxId, auxNombre, auxApellido,auxCuit); //SIN ESPACIOS
					}

				}
				retorno = 0;
				fclose(pFile);
			}
		}
	}
	 return retorno;
}

/** \brief Carga los datos de las ventas desde el archivo ventas.txt (modo texto).
 *
 * \param path char* direccion donde se encuentra el archivo
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int controller_ventaLoadFromText(char* path , LinkedList* this)
{
    int retorno = -1;

    FILE* pFile = fopen(path,"r");
    if(pFile !=NULL)
    {
    	parser_ventaFromText(pFile,this);
    	retorno = 0;
    }
    fclose(pFile);

    return retorno;
}
/** \brief Guarda los datos de las ventas en el archivo ventas.txt (modo texto).
 *
 * \param path char* direccion donde se encuentra el archivo
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
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
						fprintf(pFile,"%d,%d,%s,%d,%d,%d\n",
								auxIdVenta, auxIdCliente, auxNombreArchivo,auxCantidad,auxZona, auxEstado);
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

	Cliente* bufferCliente;
	int bufferId = 1000;
	char bufferNombre[SIZECLIENTE];
	char bufferApellido[SIZECLIENTE];
	char bufferCuit[SIZECUIT];

	if(this != NULL)
	{
		bufferCliente = cliente_new();
		if((utn_getNombre("\nIngrese el nombre del cliente:", "\nEse no es un nombre valido\n", bufferNombre, 2,SIZECLIENTE) == 0) &&
		   (utn_getNombre("\nIngrese el apellido del cliente:", "\nEse no es un nombre valido\n", bufferApellido, 2,SIZECLIENTE) == 0) &&
		   (utn_getCuit("\nIngrese el cuit del cliente(solo numeros):", "\nEse no es un cuit valido\n", bufferCuit, 2,SIZECUIT) == 0) &&
		    cliente_buscarCuitRepetido(this, bufferCuit) == 0)
		{
			if(controller_asignarIdCliente(this, &bufferId) == 0 &&
			   cliente_setId(bufferCliente, bufferId)==0 &&
			   cliente_setNombre(bufferCliente, bufferNombre)==0 &&
			   cliente_setApellido(bufferCliente, bufferApellido)==0 &&
			   cliente_setCuit(bufferCliente, bufferCuit)== 0)
				{
					printf("\nEl cliente dado de alta tiene el ID: %d", bufferId);
					ll_add(this, bufferCliente);
					retorno = 0;
				}
		}
		else
		{
			cliente_delete(bufferCliente);
			printf("\nSurgio un error durante el alta\n");
		}
	}
    return retorno;
}

/** \brief Alta de ventas
 *
 * \param this1 LinkedList* es donde esta contenida la direccion de memoria de la lista de los clientes
 * \param this2 LinkedList* es donde esta contenida la direccion de memoria de la lista de las ventas
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int controller_venderAfiches(LinkedList* this1, LinkedList* this2 )
{
	int retorno = -1;
	Venta* bufferVenta;
	int auxIdCliente;
	int clienteAlAgregarVenta;
	int auxIdVenta;
	int auxCantidad;
	char bufferNombreArchivo[SIZEVENTAS];
	int auxZona;

	if(this1 != NULL && this2 != NULL)
	{
		bufferVenta = venta_new();
		printf("\n\n ID   NOMBRE    APELLIDO   CUIT ");
		if((ll_map(this1, cliente_printCliente) == 0) &&
			utn_getNumero("\nIngrese el ID al que le quiere asignar afiches ", "\nEse no es un id valido\n",
						 &auxIdCliente, 2,1,99999) == 0 )
		{
			clienteAlAgregarVenta =cliente_buscarClientePorId(this1, auxIdCliente);
			if(clienteAlAgregarVenta != -1)
			{
				if(utn_getString("\nIngrese el nombre del afiche: ", "\nEse no es un nombre valido\n", bufferNombreArchivo, 2,SIZECLIENTE) == 0 &&
				   utn_getNumero("\nIngrese la cantidad de afiches: ", "\nEsa no es una cantidad valida\n", &auxCantidad, 2,1,100) == 0 &&
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
				else
				{
					venta_delete(bufferVenta);
				}
			}
			else
			{
				venta_delete(bufferVenta);
				printf("\nEse cliente no existe");
			}
		}
	}

	return retorno;
}
/** \brief Modifica una venta
 *
 * \param this1 LinkedList* es donde esta contenida la direccion de memoria de la lista de los clientes
 * \param this2 LinkedList* es donde esta contenida la direccion de memoria de la lista de las ventas
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int controller_modificarVenta(LinkedList* this1, LinkedList* this2)
{
	int retorno = -1;
	int auxIdVenta;
	int auxIdCliente;
	int clienteAMostrar;
	int opcion;
	int auxCantidad;
	char auxNombreArchivo[SIZEVENTAS];
	int auxZona;
	LinkedList* listaNoCobrados = NULL;
	Venta* bufferVenta;
	Cliente* bufferCliente;

	if(this1 != NULL && this2 != NULL)
	{
		printf("\nID VENTA - ID CLIENTE -    NOMBRE ARCHIVO    - CANTIDAD AFICHES- ZONA - ESTADO\n");
		listaNoCobrados = ll_filter(this2, venta_buscarVentasSinCobrar);
		if(ll_map(listaNoCobrados, venta_imprimirUnaVenta) == 0 &&
		   utn_getNumero("\n\nIngrese el ID de la venta que quiere modificar: ", "\nEse no es un id valido\n",
						&auxIdVenta, 2,1,99999) == 0)
		{
				bufferVenta = venta_buscarVentaPorId(this2,auxIdVenta);
				if(bufferVenta != NULL &&
				   venta_getIdCliente(bufferVenta,&auxIdCliente ) == 0)
				{
					bufferCliente = cliente_devolverClientePorId(this1, auxIdCliente);
					if(cliente_getId(bufferCliente,&clienteAMostrar)== 0 &&
					   cliente_imprimirClienteDeUnaVenta(this1, this2, clienteAMostrar) == 0 &&
					   venta_getCantidadAfiches(bufferVenta,&auxCantidad) == 0 &&
					   venta_getNombreArchivo(bufferVenta,auxNombreArchivo) == 0 &&
					   venta_getZona(bufferVenta,&auxZona) == 0)
					{
						do
						{
							printf("\n\nCantidad afiches: %d Nombre Archivo:%s   Zona: %d\n",auxCantidad, auxNombreArchivo, auxZona);
							if(
								utn_getNumero("\nQue campo desea modificar?:\n1-Cantidad de afiches.\n2-Nombre del archivo.\n"
											 "3-Zona(1- CABA  2- ZONA SUR 3- ZONA OESTE)\n4-Salir\n\n",
											 "\nEsa no es una opcion valida\n", &opcion, 2, 1, 4) == 0)
							{
								switch(opcion)
								{
								case 1:
									if(utn_getNumero("\nIngrese la nueva cantidad de afiches: ",
									  "\nEsa no es una cantidad valida\n", &auxCantidad, 2, 1,100) == 0  &&
											venta_setCantidadAfiches(bufferVenta,auxCantidad ) == 0)
									{
										printf("\nCambio logrado exitosamente\n");
									}
									break;
								case 2:
									if(utn_getString("\nIngrese el nuevo nombre del afiche: ",
											"\nEse no es un nombre valido\n", auxNombreArchivo, 2,SIZEVENTAS) == 0 &&
											venta_setNombreArchivo(bufferVenta,auxNombreArchivo) == 0)
									{
										printf("\nCambio logrado exitosamente\n");
									}
									break;

								case 3:
									if(utn_getNumero("\nIngrese la zona donde se pegaran los afiches:\n1-CABA\n2-ZONA SUR\n3-ZONA OESTE\n",
											  "\nEsa no es una zona valido\n", &auxZona, 2, 1, 3) == 0 &&
										venta_setZona(bufferVenta,auxZona) == 0 )
									{
										printf("\nCambio logrado exitosamente\n");
									}
									break;
								}
							}
						}while(opcion != 4);
						retorno = 0;
					}
				}
			}
			else
			{
				printf("\nEse ID no es modificable.");
			}

	}
	return retorno;
}

/** \brief Modifica el estado de la cobranza de una venta
 *
 * \param this1 LinkedList* es donde esta contenida la direccion de memoria de la lista de los clientes
 * \param this2 LinkedList* es donde esta contenida la direccion de memoria de la lista de las ventas
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int controller_cobrarVenta(LinkedList* this1, LinkedList* this2)
{
	int retorno = -1;
	int auxIdVenta;
	int flagCobranza = 2;
	LinkedList* listaNoCobrados = NULL;
	Venta* bufferVenta;

	if(this1 != NULL && this2 != NULL)
	{
		printf("\nID VENTA - ID CLIENTE -    NOMBRE ARCHIVO    - CANTIDAD AFICHES- ZONA - ESTADO\n");
		listaNoCobrados = ll_filter(this2, venta_buscarVentasSinCobrar);
		if(ll_map(listaNoCobrados, venta_imprimirUnaVenta) == 0 &&
		   utn_getNumero("\n\nIngrese el ID de la venta que quiere modificar: ", "\nEse no es un id valido\n",
						&auxIdVenta, 2,1,999) == 0)
		{
			if(cliente_imprimirClienteDeUnaVenta(this1, this2, auxIdVenta) == 0)
			{
				bufferVenta = venta_buscarVentaPorId(this2,auxIdVenta);
					if(utn_getNumero("\n\nEsta realmente seguro que quiere marcar esta venta como cobrada?\n"
									 "\n1-Marcar venta como cobranda\n2-Abortar operacion\n\n",
									 "\nEsa no es una opcion valida\n", &flagCobranza, 2, 1, 2) == 0 &&
					   flagCobranza	 == 1)
					{
						venta_setEstadoCobranza(bufferVenta,COBRADA);
						retorno = 0;
					}
					else
					{
						printf("\nOperacion abortada\n");
					}
			}
			else
			{
				printf("\nEse ID no es modificable.");
			}
		}
	}
	return retorno;
}


/** \brief Busca el id maximo de la lista
 *
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \param id int* el indice maximo encontrado
 * return int  el indice deseado o -1 si hay error
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

/** \brief Busca el proximo id en la lista
 *
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \param id int* puntero al proximo id
 * \return -1 si hay error o 0 si sale bien
 */
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

/** \brief Busca el id maximo de la lista
 *
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \param id int* el indice maximo encontrado
 * return int  el indice deseado o -1 si hay error
 */
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

/** \brief Busca el proximo id en la lista
 *
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \param id int* puntero al proximo id
 * \return -1 si hay error o 0 si sale bien
 */
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

/** \brief Imprime el cliente de una venta
 *
 * \param this1 LinkedList* es donde esta contenida la direccion de memoria de la lista de los clientes
 * \param this2 LinkedList* es donde esta contenida la direccion de memoria de la lista de las ventas
 * \param id int el id del cliente a encontrar
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int cliente_imprimirClienteDeUnaVenta(LinkedList* this1,LinkedList* this2, int id)
{
	int retorno = -1;
	int len;
	Venta* bufferVenta;
	Cliente* bufferCliente;
	int auxIdCliente;
	int idABuscar;
	char auxNombre[SIZECLIENTE];
	char auxApellido[SIZECLIENTE];
	char auxCuit[SIZECUIT];
	int auxEstado;

	if(this1 != NULL && this2 != NULL)
	{
		len = ll_len(this1);
		bufferVenta = venta_buscarVentaPorId(this2, id);
		for(int i = 0; i < len; i++)
		{
			bufferCliente = (Cliente*) ll_get (this1, i);

			if(cliente_getId(bufferCliente, &auxIdCliente) == 0 &&
			   venta_getIdCliente(bufferVenta,&idABuscar ) == 0 &&
			   auxIdCliente == idABuscar &&
			   venta_getEstadoCobranza(bufferVenta,&auxEstado ) == 0&&
			   auxEstado == SINCOBRAR &&
			   cliente_getNombre(bufferCliente, auxNombre) == 0 &&
		       cliente_getApellido(bufferCliente, auxApellido) == 0 &&
			   cliente_getCuit(bufferCliente, auxCuit) == 0)
			{
				printf("\nNombre:%s - Apellido:%s - Cuit:%s", auxNombre, auxApellido, auxCuit );
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}



