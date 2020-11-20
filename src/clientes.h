/*
 * clientes.h
 *
 *  Created on: 2020/11/20
 *      Author: PC
 */

#ifndef CLIENTES_H_
#define CLIENTES_H_
#define SIZECLIENTE 30
typedef struct
{
	int idCliente;
	char nombre[SIZECLIENTE];
	char apellido[SIZECLIENTE];
	int cuit;
}Cliente;

Cliente* cliente_new();
Cliente* cliente_newParametros(char* idStr,char* nombreStr,char* apellidoStr,char* cuitStr);
void cliente_delete(Cliente* this);

int cliente_setId(Cliente* this,int id);
int cliente_getId(Cliente* this,int* id);

int cliente_setNombre(Cliente* this,char* nombre);
int cliente_getNombre(Cliente* this,char* nombre);

int cliente_setApellido(Cliente* this,char* apellido);
int cliente_getApellido(Cliente* this,char* apellido);

int cliente_setCuit(Cliente* this,int cuit);
int cliente_getCuit(Cliente* this,int* cuit);

int cliente_compareByName(void* thisOne , void* thisTwo);
int cliente_compareByHoursWorked(void* thisOne , void* thisTwo);
int cliente_compareBySalary(void* thisOne , void* thisTwo);

#endif /* CLIENTES_H_ */
