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
#include "ventas.h"
#include "controller.h"
#include "utn.h"
#include "informes.h"

int main(void)
{
	setbuf(stdout, NULL);
	int opcion;
	int opcionEstadisticas;
	int flagCargado = 0;

	LinkedList* listaClientes = ll_newLinkedList();
	LinkedList* listaVentas = ll_newLinkedList();

	do
	{

		if((flagCargado == 0  &&
			controller_clienteLoadFromText("clientes.txt", listaClientes) == 0 &&
			controller_ventaLoadFromText("ventas.txt", listaVentas) == 0 )
			 ||
			utn_getNumero("\n\nMenu de opciones"
    					 "\n1. Agregar cliente"
    					 "\n2. Vender afiches."
    					 "\n3. Modificar venta."
    					 "\n4. Cobrar venta."
    					 "\n5. Generar informe de cobros."
    					 "\n6. Generar informe de deudas."
    					 "\n7. Generar estadisticas."
    					 "\n8. Salir\n","Error,opcion invalida\n",&opcion, 5, 1, 8)== 0)
		{
			switch(opcion)
			{
			case 1:
					if(controller_addCliente(listaClientes) == 0 &&
					   controller_clienteSaveAsText("clientes.txt",listaClientes) == 0)
					{
						printf("\nCliente agregado con exito\n");
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
			case 3:
					if(controller_modificarVenta(listaClientes,listaVentas) == 0 &&
					   controller_ventaSaveAsText("ventas.txt",listaVentas) == 0)
					{
						printf("\nModificacion lograda con exito \n");
					}
					break;

			case 4:
					if(controller_cobrarVenta(listaClientes,listaVentas) == 0 &&
					   controller_ventaSaveAsText("ventas.txt",listaVentas) == 0)
					{
						printf("\nVenta cobrada exitosamente\n");
					}
					break;
			case 5:
					if(informe_informeCobros("cobrados.txt",listaClientes,listaVentas) == 0)
					{
						printf("\nInforme realizado extiosamente\n");
					}
					break;
			case 6:
					if(informe_informeDeudas("a_cobrar.txt",listaClientes,listaVentas) == 0)
					{
						printf("\nInforme realizado extiosamente \n");
					}
					break;
			case 7:
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
								if(informe_clinteMayorOMenorAfiches(listaClientes, listaVentas, opcionEstadisticas) == 0)
								{
									printf("\nInforme realizado extiosamente \n");
								}
							 	 break;
						case 2:
								if(informe_clinteMayorOMenorAfiches(listaClientes, listaVentas, opcionEstadisticas) == 0)
								{
									printf("\nInforme realizado extiosamente \n");
								}
							 	 break;
						case 3:
								if(informe_ventaConMayorAfiches(listaClientes, listaVentas) == 0)
								{
								  printf("\nInforme realizado extiosamente \n");
								}
							 	 break;
						}
					}
				}while(opcionEstadisticas != 4);
					break;
			}
			flagCargado = 1;
		}

	}while(opcion != 8);
}
