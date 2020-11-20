/*
 * utn.c
 *
 *  Created on: 2020/10/12
 *      Author: PC
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#define LIMITE_BUFFER_STRING 4905

static int myGets(char *cadena, int longitud);
static int getFloat(float *pResultado);
static int isFloat(char *cadena);
static int getInt(int *pResultado);


/**
 * \brief Solicita un float al usuario
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param float* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int minimo, valor minimo admitido
 * \param int minimo, valor maximo admitido
 * \return 0 en caso de exito, -1 de caso contrario
 *
 */

float utn_getFloat(char *mensaje, char *mensajeError, float *pResultado,int reintentos,float min, float max)
{
	int retorno = -1;
	float bufferFloat;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && min <= max && reintentos >= 0)
	{
		do
		{
			printf("%s", mensaje);
			if(getFloat(&bufferFloat)==0)
			{
				if(bufferFloat >= min && bufferFloat <= max)
				{
					*pResultado = bufferFloat;
					retorno = 0;
					break;
				}
				else
				{
					printf("%s", mensajeError);
					reintentos--;
				}

			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}

		}while(reintentos >= 0);
	}
	return retorno;

}

int ordenar(int array[], int len)
{
	int retorno= -1;
	int aux;
	int i;
	int flagDesordenado = 1;

	if(array!=NULL && len > 0)
	{
		while(flagDesordenado==1)
		{
			flagDesordenado = 0;
			for(i=0; i<(len-1); i++)
			{
				if(array[i] > array[i+1])
				{
					aux = array[i];
					array[i] = array[i+1];
					array[i+1]= aux;
					flagDesordenado = 1;
				}

			}
		}
	}
	retorno = 0;
	return retorno;

}

/**
 * \brief Solicita un entero al usuario
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int minimo, valor minimo admitido
 * \param int minimo, valor maximo admitido
 * \return 0 en caso de exito, -1 de caso contrario
 *
 */
int utn_getNumero(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int minimo,int maximo)
{
	int retorno = -1;
	int bufferInt;
	if(	mensaje != NULL && 	mensajeError != NULL &&	pResultado != NULL && reintentos >= 0 && maximo >= minimo)
	{
		do
		{
			printf("%s",mensaje);
			if(getInt(&bufferInt)==0 && bufferInt >=minimo && bufferInt <=maximo)
			{
				*pResultado = bufferInt;
				retorno= 0;
				break;
			}
			printf("%s",mensajeError);
			reintentos--;

		}while(reintentos >= 0);
	}
	return retorno;
}

static int getInt(int *pResultado)
{
	int retorno=-1;
	char bufferString[5000];
	if(pResultado !=NULL && myGets(bufferString,sizeof(bufferString))==0 && esNumerica(bufferString,5000))
	{
		retorno =0;
		*pResultado = atoi(bufferString);
	}
	return retorno;
}

/**
 * \brief 	Verifica una cadena recibida como parametro para determinar
 * 			si es un nombre valido
 * \param char* cadena, Cadena a analizar
 * \param int limite, indica la cantidad de letras maxima de la cadena
 * \return (0) Indicar que no es un nombre valido / (1) Indica que que es un nombre valido
 *
 */
int esUnNombreValido(char* cadena,int limite)
{
	int respuesta = 1; // TODO OK

	for(int i=0; i<=limite && cadena[i] != '\0';i++)
	{
		//esta mal <----- A - Z -----> Esta mal.
		if(	(cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			cadena[i] != '.' && cadena[i] != ' ')  // para que si pone el punto no te saque.
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}


/**
 * \brief Solicita un nombre al usuario
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param char* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int limite, indica la cantidad de letras maxima del nombre
 * \return 0 en caso de exito, -1 de caso contrario
 *
 */
int utn_getNombre(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
				strnlen(bufferString,sizeof(bufferString)-1)<= limite &&
				esUnNombreValido(bufferString,limite) != 0 )
			{
				retorno = 0;
				//NO EXISTE pResultado = bufferString;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);

	}
	return retorno;

}
/**
 * \brief Solicita un string al usuario
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param char* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int limite, indica la cantidad de letras maxima del nombre
 * \return 0 en caso de exito, -1 de caso contrario
 *
 */
int utn_getString(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
				strnlen(bufferString,sizeof(bufferString)-1)<= limite)
			{
				retorno = 0;
				//NO EXISTE pResultado = bufferString;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);

	}
	return retorno;

}

static int myGets(char *cadena, int longitud)
{
	fflush(stdin);
	fgets (cadena, longitud, stdin); //llena con lo escribio el usuario y pone e; /0 cuando presione enter. es como scanf pero mejor
	cadena[strlen (cadena) - 1] = '\0'; //por si me paso del limite, el fgets igual te lo corta
	return 0;
}


int esNumerica(char* cadena, int limite)
{
	int retorno = 1; // VERDADERO
	int i;
	for(i=0;i<limite && cadena[i] != '\0';i++)
	{
		if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))
		{
			continue;
		}
		if(cadena[i] > '9' || cadena[i] < '0')
		{
			retorno = 0;
			break;
		}
		//CONTINUE
	}
	//BREAK
	return retorno;
}
/*
int isValidInt(int limite)
{
	int retorno = 1; // VERDADERO
	int i;
	for(i=0; i<limite;i++)
	{
		if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))
		{
			continue;
		}
		if(cadena[i] > '9' || cadena[i] < '0')
		{
			retorno = 0;
			break;
		}
		//CONTINUE
	}
	//BREAK
	return retorno;
}*/
/**
 * brief verifica si la cadena de texto es flotante.
 * return 0 si da OK o -1 si no
 */


static int getFloat(float *pResultado)
{
	int retorno = -1;
	char buffer[460];

	if(pResultado != NULL)
	{
	  if(myGets(buffer,sizeof(buffer))==0 && isFloat(buffer)==1)
	  {
		  *pResultado= atof(buffer);
		   retorno = 0;
	  }
	}
	return retorno;
}
static int isFloat(char *cadena)
{
	int retorno = 1; // VERDADERO
	int contadorPuntos= 0;

	if(cadena != NULL && strlen(cadena)> 0)
	{
		for(int i=0; cadena[i] != '\0';i++)
		{
			if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))
			{
			    continue;
			}
	    	if(cadena[i]<  '0' || cadena[i] > '9')
			{
				if(cadena[i] == '.' && contadorPuntos ==0)
				{
					contadorPuntos++;
				}
				else
				{
					retorno=0;
					break;
				}
			 }

		  }
	}
  return retorno;
}
