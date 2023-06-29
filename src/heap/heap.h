#ifndef HEAP_H
#define HEAP_H

#include "max_heap.h"
#include "min_heap.h"

namespace heap {
    /** Nodo Izquierdo
     * Precondición: n debe ser un índice válido
     * Descripción: Dado un índice válido de un heap, calcula
     * el índice que corresponde a su hijo izquierdo. */
    const Nat Izq(Nat n);

    /** Nodo Derecho
     * Precondición: n debe ser un índice válido
     * Descripción: Dado un índice válido de un heap, calcula
     * el índice que corresponde a su hijo derecho. */
    const Nat Der(Nat n);

    /** Nodo Padre
     * Precondición: n debe ser un índice válido
     * Descripción: Dado un índice válido de un heap, calcula
     * el índice que corresponde a su padre. */
    const Nat Padre(Nat n);

    /** Potencia más cercana de dos
     * Precondición: Nada
     * Descripción: Dado un número, devuelve la potencia de dos
     * más cercana. */
    const Nat potenciaDeDos(Nat n);
}

#endif //HEAP_H
