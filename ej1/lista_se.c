#include <stdbool.h>
#include <stdlib.h>
#include "lista_se.h"

/*Funciones adicionales*/
nodo_t* crear_nodo(void* dato){
	nodo_t* resultado = malloc(sizeof(nodo_t));
	if (!resultado)
		return NULL;
	resultado->elemento = dato;
	resultado->siguiente = NULL;
	return resultado;
}

//Iterador especial interno del TDA
//PRE: recibe el puntero a un nodo valido y se mueve "indice" veces, si indice es -1, itera hasta el ultimo nodo
//post: devuelve un puntero a nodo aun si el indice era muy alto
nodo_t* iterador_interno(nodo_t* inicio, int indice,nodo_t* ultimo){
	if (!inicio)
		return NULL;
	nodo_t* cursor = inicio;
	if (inicio == ultimo){ //La salida si el ultimo es igual al nodo, pasa solo cuando se solicita el nodo primero
		return inicio;
	}
	while ((cursor->siguiente != NULL)){
		if (cursor->siguiente == ultimo)
			break;
		if (indice == 0)
			break;
		indice--;
		cursor = cursor -> siguiente;
	}
	return cursor;
}

/*
 * Devuelve la cantidad de elementos en una lista.
 */
size_t elementos(lista_se_t* lista){
	if (!lista)
		return 0;
	return lista->cantidad;
}

/*
 * Crea la estructura de la lista, inicializando
 * los nodos inicio y actual en NULL y reservando la memoria
 * necesaria para la estructura.
 */
lista_se_t* crear_lista(){
	lista_se_t* lista_temp = malloc(sizeof(lista_se_t));
	if (!lista_temp)
			return NULL;
	lista_temp->inicio = NULL;
	lista_temp->cantidad = 0;
	return lista_temp;
}

/*
 * Inserta un elemento luego al final de la lista, reservando la memoria necesaria para este nodo.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int insertar(lista_se_t* lista, void* elemento){
	if (!elemento)
		return -1;
	if (!lista)
		return -1;
	nodo_t* nodo_temp = crear_nodo(elemento);
	if (!nodo_temp)
		return -1;
	//si es el primero
	if (elementos(lista) == 0){
		lista->inicio = nodo_temp;
		lista->cantidad++;
		return 0;
	}
	//Si no es el primero
	nodo_t* anterior_al_insertar = iterador_interno(lista->inicio, -1, NULL);
	anterior_al_insertar->siguiente = nodo_temp;
	lista->cantidad++;
	return 0;
}
/*
 * Inserta un elemento en la posicion indicada, reservando la memoria necesaria para este nodo.
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int insertar_en_posicion(lista_se_t* lista, void* elemento, int indice){
	if (!elemento)
		return -1;
	if (!lista)
		NULL;
	if (indice < 0)
		return -1;
	//si se inserta al principio y la lista esta vacia
	if ( (indice == 0) && (elementos(lista) == 0) ){
		nodo_t* nodo_temp = crear_nodo(elemento);
		if (!nodo_temp)
			return -1;
		lista->inicio = nodo_temp;
		lista->cantidad++;
	}
	//Caso en que el indice es mayor a la cantidad que hay en la lista
	if (indice >= elementos(lista))
		return insertar(lista,elemento);
	nodo_t* anterior_al_insertar = iterador_interno(lista->inicio,indice,NULL);
	//Caso donde se inserta en el indice 0
	if (anterior_al_insertar == lista->inicio){
		nodo_t* nodo_temp = crear_nodo(elemento);
		if (!nodo_temp)
			return -1;
		nodo_t* p_aux = lista->inicio;
		nodo_temp->siguiente = p_aux;
		lista->inicio = nodo_temp;
		lista->cantidad++;
		return 0;
	}
	//Caso donde el indice es muy alto
	nodo_t* anterior_al_anterior_al_insertar = iterador_interno(lista->inicio, -1, anterior_al_insertar);
	nodo_t* nodo_temp = crear_nodo(elemento);
	if (!nodo_temp)
		return -1;
	nodo_temp->siguiente = anterior_al_insertar;
	anterior_al_anterior_al_insertar->siguiente = nodo_temp;
	lista->cantidad++;
	return 0;
}

/*
 * Borra el elemento que se encuentra en la ultima posición liberando la memoria reservada para el.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int borrar(lista_se_t* lista){
	if (!lista)
		return -1;
	if (!lista->inicio)
		return -1;
	//Si la lista tiene un elemento
	if (elementos(lista) == 1){//Caso que el primero es al que eliminare
			free(lista->inicio);
			lista->inicio = NULL;
			lista->cantidad--;
			return 0;
	}
	//si la lista tiene mas de un elemento
	nodo_t* nodo_a_eliminar = iterador_interno(lista->inicio,-1,NULL);
	if (!nodo_a_eliminar)
		return -1;
	nodo_t* nodo_antetior_al_eliminar = iterador_interno(lista->inicio, -1, nodo_a_eliminar);
	if (nodo_a_eliminar != nodo_antetior_al_eliminar) // si hay un solo elemento?
		nodo_antetior_al_eliminar->siguiente = NULL;
	free(nodo_a_eliminar);
	lista->cantidad--;
	return 0;
}
/*
 * Borra el elemento que se encuentra en la posición indicada, liberando la memoria reservada para el.
 * En caso de no existir esa posición se intentará borrar el último elemento.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int borrar_de_posicion(lista_se_t* lista, int indice){
	if (!lista)
		return -1;
	if (indice < 0)
		return -1;
	if (indice > elementos(lista))
		return -1;
	if (elementos(lista) == 0)
	 	return -1;
	nodo_t* nodo_a_eliminar = iterador_interno(lista->inicio,indice,NULL);
	nodo_t* anterior_al_nodo_a_eliminar = iterador_interno(lista->inicio, -1, nodo_a_eliminar);
	//Caso que es la posicion 0
	if (nodo_a_eliminar == anterior_al_nodo_a_eliminar){ //Caso donde solo hay un elemento
		lista->inicio = nodo_a_eliminar->siguiente;
		free(nodo_a_eliminar);
		lista->cantidad--;
		return 0;
	}
	//otro caso, o caso del medio de lista
	anterior_al_nodo_a_eliminar->siguiente = nodo_a_eliminar->siguiente;
	free(nodo_a_eliminar);
	lista->cantidad--;
	return 0;
}

/*
 * Devuelve el elemento en la posicion indice.
 * Si no existe dicha posicion devuelve NULL.
 */
void* elemento_en_posicion(lista_se_t* lista, int indice){
	if (!lista)
		return NULL;
	if (indice < 0)
		return NULL;
	if (indice > elementos(lista) || indice == elementos(lista))
		return NULL;
	return (iterador_interno(lista->inicio, indice, NULL))->elemento;
}
/*
 * Devuelve el último elemento de la lista.
 * Si no existe dicha posicion devuelve NULL.
 */
void* ultimo(lista_se_t* lista){
	if (!lista)
		return NULL;
	nodo_t* resultado = iterador_interno(lista->inicio,-1,NULL);
	if (resultado != NULL) //si la funcion anterior me da un NULL por que no hay un primero
		return resultado->elemento;
	else
		return NULL;
}
/*
 * Devuelve true si la lista está vacía o true si no lo está.
 *Devuelve False si la lista es no valida
 */
bool vacia(lista_se_t* lista){
	if (!lista)
		return true;
	return (lista->cantidad == 0);
}

/*
 * Libera la memoria reservada por los nodos presentes en la lista y luego la memoria reservada por la estructura.
 * Devuelve 0 si pudo destruirla o -1 si no pudo.
 */
int destruir_lista(lista_se_t* lista){
	//borrar desde el fondo hasta el principio y borrar el nodo lista
	if (!lista)
		return -1;
	//Si la lista tiene cantidad 0 solo eliminar la lista
	if (elementos(lista) == 0){
		free(lista);
		return 0;
	}
	// abarca los casos de uno y mAs elementos
	while (borrar(lista) == 0){
		true;
	}
	free(lista);
	return 0;
}
