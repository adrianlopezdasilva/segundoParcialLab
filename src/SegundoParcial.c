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
#include "clientes.h"
#include "controller.h"
#include "utn.h"

int main(void)
{
	setbuf(stdout, NULL);
	int opcion;

	LinkedList* listaClientes = ll_newLinkedList();
	LinkedList* listaVentas = ll_newLinkedList();

	do
	{
		if(controller_clienteLoadFromText("clientes.txt", listaClientes) ==  0 &&
			utn_getNumero("\n\nMenu de opciones"
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
			case 1: // NECESITO VERIFICAR MEJOR EL CUIT, EVITAR QUE SE GUARDE 2 VECES LA LISTA
					if(controller_addCliente(listaClientes) == 0 &&
					   controller_clienteSaveAsText("clientes.txt",listaClientes) == 0)
					{
						printf("\nCliente agregado con exito\n");
					}
					else
					{
						printf("\nSurgio un error");
					}
					break;
			case 2:
					if( controller_venderAfiches(listaClientes,listaVentas) == 0 &&
						controller_ventaSaveAsText("ventas.txt",listaVentas) == 0)
					{
						printf("\nVenta agregada con exito\n");
					}
					else
					{
						printf("\nSurgio un error");
					}
					break;
			}
		}

	}while(opcion != 8);
}
