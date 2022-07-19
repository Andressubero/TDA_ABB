#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

abb_t *abb_crear(abb_comparador comparador)
{	
	if (!comparador)
		return NULL;
	abb_t *nuevo_arbol = malloc(sizeof(abb_t));
	if (!nuevo_arbol)
		return NULL;
	nuevo_arbol->nodo_raiz = NULL;
	nuevo_arbol->comparador = comparador;
	nuevo_arbol->tamanio = 0;
	return nuevo_arbol;
}

nodo_abb_t * insertar_elemento_comparando (abb_t *arbol, nodo_abb_t *nodo_actual,void *elemento)
{	
	if (!nodo_actual){
		nodo_abb_t *nuevo_nodo = malloc(sizeof(nodo_abb_t));
		if (!nuevo_nodo)
			return NULL;
		nuevo_nodo->elemento = elemento;
		nuevo_nodo->izquierda = NULL;
		nuevo_nodo->derecha = NULL;
		arbol->tamanio++;
		return nuevo_nodo;
	}
	int comparacion = arbol->comparador(elemento, nodo_actual->elemento);
	if (comparacion > 0)
		nodo_actual->derecha = insertar_elemento_comparando(arbol, nodo_actual->derecha, elemento);

	if (comparacion <= 0)
		nodo_actual->izquierda = insertar_elemento_comparando(arbol, nodo_actual->izquierda, elemento);

	return nodo_actual;

}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{	
	if (!arbol)
		return NULL;
	arbol->nodo_raiz = insertar_elemento_comparando(arbol, arbol->nodo_raiz, elemento);
	return arbol;
}

nodo_abb_t *buscar_menor_predecesor (nodo_abb_t *raiz){
	nodo_abb_t *nodo_menor = NULL;
	if (!raiz->derecha->derecha){
		nodo_menor = raiz->derecha;
		raiz->derecha = nodo_menor->izquierda;
		return nodo_menor; 
	}
	return buscar_menor_predecesor (raiz->derecha);
}

nodo_abb_t *reemplazar_con_menor_predecesor (nodo_abb_t *raiz)
{	
	nodo_abb_t *aux = NULL;
	if (!raiz->izquierda->derecha){
		aux = raiz->izquierda;
		aux->derecha = raiz->derecha;
		return aux;
	}
	aux = buscar_menor_predecesor (raiz->izquierda);
	aux->izquierda = raiz->izquierda;
	aux->derecha = raiz->derecha;
	return aux;
}



nodo_abb_t *quitar_elemento_comparando(
abb_t *arbol,
nodo_abb_t *nodo_actual,
void *elemento,
void **elemento_encontrado
)
{
	if (!nodo_actual)
		return NULL;
	int comparacion = arbol->comparador(elemento, nodo_actual->elemento);
	if (comparacion == 0){
		nodo_abb_t *aux = NULL;
		*elemento_encontrado = nodo_actual->elemento;
		if (nodo_actual->izquierda && nodo_actual->derecha){
			aux = reemplazar_con_menor_predecesor (nodo_actual);
			free(nodo_actual);
			arbol->tamanio--;
			return aux;
		}
		if(nodo_actual->izquierda){
			aux = nodo_actual->izquierda;
			free(nodo_actual);
			arbol->tamanio--;
			return aux;
		}
		aux = nodo_actual->derecha;
		free(nodo_actual);
		arbol->tamanio--;
		return aux;
	}
	if (comparacion > 0)
		nodo_actual->derecha = quitar_elemento_comparando(arbol, nodo_actual->derecha, elemento, elemento_encontrado);
	if (comparacion < 0)
		nodo_actual->izquierda = quitar_elemento_comparando(arbol, nodo_actual->izquierda, elemento, elemento_encontrado);

	return nodo_actual;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{	
	if (!arbol || abb_vacio(arbol))
		return NULL;
	void *elemento_encontrado = NULL;
	arbol->nodo_raiz = quitar_elemento_comparando(arbol, arbol->nodo_raiz, elemento, &elemento_encontrado);
	return elemento_encontrado;

}

void *buscar_elemento_comparando(abb_t *arbol, nodo_abb_t *nodo_actual,void *elemento)
{	
	if (!nodo_actual)
		return NULL;
	
	int comparacion = arbol->comparador(elemento, nodo_actual->elemento);
	if (comparacion == 0)
		return nodo_actual->elemento;
	
	if (comparacion > 0)
		return buscar_elemento_comparando(arbol, nodo_actual->derecha, elemento);

	return buscar_elemento_comparando(arbol, nodo_actual->izquierda, elemento);
}

void *abb_buscar(abb_t *arbol, void *elemento)
{	
	if (!arbol)
		return NULL;
	return buscar_elemento_comparando(arbol, arbol->nodo_raiz,elemento);
}

bool abb_vacio(abb_t *arbol)
{	
	if (!arbol || (!arbol->nodo_raiz) || (arbol->tamanio == 0))
		return true;
	return false;
}

size_t abb_tamanio(abb_t *arbol)
{	
	if (!arbol)
		return 0;
	return arbol->tamanio;
}

void destruir_post_orden (nodo_abb_t *nodo_actual, void (*destructor)(void *))
{
if (!nodo_actual)
		return;
	destruir_post_orden (nodo_actual->izquierda, destructor);
	destruir_post_orden (nodo_actual->derecha, destructor);
	if (destructor && nodo_actual->elemento)
		destructor(nodo_actual->elemento);
	free(nodo_actual);
	return;
}

void abb_destruir(abb_t *arbol)
{	
	if (!arbol)
		return;
	destruir_post_orden(arbol->nodo_raiz, NULL);
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol)
		return;
	if (!destructor)
		destruir_post_orden (arbol->nodo_raiz, NULL);
	else
		destruir_post_orden(arbol->nodo_raiz, destructor);
	free(arbol);
}

void con_cada_elemento_in_orden (nodo_abb_t *nodo_actual,bool (*funcion)(void *, void *), void *aux, size_t *i, bool *seguir_recorriendo)
{
	if (!nodo_actual)
		return;

	con_cada_elemento_in_orden (nodo_actual->izquierda,funcion, aux, i, seguir_recorriendo);
	if (*seguir_recorriendo){
		(*i)++;
		bool resultado = funcion(nodo_actual->elemento, aux);
		if (!resultado){
			*seguir_recorriendo = false;
			return;
		}
	con_cada_elemento_in_orden (nodo_actual->derecha,funcion, aux, i, seguir_recorriendo);
	}
}

void con_cada_elemento_pre_orden (nodo_abb_t *nodo_actual,bool (*funcion)(void *, void *), void *aux, size_t *i, bool *seguir_recorriendo)
{
	if (!nodo_actual)
		return;
	(*i)++;
	bool resultado = funcion(nodo_actual->elemento, aux);
	if (!resultado){
		*seguir_recorriendo = false;
		return;
	}
	con_cada_elemento_pre_orden (nodo_actual->izquierda,funcion, aux, i, seguir_recorriendo);
	if (*seguir_recorriendo)	
		con_cada_elemento_pre_orden (nodo_actual->derecha,funcion, aux, i, seguir_recorriendo);
	return;
}

void con_cada_elemento_post_orden (nodo_abb_t *nodo_actual,bool (*funcion)(void *, void *), void *aux, size_t *i, bool *seguir_recorriendo)
{
	if (!nodo_actual)
		return;
	if (*seguir_recorriendo == false)
		return;
	con_cada_elemento_post_orden (nodo_actual->izquierda,funcion, aux, i, seguir_recorriendo);
	if (*seguir_recorriendo == false)
		return;
	con_cada_elemento_post_orden (nodo_actual->derecha,funcion, aux, i, seguir_recorriendo);
	if (*seguir_recorriendo == false)
		return;
	(*i)++;
	if (!funcion(nodo_actual->elemento, aux))
		*seguir_recorriendo = false;

}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!arbol || (recorrido > 2) || !funcion)
		return 0;
	size_t i = 0;
	bool seguir_recorriendo = true;
	if (recorrido == INORDEN)
		con_cada_elemento_in_orden (arbol->nodo_raiz, funcion, aux, &i, &seguir_recorriendo);
	if (recorrido == PREORDEN)
		con_cada_elemento_pre_orden (arbol->nodo_raiz, funcion, aux, &i, &seguir_recorriendo);
	if (recorrido == POSTORDEN)
		con_cada_elemento_post_orden (arbol->nodo_raiz, funcion, aux, &i, &seguir_recorriendo);

	return i;
}

void guardar_elemento_vector(void **array, void *elemento, size_t *i)
{
	array[*i] = elemento;
	(*i)++;
}

void recorrido_in_orden (nodo_abb_t *nodo_actual, void **array,size_t tamanio_array,size_t *i)
{
	if (!nodo_actual)
		return;

	recorrido_in_orden (nodo_actual->izquierda,array, tamanio_array, i);
	if (*i<tamanio_array)
		guardar_elemento_vector(array, nodo_actual->elemento, i);
	
	if (*i<tamanio_array)
		recorrido_in_orden (nodo_actual->derecha,array, tamanio_array, i);
}
void recorrido_pre_orden (nodo_abb_t *nodo_actual, void **array,size_t tamanio_array,size_t *i)
{
	if (!nodo_actual)
		return;
	if (*i<tamanio_array)
		guardar_elemento_vector(array, nodo_actual->elemento, i);
	recorrido_pre_orden (nodo_actual->izquierda,array, tamanio_array, i);
	if (*i<tamanio_array)
		recorrido_pre_orden (nodo_actual->derecha,array, tamanio_array, i);
}

void recorrido_post_orden (nodo_abb_t *nodo_actual, void **array,size_t tamanio_array,size_t *i)
{
	if (!nodo_actual)
		return;
	recorrido_post_orden (nodo_actual->izquierda,array, tamanio_array, i);
	if (*i<tamanio_array)
		recorrido_post_orden (nodo_actual->derecha,array, tamanio_array, i);
	if (*i<tamanio_array)
		guardar_elemento_vector(array, nodo_actual->elemento, i);
}


size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{	
	if (!arbol || !array)
		return 0;
	size_t i = 0;
	if (recorrido == INORDEN)
		recorrido_in_orden (arbol->nodo_raiz, array,tamanio_array, &i);
	if (recorrido == PREORDEN)
		recorrido_pre_orden (arbol->nodo_raiz, array,tamanio_array, &i);
	if (recorrido == POSTORDEN)
		recorrido_post_orden (arbol->nodo_raiz, array,tamanio_array, &i);

	return i;
}
