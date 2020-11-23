/*
 * parser.h
 *
 *  Created on: 2020/11/20
 *      Author: PC
 */

#ifndef PARSER_H_
#define PARSER_H_

int parser_clienteFromText(FILE* pFile , LinkedList* this);
int parser_clienteFromBinary(FILE* pFile , LinkedList* this);
int parser_ventaFromText(FILE* pFile , LinkedList* this);

#endif /* PARSER_H_ */
