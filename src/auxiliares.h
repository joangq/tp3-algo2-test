#ifndef AUXILIARES
#define AUXILIARES
#include "tipos.h"
#include <vector>

/** Búsqueda Binaria
 * Descripción: Sobre un vector de naturales, busca el índice al
 * elemento más cercano. (O devuelve el indice al elemento buscado) */
Nat busquedaBinaria(const vector<Nat>& A, Nat x, Nat low, Nat high);

/** Merge
 * Precondición: A y B ordenados
 * Descripción: Mergea dos vectores ordenados y devuelve el resultado.
 * Lo hace in-place sobre el nuevo vector. (Nunca cambia el tamaño)
 * */
vector<Nat> merge(const vector<Nat>& A, const vector<Nat>& B);

/** Merge Sort
 * Descripción: Ordena un vector de naturales. Devuelve el vector ordenado
 * y no modifica el que se pasa como parámetro.
 * */
vector<Nat> mergeSort(const vector<Nat>& A);

#endif //AUXILIARES