/*
 * informes.h
 *
 *  Created on: 2020/11/22
 *      Author: PC
 */

#ifndef INFORMES_H_
#define INFORMES_H_

int informe_informeCobros(char* path,LinkedList* this1, LinkedList* this2);
int informe_contadorVentasCobradas(LinkedList* this,int idCliente);
int informe_informeDeudas(char* path,LinkedList* this1, LinkedList* this2);
int informe_contadorVentasAdeudadas(LinkedList* this,int idCliente);
int informe_ventaConMayorAfiches(LinkedList* this1, LinkedList* this2);
int informe_clinteMayorOMenorAfiches(LinkedList* this1, LinkedList* this2,int criterio);
#endif /* INFORMES_H_ */
