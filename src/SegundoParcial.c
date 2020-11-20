/*
 ============================================================================
 Name        : SegundoParcial.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "utn.h"

int main(void)
{
	setbuf(stdout, NULL);
	int opcion;

	LinkedList* listaEmpleados = ll_newLinkedList();

	do
	{
		if(utn_getNumero("\n\nMenu de opciones"
    					 "\n1. Agregar cliente"
    					 "\n2. Vender afiches."
    					 "\n3. Modificar venta."
    					 "\n4. Cobrar venta."
    					 "\n5. Generar informe de cobros."
    					 "\n6. Generar informe de deudas."
    					 "\n7. Generar estadisticas."
    					 "\n8. Salir\n","Error,opcion invalida\n",&opcion, 20, 1, 8)== 0)
		{
			switch(opcion)
			{
			case 1:
					break;
			}
		}

	}while(opcion != 8);
}
