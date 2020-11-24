#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;

    this = (LinkedList*) malloc (sizeof(LinkedList));
    if(this != NULL)
    {
    	this->size= 0;
    	this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* nodeDevuelto = NULL;
	if(this != NULL && nodeIndex > -1 && nodeIndex < this->size)
	{
		nodeDevuelto = this->pFirstNode;
		for(int i = 0; i < nodeIndex; i++)
		{
			nodeDevuelto = nodeDevuelto->pNextNode;
		}

	}
    return nodeDevuelto;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* pNuevoNodo = NULL;
    Node* pPrevNodo = NULL;

    if(this != NULL && nodeIndex >= 0	&& nodeIndex <= this->size)
    {
    	pNuevoNodo = (Node*) malloc(sizeof(Node));
    	pNuevoNodo->pElement = pElement;
    	//identifico donde lo agrego
    	if(nodeIndex == 0)
    	{
    		//quiero agregar un nodo en la primer posicion
    		pNuevoNodo->pNextNode = this->pFirstNode; //siempre primero esta linea de codigo
    		this->pFirstNode = pNuevoNodo;
    	}
    	else
    	{
    		//en el medio
    		pPrevNodo = getNode(this, nodeIndex-1);
    		pNuevoNodo->pNextNode = pPrevNodo->pNextNode;
    		pPrevNodo->pNextNode = pNuevoNodo;
    	}
    	this->size++;
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	if(addNode(this, ll_len(this), pElement) == 0) //se agrega en la posicion del ll_len
    	{
    		returnAux = 0;
    	}
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxNode = NULL;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	auxNode = getNode(this, index);
    	if(auxNode != NULL)
    	{
    		returnAux = auxNode->pElement;
    	}
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* auxNode = NULL;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	auxNode = getNode(this, index);
    	if(auxNode != NULL)
    	{
    		auxNode->pElement = pElement;
    		returnAux = 0;
    	}
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pNodeABorrar = NULL;
    Node* pPrevNodo = NULL;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	pNodeABorrar = getNode(this, index);
    	if(pNodeABorrar != NULL)
    	{
    		if( index == 0)
    		{
    			this->pFirstNode = pNodeABorrar->pNextNode;
    		}
    		else
    		{
    			 pPrevNodo = getNode(this, index-1);
    			 if(pPrevNodo != NULL)
    			 {
    				 pPrevNodo ->pNextNode = pNodeABorrar->pNextNode;
    			 }
    		}
    		free(pNodeABorrar);
    		this->size--;
    		returnAux = 0;
    	}
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int len = ll_len(this);

    if(this != NULL)
    {
    	if(len > 0)
    	{
    		for(int i = len; i >= 0; i--)
    		{
    			if(ll_remove(this, i) == 0)
    			{
    				returnAux = 0;
    			}
    		}
    	}
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL && ll_clear(this) == 0)
    {
    	this = NULL;
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    void* auxElement;
    int len;
    if(this != NULL)
    {
    	len = ll_len(this);
    	for(int i = 0; i < len; i++)
    	{
    		auxElement = ll_get(this, i);
    		if(auxElement == pElement)
    		{
    			returnAux = i;
    			break;
    		}
    	}
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    int len;

    if(this != NULL)
    {
    	len = ll_len(this);
    	returnAux = 1;
    	if(len > 0)
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement) //llamar a add node
{
    int returnAux = -1;

    if(this != NULL && index >= 0 && index <= ll_len(this))
    {
    	if(addNode(this, index, pElement) == 0)
    	{
    		returnAux = 0;
    	}
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index) //suma get y remove
{
    void* returnAux = NULL;
    Node* auxNode;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	auxNode = getNode(this, index);
    	if(auxNode != NULL)
    	{
    		returnAux = auxNode->pElement;
    		ll_remove(this, index);
    	}
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	returnAux = 0;
    	if(ll_indexOf(this, pElement) >= 0)
    	{
    		returnAux = 1;

    	}
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int len;
    void* auxElement;

    if(this != NULL && this2 != NULL)
    {
    	len = ll_len(this2);
    	returnAux = 1;
    	for(int i = 0; i < len; i++)
    	{
    		auxElement = ll_get(this2, i);
    		if(ll_contains(this, auxElement) != 1)
    		{
    			returnAux = 0;
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* auxElement;

    if(this != NULL && from >= 0 && to >= from && to <= ll_len(this))
    {
    	cloneArray = ll_newLinkedList();
    	if(cloneArray != NULL)
    	{
    		for(int i = from; i <= to; i++)
    		{
    			auxElement = ll_get(this, i);
    			ll_add(cloneArray, auxElement);
    		}
    	}

    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    if(this != NULL)
    {
    	cloneArray= ll_subList(this, 0, this->size);
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int len;
    int flagSwap;
    void* pElementoUno;
    void* pElementoDos;
    void* auxElemento;

    if(this != NULL && pFunc != NULL  &&  (order == 0 || order == 1))
    {
    	len = ll_len(this);
    	do
    	{
    		flagSwap = 0;
    		for(int i = 0; i < len-1; i++)
    		{
    			pElementoUno = ll_get(this, i);
    			pElementoDos = ll_get(this, i+1);
    			if((pFunc(pElementoUno, pElementoDos) < 0 && order == 0) ||
    			   (pFunc(pElementoUno, pElementoDos) > 0 && order == 1))
    			{
    				auxElemento = pElementoUno;
    				ll_set(this, i, pElementoDos);
    				ll_set(this, i+1, auxElemento);
    				flagSwap = -1;
    			}
    			returnAux = 0;
    		}
    	}while(flagSwap == -1);
    }
    return returnAux;

}

/** \brief Recorre los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                         ( 0) Si ok
 */
int ll_map(LinkedList* this, int (*pFunc)(void*))
{
	int returnAux = -1;
	int len;
	void* pElemento;

	if(this != NULL && pFunc != NULL)
	{
		len = ll_len(this);
		for(int i = 0; i < len; i++)
		{
			pElemento = ll_get(this, i);
			pFunc(pElemento);
		}
		returnAux = 0;
	}

	return returnAux;
}

/** \brief Acumula los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param pResultado int* Puntero donde se guardara el resultado de la funcion
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_reduceInt(LinkedList* this, int (*pFunc)(void*), int* pResultado)
{
	int returnAux = -1;
	int len;
	void* pElemento;
	int acumulador = 0;

	if(this != NULL && pFunc != NULL)
	{
		len = ll_len(this);
		for(int i = 0; i < len; i++)
		{
			pElemento = ll_get(this, i);
			acumulador = acumulador + pFunc(pElemento);
		}
		*pResultado = acumulador;
		returnAux = 0;
	}

	return returnAux;
}

/** \brief Acumula los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param pResultado float* Puntero donde se guardara el resultado de la funcion
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */

int ll_reduceFloat(LinkedList* this, float (*pFunc)(void*), float* pResultado)
{
	int returnAux = -1;
	int len;
	void* pElemento;
	float acumulador = 0;

	if(this != NULL && pFunc != NULL)
	{
		len = ll_len(this);
		for(int i = 0; i < len; i++)
		{
			pElemento = ll_get(this, i);
			acumulador = acumulador + pFunc(pElemento);
		}
		*pResultado = acumulador;
		returnAux = 0;
	}

	return returnAux;
}

/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return LinkedList Retorna una nueva lista con los elementos deseados
 */
LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	int len;
	int i = 0;
	void* pElemento;
	LinkedList* newList = NULL;

	if(this != NULL && pFunc != NULL)
	{
		newList = ll_newLinkedList();
		len = ll_len(this);
		while (i < len)
		{
			pElemento = ll_get(this, i);
			if(pFunc(pElemento) == 1 )
			{
				ll_add(newList, pElemento);
			}
			i++;
		}
	}
	return newList;
}
