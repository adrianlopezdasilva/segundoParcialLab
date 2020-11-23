/*
 * clientes.c
 *
 *  Created on: 2020/11/20
 *      Author: PC
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "utn.h"


static int isValidCuit();
/** \brief Crea un nuevo Cliente
 *
 * \param void LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \return Cliente* en caso de que salga bien, NULL de lo contrario
 *
 */
Cliente* cliente_new(void)
{
	Cliente* bufferCliente;
	bufferCliente = (Cliente*)malloc(sizeof(Cliente));
	if(bufferCliente == NULL)
	{
		printf("\nLa lista esta llena\n");
	}
	return bufferCliente;
}

/** \brief Crea un nuevo Cliente, pasandole el valor de los campos como parametro
 *
 *\param idStr char* string que contiene el id a utilizar
 *\param nombreStr char* string que contiene el nombre a utilizar
 *\param horasTrabajadasStr char* string que contiene las horas trabajadas a utilizar
 *\param cuitStr char* string que contiene el cuit a utilizara
 *
 * \return Cliente* en caso de que salga bien, NULL de lo contrario
 *
 */
Cliente* cliente_newParametros(char* idStr,char* nombreStr,char* apellidoStr, char* cuitStr)
{
	Cliente* this = cliente_new();
	int auxId;
	int auxCuit;

	auxId= atoi(idStr);
	auxCuit= atoi(cuitStr);
	if(this != NULL)
	{
		if((cliente_setId(this, auxId)) == 0 &&
			(cliente_setNombre(this, nombreStr)) == 0 &&
			(cliente_setApellido(this, apellidoStr)) == 0 &&
			(cliente_setCuit(this, auxCuit) == 0))
		{
			return this;
		}
	}
	return NULL;
}

/** \brief Elimina un cliente
 *
 * \param this Cliente* el Cliente a borrar
 * \return void
 */
void cliente_delete(Cliente* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}

/** \brief Fija el id de un cliente
 *
 * \param this Cliente* el Cliente a utilizar
 * \param id int el id a fijar
 *
 * \return -1 si hay error, 0 si funciona bien
 */

int cliente_setId(Cliente* this,int id)
{
	int retorno = -1;
	if(this != NULL && id >0)
	{
		this->idCliente = id;
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene el id de un cliente
 *
 * \param this Cliente* el Cliente a utilizar
 * \param id int* el id obtenido
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int cliente_getId(Cliente* this,int* id)
{
	int retorno = -1;
	if(this != NULL)
	{
		*id = this->idCliente;
		retorno = 0;
	}
	return retorno;
}

/** \brief Fija el nombre de un cliente
 *
 * \param this Cliente* el Cliente a utilizar
 * \param nombre char* el nombre a fijar
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int cliente_setNombre(Cliente* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		if(esUnNombreValido(nombre,SIZECLIENTE)== 1 ) // ESTA FUNCION BUSCA SI HAY UN ERROR
		{
			strncpy(this->nombre,nombre, sizeof(this->nombre));
			retorno = 0;
		}

	}
	return retorno;
}

/** \brief Obtiene el nombre de un cliente
 *
 * \param this Cliente* el Cliente a utilizar
 * \param nombre char* el nombre obtenido
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int cliente_getNombre(Cliente* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		strncpy(nombre,this->nombre, SIZECLIENTE);
		retorno = 0;
	}
	return retorno;
}

/** \brief Fija el apellido
 *
 * \param this Cliente* el Cliente a utilizar
 * \param horasTrabajadas int las horas trabajadas a fijar
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int cliente_setApellido(Cliente* this,char* apellido)
{
	int retorno = -1;
	if(this != NULL && apellido != NULL)
	{
		if(esUnNombreValido(apellido,SIZECLIENTE)== 1 ) // ESTA FUNCION BUSCA SI HAY UN ERROR
		{
			strncpy(this->apellido,apellido, sizeof(this->apellido));
			retorno = 0;
		}

	}
	return retorno;
}
/** \brief Obtiene el apellido de un cliente
 *
 * \param this Cliente* el Cliente a utilizar
 * \param horasTrabajadas int* las horas trabajadas obtenidas
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int cliente_getApellido(Cliente* this,char* apellido)
{
	int retorno = -1;
	if(this != NULL && apellido != NULL)
	{
		strncpy(apellido,this->apellido, SIZECLIENTE);
		retorno = 0;
	}
	return retorno;
}

/** \brief Fija el cuit  de un cliente
 *
 * \param this Cliente* el Cliente a utilizar
 * \param cuit int el cuit a fijar
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int cliente_setCuit(Cliente* this,int cuit)
{
	int retorno = -1;
	if(this != NULL && cuit >0)
	{
		if(isValidCuit(cuit) == 1)
		{
			this->cuit =cuit;
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief Obtiene el cuit de un cliente
 *
 * \param this Cliente* el Cliente a utilizar
 * \param cuit int* el cuit obtenido
 *
 * \return -1 si hay error, 0 si funciona bien
 */
int cliente_getCuit(Cliente* this,int* cuit)
{
	int retorno = -1;
	if(this != NULL)
	{
		*cuit = this->cuit;
		retorno = 0;
	}
	return retorno;
}
/** \brief Compara la lista de clientes segun su nombre
 *
 * \param thisOne void* El primer campo a comprar
 * \param thisTwo void* El segundo campo a comprar
 *
 * \return 1 si el primer campo es mas grande o -1 de lo contrario, 0 si hay error
 */
int cliente_compareByName(void* thisOne , void* thisTwo)
{
	int retorno = 0;
	char nombreUno[SIZECLIENTE];
	char nombreDos[SIZECLIENTE];

	Cliente* bufferEmpleadoUno;
	Cliente* bufferEmpleadoDos;

	bufferEmpleadoUno = (Cliente*) thisOne;
	bufferEmpleadoDos = (Cliente*) thisTwo;

	if(thisOne != NULL && thisTwo != NULL)
	{
		if(cliente_getNombre(bufferEmpleadoUno, nombreUno)== 0 &&
		   cliente_getNombre(bufferEmpleadoDos, nombreDos) == 0)
		{
			if(strncmp(nombreUno, nombreDos, SIZECLIENTE ) > 0)
			{
				retorno = 1;
			}
			else if(strncmp(nombreUno, nombreDos, SIZECLIENTE ) < 0)
			{
				retorno = -1;
			}
		}
	}
	return retorno;
}

/** \brief Compara la lista de clientes segun sus horas trabajadas
 *
 * \param thisOne void* El primer campo a comprar
 * \param thisTwo void* El segundo campo a comprar
 *
 * \return 1 si el primer campo es mas grande o -1 de lo contrario, 0 si hay error
 */
int cliente_compareByApellido(void* thisOne , void* thisTwo)
{
	int retorno = 0;
	char nombreUno[SIZECLIENTE];
	char nombreDos[SIZECLIENTE];

	Cliente* bufferEmpleadoUno;
	Cliente* bufferEmpleadoDos;

	bufferEmpleadoUno = (Cliente*) thisOne;
	bufferEmpleadoDos = (Cliente*) thisTwo;

	if(thisOne != NULL && thisTwo != NULL)
	{
		if(cliente_getApellido(bufferEmpleadoUno, nombreUno)== 0 &&
		   cliente_getApellido(bufferEmpleadoDos, nombreDos) == 0)
		{
			if(nombreUno > nombreDos)
			{
				retorno = 1;
			}
			else if (nombreUno < nombreDos)
			{
				retorno = -1;
			}
		}
	}
	return retorno;
}
/** \brief Compara la lista de clientes segun su salario
 *
 * \param thisOne void* El primer campo a comprar
 * \param thisTwo void* El segundo campo a comprar
 *
 * \return 1 si el primer campo es mas grande o -1 de lo contrario, 0 si hay error
 */
int Cliente_compareByCuit(void* thisOne , void* thisTwo)
{
	int retorno = 0;
	int auxCuitUno;
	int auxCuitDos;

	Cliente* bufferEmpleadoUno;
	Cliente* bufferEmpleadoDos;

	bufferEmpleadoUno = (Cliente*) thisOne;
	bufferEmpleadoDos = (Cliente*) thisTwo;

	if(thisOne != NULL && thisTwo != NULL)
	{
		if(cliente_getCuit(bufferEmpleadoUno, &auxCuitUno)== 0 &&
		   cliente_getCuit(bufferEmpleadoDos, &auxCuitDos) == 0)
		{
			if(auxCuitUno > auxCuitDos)
			{
				retorno = 1;
			}
			else if (auxCuitUno < auxCuitDos)
			{
				retorno = -1;
			}
		}
	}
	return retorno;
}


int isValidCuit()
{
	return 1;
}




