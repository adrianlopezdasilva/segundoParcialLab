/*
 * ventas.c
 *
 *  Created on: 2020/11/20
 *      Author: PC
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ventas.h"
#include "LinkedList.h"
#include "utn.h"


static int isValidZona (int zona);
static int isValidCantidadAfiches(int horas);

/** \brief Crea un nuevo venta
 *
 * \param void LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \return Venta* en caso de que salga bien, NULL de lo contrario
 *
 */
Venta* venta_new(void)
{

	Venta* bufferVenta;
	bufferVenta = (Venta*)malloc(sizeof(Venta));
	if(bufferVenta == NULL)
	{
		printf("\nLa lista esta llena\n");
	}
	return bufferVenta;
}

/** \brief Crea un nuevo venta, pasandole el valor de los campos como parametro
 *
 *\param idStr char* string que contiene el idVenta a utilizar
 *\param nombreArchivoStr char* string que contiene el nombreArchivo a utilizar
 *\param cantidadStr char* string que contiene las horas trabajadas a utilizar
 *\param zonaStr char* string que contiene el zona a utilizara
 *
 * \return Venta* en caso de que salga bien, NULL de lo contrario
 *
 */
Venta* venta_newParametros(char* idVentaStr,char* idClienteStr, char* nombreArchivoStr,char* cantidadStr, char* zonaStr,char* estadoCobranzaStr)
{
	Venta* this = venta_new();
	int auxIdVenta;
	int auxIdCliente;
	int auxCantidad;
	int auxZona;
	int auxEstado;

	auxIdVenta= atoi(idVentaStr);
	auxIdCliente= atoi(idClienteStr);
	auxCantidad= atoi(cantidadStr);
	auxZona= atoi(zonaStr);
	auxEstado = atoi(estadoCobranzaStr);
	if(this != NULL)
	{
		if((venta_setIdVenta(this, auxIdVenta)) == 0 &&
			(venta_setIdCliente(this, auxIdCliente)) == 0 &&
			(venta_setNombreArchivo(this, nombreArchivoStr)) == 0 &&
			(venta_setCantidadAfiches(this, auxCantidad)) == 0 &&
			(venta_setZona(this, auxZona) == 0) &&
			(venta_setEstadoCobranza(this, auxEstado) == 0))
		{
			return this;
		}
	}
	return NULL;
}

/** \brief Elimina un empleado
 *
 * \param this Venta* el venta a borrar
 * \return void
 */
void venta_delete(Venta* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}

/** \brief Fija el idVenta de un empleado
 *
 * \param this Venta* el venta a utilizar
 * \param idVenta int el idVenta a fijar
 *
 * \return -1 si hay error, 0 si funciona bien
 */

int venta_setIdVenta(Venta* this,int idVenta)
{
	int retorno = -1;
	if(this != NULL && idVenta >0)
	{
		this->idVenta = idVenta;
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene el idVenta de un empleado
 *
 * \param this Venta* el venta a utilizar
 * \param idVenta int* el idVenta obtenido
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int venta_getIdVenta(Venta* this,int* idVenta)
{
	int retorno = -1;
	if(this != NULL)
	{
		*idVenta = this->idVenta;
		retorno = 0;
	}
	return retorno;
}

/** \brief Fija el idCliente de un empleado
 *
 * \param this Venta* el venta a utilizar
 * \param idVenta int el idVenta a fijar
 *
 * \return -1 si hay error, 0 si funciona bien
 */

int venta_setIdCliente(Venta* this,int idCliente)
{
	int retorno = -1;
	if(this != NULL && idCliente >0)
	{
		this->idCliente = idCliente;
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene el idVenta de un empleado
 *
 * \param this Venta* el venta a utilizar
 * \param idVenta int* el idVenta obtenido
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int venta_getIdCliente(Venta* this,int* idCliente)
{
	int retorno = -1;
	if(this != NULL)
	{
		*idCliente = this->idCliente;
		retorno = 0;
	}
	return retorno;
}
/** \brief Fija el nombreArchivo de una venta
 *
 * \param this Venta* la venta a utilizar
 * \param nombreArchivo char* el nombreArchivo a fijar
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int venta_setNombreArchivo(Venta* this,char* nombreArchivo)
{
	int retorno = -1;
	if(this != NULL && nombreArchivo != NULL)
	{
		if(esUnNombreValido(nombreArchivo,SIZEVENTAS)== 1 ) // ESTA FUNCION BUSCA SI HAY UN ERROR
		{
			strncpy(this->nombreArchivo,nombreArchivo, SIZEVENTAS);
			retorno = 0;
		}

	}
	return retorno;
}

/** \brief Obtiene el nombreArchivo de una venta
 *
 * \param this Venta* la venta a utilizar
 * \param nombreArchivo char* el nombreArchivo obtenido
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int venta_getNombreArchivo(Venta* this,char* nombreArchivo)
{
	int retorno = -1;
	if(this != NULL && nombreArchivo != NULL)
	{
		strncpy(nombreArchivo,this->nombreArchivo, SIZEVENTAS);
		retorno = 0;
	}
	return retorno;
}

/** \brief Fija la cantidad de afiches de una venta
 *
 * \param this Venta* la venta a utilizar
 * \param cantidad int la cantidad de afiches  a fijar
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int venta_setCantidadAfiches(Venta* this,int cantidad)
{
	int retorno = -1;
	if(this != NULL && cantidad >0)
	{
		if(isValidCantidadAfiches(cantidad) == 1)
		{
			this->cantidad =cantidad;
			retorno = 0;
		}

	}
	return retorno;
}
/** \brief Obtiene la cantidad de afiches de una venta
 *
 * \param this Venta* la venta a utilizar
 * \param cantidad int* la cantidad de afiches obtenido
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int venta_getCantidadAfiches(Venta* this,int* cantidad)
{
	int retorno = -1;
	if(this != NULL)
	{
		*cantidad = this->cantidad;
		retorno = 0;
	}
	return retorno;
}

/** \brief Fija el zona  de una venta
 *
 * \param this Venta* la venta a utilizar
 * \param zona int la zona a fijar
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int venta_setZona(Venta* this,int zona)
{
	int retorno = -1;
	if(this != NULL && zona >0)
	{
		if(isValidZona(zona) == 1)
		{
			this->zona =zona;
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief Obtiene la zona de una venta
 *
 * \param this Venta* la venta a utilizar
 * \param zona int* la zona obtenido
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int venta_getZona(Venta* this,int* zona)
{
	int retorno = -1;
	if(this != NULL)
	{
		*zona = this->zona;
		retorno = 0;
	}
	return retorno;
}


/** \brief Valida que la zona este dentro de los rangos aceptables
 *
 * \param zona int La zona a validar
 * \return -1 si hay error, 1 si funciona bien
 */
static int isValidZona (int zona)
{
	int retorno = 1;

	if(zona < 0 || zona > 3)
	{
		retorno = -1;
	}

	return retorno;
}

/** \brief Obtiene el estado de la cobrazna de los afiches
 *
 * \param this Venta* la lista a utilizar
 * \param estadoCobranza int* el estadoCobranza obtenido
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int venta_getEstadoCobranza(Venta* this,int* estadoCobranza)
{
	int retorno = -1;
	if(this != NULL)
	{
		*estadoCobranza = this->estadoCobranza;
		retorno = 0;
	}
	return retorno;
}

/** \brief Fija el estado de la cobranza de una venta
 *
 * \param this Venta* el venta a utilizar
 * \param estadoCobranza int el estadoCobranza a fijar
 *
 * \return -1 si hay error, 0 si funciona bien
 */

int venta_setEstadoCobranza(Venta* this,int estadoCobranza)
{
	int retorno = -1;
	if(this != NULL && (estadoCobranza == 0  || estadoCobranza == 1))
	{
		this->estadoCobranza = estadoCobranza;
		retorno = 0;
	}
	return retorno;
}

/** \brief Valida que la cantidad de afiches este dentro de los rangos aceptables
 *
 * \param zona int El zona a validad
 * \return -1 si hay error, 1 si funciona bien
 */
static int isValidCantidadAfiches(int cantidad)
{
	int retorno = 1;

	if(cantidad < 0 || cantidad > 100)
	{
		retorno = -1;
	}

	return retorno;
}
/** \brief Funcion criterio para ll_filter, busca las ventas sin cobrar
 *
 * \param this void* La lista a ser usada
 * \return -1 en caso de que haya error, 0 si bien
 */
int venta_buscarVentasSinCobrar(void* this)
{
	int retorno = -1;
	Venta* bufferVenta = (Venta*) this;
	int auxEstado;

	if(this != NULL)
	{
		if(venta_getEstadoCobranza(bufferVenta, &auxEstado)== 0 &&
		   auxEstado == SINCOBRAR )
		{
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief Funcion criterio para ll_filter, busca las ventas sin cobrar
 *
 * \param this void* La lista a ser usada
 * \return -1 en caso de que haya error, 0 si bien
 */
int venta_buscarVentasCobradas(void* this)
{
	int retorno = -1;
	Venta* bufferVenta = (Venta*) this;
	int auxEstado;

	if(this != NULL)
	{
		if(venta_getEstadoCobranza(bufferVenta, &auxEstado)== 0 &&
		   auxEstado == COBRADA )
		{
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief Busca una coincidencia de un id pasado por parametro con un id existente en la lista
 *
 * \param this Linkedlist* la lista a utilizar
 * \param id int el id a comparar
 *
 * \return Venta* en caso de que salga bien, NULL de lo contrario
 */
Venta* venta_buscarVentaPorId(LinkedList* this, int id)
{
	int len;
	Venta* bufferVenta = NULL;
	int auxId;

	if(this != NULL)
	{
		len = ll_len(this);
		for(int i = 0; i < len; i++)
		{
			bufferVenta = (Venta*) ll_get (this, i);
			if(venta_getIdVenta(bufferVenta, &auxId) == 0 &&
			   id == auxId)
			{
				break;
			}
		}
	}
	return bufferVenta;
}

int venta_ventasDeUnCliente(void* pElement, void* arg)
{
	int retorno = -1;
	int auxCantidad = 0;
	int* auxIdCliente = (int*) arg;
	Venta* bufferVenta = (Venta*) pElement;
	int bufferId;

	if(venta_getIdCliente(bufferVenta, &bufferId) == 0 &&
	   bufferId == *auxIdCliente &&
	   venta_getCantidadAfiches(bufferVenta, &auxCantidad) == 0)
	{
		retorno = auxCantidad;
	}
	return retorno;
}

int venta_imprimirUnaVenta(void* this)
{
	int retorno = -1;
	Venta* bufferVenta = (Venta*) this;
	int auxEstado;
	int auxIdVenta;
	int auxIdCliente;
	int auxCantidad;
	char auxNombreArchivo[SIZEVENTAS];
	int auxZona;

	if(this != NULL)
	{
		if(venta_getEstadoCobranza(bufferVenta, &auxEstado)== 0 &&
		   venta_getIdCliente(bufferVenta, &auxIdCliente)==0 &&
		   venta_getIdVenta(bufferVenta, &auxIdVenta) == 0 &&
		   venta_getCantidadAfiches(bufferVenta, &auxCantidad) == 0 &&
		   venta_getNombreArchivo(bufferVenta, auxNombreArchivo)==0 &&
		   venta_getZona(bufferVenta, &auxZona)==0 )
		{
			printf("\n%d - %d - %s -  %d - %d - %d",auxIdVenta, auxIdCliente, auxNombreArchivo, auxCantidad, auxZona, auxEstado);
			retorno = 0;
		}

	}
	return retorno;

}
