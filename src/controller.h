/*
 * controller.h
 *
 *  Created on: 2020/11/20
 *      Author: PC
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int controller_clienteLoadFromText(char* path , LinkedList* this);
int controller_clienteSaveAsText(char* path , LinkedList* this);
int controller_clienteSaveAsBinary(char* path , LinkedList* this);
int controller_addCliente(LinkedList* this);
int controller_clienteFindNextId(LinkedList* this);
int controller_printClientes(LinkedList* this);
int controller_venderAfiches(LinkedList* this,LinkedList* this2);
int controller_encontrarIdMaximoCliente (LinkedList* this, int* id);
int controller_asignarIdCliente(LinkedList* this, int* id);
int controller_encontrarIdMaximoVenta (LinkedList* this, int* id);
int controller_asignarIdVenta(LinkedList* this, int* id);
int controller_buscarClientePorId(LinkedList* this, int id);
int controller_ventaSaveAsText(char* path , LinkedList* this);

#endif /* CONTROLLER_H_ */
