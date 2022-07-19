#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

int comparador(void *elemento_1, void *elemento_2)
{
    int *e_1 = elemento_1;
    int *e_2 = elemento_2;
    return (int)(*e_1 - *e_2);
}

bool imprimir_numeros (void *elemento_1, void *elemento_2)
{   
    int *e_1 = elemento_1;
    int *e_2 = elemento_2;
    printf("%i ",*e_1);
    return (*e_1 != *e_2);
}
void no_puedo_crear_arbol_con_comparador_null()
{
    pa2m_afirmar(abb_crear(NULL) == NULL, "No puedo crear arbol con comparador NULL");

}

void arbol_creado_estructuras_inicializadas()
{   
    abb_t *nuevo_arbol = abb_crear(comparador);
    pa2m_afirmar(nuevo_arbol != NULL, "Se pudo reservar memoria para el nuevo arbol");
    pa2m_afirmar(abb_tamanio(nuevo_arbol) == 0, "La cantidad de elementos es cero al crear el arbol");
    pa2m_afirmar(nuevo_arbol->nodo_raiz == NULL, "El nodo raiz es NULL");
    abb_destruir(nuevo_arbol);

}

void no_puedo_insertar_elemento_arbol_null()
{   
    int numero = 10;
    pa2m_afirmar(abb_insertar(NULL, &numero) == NULL, "No puedo insertar elemento en arbol NULL");
}

void no_puedo_insertar_elemento_null()
{   
    abb_t *arbol = abb_crear(comparador);
    abb_t *nuevo_arbol = abb_insertar(arbol, NULL);
    pa2m_afirmar(nuevo_arbol == NULL, "No puedo insertar NULL");
    abb_destruir(nuevo_arbol);
    abb_destruir(arbol);
}

void puedo_insertar_elemento_en_arbol()
{   
    int numero_10 = 10;
    int numero_20 = 20;
    int numero_5 = 5;
    int numero_30 = 30;
    int numero_1 = 1;
    abb_t *nuevo_arbol = abb_crear(comparador);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
    pa2m_afirmar(nuevo_arbol->tamanio == 1, "Se pudo insertar elemento en arbol vacio");
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
    pa2m_afirmar(nuevo_arbol->tamanio == 2, "Se pudo insertar elemento en arbol no vacio");
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_5);
    pa2m_afirmar(nuevo_arbol->tamanio == 3, "Se pudo insertar elemento en arbol no vacio");
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_30);
    pa2m_afirmar(nuevo_arbol->tamanio == 4, "Se pudo insertar elemento en arbol no vacio");
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_1);
    pa2m_afirmar(abb_tamanio(nuevo_arbol) == 5, "Se pudo insertar elemento en arbol no vacio");
    abb_destruir(nuevo_arbol);
}

void no_puedo_eliminar_elemento_que_no_existe()
{

    int numero_10 = 10;
    int numero_20 = 20;
    abb_t *nuevo_arbol = abb_crear(comparador);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
    pa2m_afirmar(abb_quitar(nuevo_arbol, &numero_20) == NULL, "No puedo eliminar elemento que no existe en el arbol");
    abb_destruir(nuevo_arbol);
}

void puedo_eliminar_elemento_del_arbol()
{
    int numero_10 = 10;
    int numero_20 = 20;
    abb_t *nuevo_arbol = abb_crear(comparador);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
    pa2m_afirmar(abb_quitar(nuevo_arbol, &numero_20) == &numero_20, "Quita un primer elemento y lo devuelve");
    pa2m_afirmar(abb_quitar(nuevo_arbol, &numero_10) == &numero_10, "Quita un segundo elemento y lo devuelve");
    pa2m_afirmar(abb_tamanio(nuevo_arbol) == 0, "Tamanio del arbol disminuye en uno");
    abb_destruir(nuevo_arbol);

}


void no_puedo_buscar_elemento_null()
{
    int numero_10 = 10;
    int numero_20 = 20;
    abb_t *nuevo_arbol = abb_crear(comparador);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
    pa2m_afirmar(abb_buscar(nuevo_arbol, NULL) == NULL, "No puedo buscar elemento NULL");
    abb_destruir(nuevo_arbol);
}

void puedo_encontrar_elemento()
{
    int numero_10 = 10;
    int numero_20 = 20;
    abb_t *nuevo_arbol = abb_crear(comparador);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
    pa2m_afirmar(abb_buscar(nuevo_arbol, &numero_20) == &numero_20, "Encontro el primer elemento buscado");
    pa2m_afirmar(abb_buscar(nuevo_arbol, &numero_10) == &numero_10, "Encontro el segundo elemento buscado");
    abb_destruir(nuevo_arbol);

}

void itero_hasta_encontrar_numero_in_orden()
{
    int numero_10 = 10;
    int numero_20 = 20;
    int numero_5 = 5;
    int numero_3 = 3;
    int numero_7 = 7;
    int numero_15 = 15;
    int numero_25 = 25;
    abb_t *nuevo_arbol = abb_crear(comparador);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_5);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_3);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_7);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_15);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_25);
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN, imprimir_numeros, &numero_25) == 7, "Itero 7 veces hasta encontrar el 25");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN, imprimir_numeros, &numero_10) == 4, "Itero 4 veces hasta encontrar el 10");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN, imprimir_numeros, &numero_15) == 5, "Itero 5 veces hasta encontrar el 15");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN, imprimir_numeros, &numero_20) == 6, "Itero 6 veces hasta encontrar el 20");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN, imprimir_numeros, &numero_5) == 2, "Itero 2 veces hasta encontrar el 5");
    abb_destruir(nuevo_arbol);
}
void itero_hasta_encontrar_numero_pre_orden()
{
    int numero_10 = 10;
    int numero_20 = 20;
    int numero_5 = 5;
    int numero_3 = 3;
    int numero_7 = 7;
    int numero_15 = 15;
    int numero_25 = 25;
    abb_t *nuevo_arbol = abb_crear(comparador);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_5);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_3);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_7);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_15);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_25);
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, PREORDEN, imprimir_numeros, &numero_25) == 7, "Itero 7 veces hasta encontrar el 25");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, PREORDEN, imprimir_numeros, &numero_10) == 1, "Itero 1 veces hasta encontrar el 10");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, PREORDEN, imprimir_numeros, &numero_15) == 6, "Itero 6 veces hasta encontrar el 15");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, PREORDEN, imprimir_numeros, &numero_20) == 5, "Itero 5 veces hasta encontrar el 20");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, PREORDEN, imprimir_numeros, &numero_5) == 2, "Itero 2 veces hasta encontrar el 5");
    abb_destruir(nuevo_arbol);
}
void itero_hasta_encontrar_numero_post_orden()
{
    int numero_10 = 10;
    int numero_20 = 20;
    int numero_5 = 5;
    int numero_3 = 3;
    int numero_7 = 7;
    int numero_15 = 15;
    int numero_25 = 25;
    abb_t *nuevo_arbol = abb_crear(comparador);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_5);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_3);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_7);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_15);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_25);
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, POSTORDEN, imprimir_numeros, &numero_25) == 5, "Itero 5 veces hasta encontrar el 25");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, POSTORDEN, imprimir_numeros, &numero_10) == 7, "Itero 7 veces hasta encontrar el 10");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, POSTORDEN, imprimir_numeros, &numero_15) == 4, "Itero 4 veces hasta encontrar el 15");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, POSTORDEN, imprimir_numeros, &numero_20) == 6, "Itero 5 veces hasta encontrar el 20");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, POSTORDEN, imprimir_numeros, &numero_5) == 3, "Itero 2 veces hasta encontrar el 5");
    abb_destruir(nuevo_arbol);
}

void itero_hasta_encontrar_null()
{
    int numero_10 = 10;
    int numero_20 = 20;
    int numero_5 = 5;
    int numero_3 = 3;
    int numero_7 = 7;
    void *null = NULL;
    abb_t *nuevo_arbol = abb_crear(comparador);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_5);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_3);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_7);
    nuevo_arbol = abb_insertar(nuevo_arbol, &null);
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN, imprimir_numeros, &null) == 1, "Itero 1 vez hasta encontrar NULL INORDEN");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, PREORDEN, imprimir_numeros, &null) == 4, "Itero 4 veces hasta encontrar NULL PREORDEN");
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, POSTORDEN, imprimir_numeros, &null) == 1, "Itero 1 vez hasta encontrar NULL POSTORDEN");
    abb_destruir(nuevo_arbol);

}

void no_puedo_iterar_arbol_null()
{ 
    void *null = NULL;
    pa2m_afirmar(abb_con_cada_elemento(NULL, INORDEN, imprimir_numeros, &null) == 0, "No puedo iterar arbol NULL");
}
void no_puedo_iterar_funcion_null()
{   
    abb_t *nuevo_arbol = abb_crear(comparador);
    void *null = NULL;
    nuevo_arbol = abb_insertar(nuevo_arbol, &null);
    pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN, NULL, &null) == 0, "No puedo iterar arbol con funcion NULL");
    abb_destruir(nuevo_arbol);
}
void imprimir_array (void **array, size_t tope)
{   
    size_t i = 0;
    while (i < tope){
        int *e = array[i];
        printf("%i ", *e);
        i++;
    }
}
void guardo_elementos_en_array_in_orden()
{
    int numero_10 = 10;
    int numero_20 = 20;
    int numero_5 = 5;
    int numero_3 = 3;
    int numero_7 = 7;
    int numero_15 = 15;
    int numero_25 = 25;
    abb_t *nuevo_arbol = abb_crear(comparador);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_5);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_3);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_7);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_15);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_25);
    void **array_1 = malloc( 7 * sizeof(void*));
    void **array_2 = malloc( 5 * sizeof(void*));
    void **array_3 = malloc( 10 * sizeof(void*));
    pa2m_afirmar(abb_recorrer(nuevo_arbol, INORDEN, array_1, 7) == 7, "Guardo 7 elementos porque era el tamanio del array");
    printf("Los elementos guardados inorden son: ");
    imprimir_array (array_1, 7);
    printf("\n");
    pa2m_afirmar(abb_recorrer(nuevo_arbol, INORDEN, array_2, 5) == 5, "Guardo 5 elementos porque era el tamanio del array");
    printf("Los elementos guardados inorden son: ");
    imprimir_array (array_2, 5);
    printf("\n");
    pa2m_afirmar(abb_recorrer(nuevo_arbol, INORDEN, array_3, 10) == 7, "Guardo 7 elementos porque son todos los elementos del arbol y el tamanio del array es mayor");
    printf("Los elementos guardados inorden son: ");
    imprimir_array (array_3, 7);
    printf("\n");
    free(array_1);
    free(array_2);
    free(array_3);
    abb_destruir(nuevo_arbol);
}

void guardo_elementos_en_array_pre_orden()
{
    int numero_10 = 10;
    int numero_20 = 20;
    int numero_5 = 5;
    int numero_3 = 3;
    int numero_7 = 7;
    int numero_15 = 15;
    int numero_25 = 25;
    abb_t *nuevo_arbol = abb_crear(comparador);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_5);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_3);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_7);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_15);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_25);
    void **array_1 = malloc( 7 * sizeof(void*));
    void **array_2 = malloc( 5 * sizeof(void*));
    void **array_3 = malloc( 10 * sizeof(void*));
    pa2m_afirmar(abb_recorrer(nuevo_arbol, PREORDEN, array_1, 7) == 7, "Guardo 7 elementos porque era el tamanio del array");
    printf("Los elementos guardados preorden son: ");
    imprimir_array (array_1, 7);
    printf("\n");
    pa2m_afirmar(abb_recorrer(nuevo_arbol, PREORDEN, array_2, 5) == 5, "Guardo 5 elementos porque era el tamanio del array");
    printf("Los elementos guardados preorden son: ");
    imprimir_array (array_2, 5);
    printf("\n");
    pa2m_afirmar(abb_recorrer(nuevo_arbol, PREORDEN, array_3, 10) == 7, "Guardo 7 elementos porque son todos los elementos del arbol y el tamanio del array es mayor");
    printf("Los elementos guardados preorden son: ");
    imprimir_array (array_3, 7);
    printf("\n");
    free(array_1);
    free(array_2);
    free(array_3);
    abb_destruir(nuevo_arbol);
}

void guardo_elementos_en_array_post_orden()
{
    int numero_10 = 10;
    int numero_20 = 20;
    int numero_5 = 5;
    int numero_3 = 3;
    int numero_7 = 7;
    int numero_15 = 15;
    int numero_25 = 25;
    abb_t *nuevo_arbol = abb_crear(comparador);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_5);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_3);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_7);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_15);
    nuevo_arbol = abb_insertar(nuevo_arbol, &numero_25);
    void **array_1 = malloc( 7 * sizeof(void*));
    void **array_2 = malloc( 5 * sizeof(void*));
    void **array_3 = malloc( 10 * sizeof(void*));
    pa2m_afirmar(abb_recorrer(nuevo_arbol, POSTORDEN, array_1, 7) == 7, "Guardo 7 elementos porque era el tamanio del array");
    printf("Los elementos guardados postorden son: ");
    imprimir_array (array_1, 7);
    printf("\n");
    pa2m_afirmar(abb_recorrer(nuevo_arbol, POSTORDEN, array_2, 5) == 5, "Guardo 5 elementos porque era el tamanio del array");
    printf("Los elementos guardados postorden son: ");
    imprimir_array (array_2, 5);
    printf("\n");
    pa2m_afirmar(abb_recorrer(nuevo_arbol, POSTORDEN, array_3, 10) == 7, "Guardo 7 elementos porque son todos los elementos del arbol y el tamanio del array es mayor");
    printf("Los elementos guardados postorden son: ");
    imprimir_array (array_3, 7);
    printf("\n");
    free(array_1);
    free(array_2);
    free(array_3);
    abb_destruir(nuevo_arbol);
}

void pruebas_con_array_o_arbol_null()
{

    abb_t *nuevo_arbol = abb_crear(comparador);
    void **array_1 = malloc( 7 * sizeof(void*));
    pa2m_afirmar(abb_recorrer(NULL, POSTORDEN, array_1, 7) == 0, "No puedo recorrer arbol NULL");
    pa2m_afirmar(abb_recorrer(nuevo_arbol, POSTORDEN, NULL, 7) == 0, "No puedo recorrer arbol con array NULL");
    free(array_1);
    abb_destruir(nuevo_arbol);
}

int main()
{
    pa2m_nuevo_grupo("Pruebas de creacion de ABB");
    no_puedo_crear_arbol_con_comparador_null();
    arbol_creado_estructuras_inicializadas();

    pa2m_nuevo_grupo("Pruebas de insercion en el ABB");
    no_puedo_insertar_elemento_arbol_null();
    no_puedo_insertar_elemento_null();
    puedo_insertar_elemento_en_arbol();

    pa2m_nuevo_grupo("Pruebas de eliminacion en el ABB");
    no_puedo_eliminar_elemento_que_no_existe();
    puedo_eliminar_elemento_del_arbol();

    pa2m_nuevo_grupo("Pruebas de buscar en el ABB");
    puedo_encontrar_elemento();
    no_puedo_buscar_elemento_null();

    pa2m_nuevo_grupo("Pruebas del iterador con NULL");
    itero_hasta_encontrar_null();
    no_puedo_iterar_arbol_null();
    no_puedo_iterar_funcion_null();

    pa2m_nuevo_grupo("Pruebas del iterador con recorrido inorden");
    itero_hasta_encontrar_numero_in_orden();

    pa2m_nuevo_grupo("Pruebas del iterador con recorrido preorden");
    itero_hasta_encontrar_numero_pre_orden();

    pa2m_nuevo_grupo("Pruebas del iterador con recorrido postorden");
    itero_hasta_encontrar_numero_post_orden();

    pa2m_nuevo_grupo("Pruebas de guardar elementos en array con recorrido inorden");
    guardo_elementos_en_array_in_orden();

    pa2m_nuevo_grupo("Pruebas de guardar elementos en array con recorrido preorden");
    guardo_elementos_en_array_pre_orden();

    pa2m_nuevo_grupo("Pruebas de guardar elementos en array con recorrido postorden");
    guardo_elementos_en_array_post_orden();

    pa2m_nuevo_grupo("Pruebas de recorridos no adecuados");
    pruebas_con_array_o_arbol_null();

    return pa2m_mostrar_reporte();
}
