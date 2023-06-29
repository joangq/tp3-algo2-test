#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <vector>

#include "heap.h"
#include "../puesto.h"
#include "../tipos.h"

/** TupPuesto - Nodo de MinHeap
 * Sirve para almacenar los puestos, ordenados por ID.
 * */
struct TupPuesto {
    Nat id;
    Puesto* puesto;

    TupPuesto();
    TupPuesto(Nat id, Puesto* puesto);
};

/** MinHeap
 * Descripción: Se guardan referencias a Puestos y se los ordena por ID.
 * El tamaño máximo es la cantidad de puestos totales.
 * */
class minHeap {
   public:
    /**Constructor sin argumentos necesario para poder instanciar.
     * Complejidad: O(1)
     * */
    explicit minHeap();

    /** Vacio
     * Complejidad: O(n)
     */
    explicit minHeap(Nat n);

    /** Agregar
     * Complejidad: O(log n)
     * */
    void agregar(TupPuesto tup);

    /** Mínimo
     * Complejidad: O(1)
     * */
    Puesto* minimo() const;

    /** RemoverMínimo
     * Complejidad: O(log n)
     * */
    void removerMinimo();

   private:
    vector<TupPuesto> nodos;
    int tamActual;

    /** HacerMinHeap (privado)
     * Descripción: Convierte al subtree con raíz en la i-ésima posición en un minHeap válido.
     * Complejidad: O(log n)
     * */
    void hacerMinHeap(Nat i);

    /** Swap (privado)
     * Intercambia dos índices de lugar.
     * */
    void swap(Nat i, Nat j);
};

#endif  // MIN_HEAP_H