/*
 * parser.c
 *
 *  Created on: 2020/11/20
 *      Author: PC
 */
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "clientes.h"

/** \brief Parsea los datos los datos de los clientes desde el archivo data.csv (modo texto).
 *
 * \param path char* direccion donde se encuentra el archivo
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int parser_clienteFromText(FILE* pFile , LinkedList* this)
{
	Cliente* bufferCliente;
	int retorno = -1;
	char auxId[4096];
	char auxNombre[4096];
	char auxApellido[4096];
	char auxCuit[4096];

	if(pFile != NULL)
	{
		do
		{
			if (fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n", auxId,auxNombre ,auxApellido ,auxCuit)== 4)
			{
				//printf("%s, %s, %s, %s\n", auxId, auxNombre, auxApellido, auxCuit);
				bufferCliente = cliente_newParametros(auxId,auxNombre,auxApellido,auxCuit);
				if(bufferCliente != NULL)
				{
					ll_add(this, bufferCliente);
				}
			}

		}while(feof(pFile) == 0);
		retorno = 0;
	}
    return retorno;
}

/** \brief Parsea los datos los datos de los clientes desde el archivo data.bin (modo binario).
 *
 * \param path char* direccion donde se encuentra el archivo
 * \param this LinkedList* es donde esta contenida la direccion de memoria de la lista
 * \return int -1 si hay error o 0 si anduvo bien
 *
 */
int parser_ClienteFromBinary(FILE* pFile , LinkedList* this)
{
	int retorno = -1;
	Cliente* bufferCliente;
	int retornoLectura;

	if(pFile != NULL)
	{
		do
		{
			bufferCliente = cliente_new();
			if(bufferCliente != NULL)
			{
				retornoLectura =fread(bufferCliente,sizeof(Cliente),1,pFile);
				if(retornoLectura == 1)
				{
					ll_add(this,bufferCliente);
				}
				else
				{
					cliente_delete(bufferCliente);
				}

			}

		}while(feof(pFile) == 0);

		retorno = 0;
	}
	return retorno;
}

