#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <vector>

#include "heap.h"
#include "../tipos.h"

/** Nodo de MaxHeap
 * Sirve para almacenar los gastos de cada persona (por ID).
 * */
struct Nodo {
    Nat gasto;
    Persona id;

    Nodo();
    Nodo(Nat gasto, Persona id);
};

/** MaxHeap
 * Descripción: Se guardan nodos con los valores de los gastos y los IDs de cada persona.
 * El tamaño máximo es la cantidad de personas totales.
 * */
class maxHeap {
   public:
    /**Constructor sin argumentos necesario para poder instanciar.
     * Complejidad: O(1)
     * */
    explicit maxHeap();

    /** Vacio
     * Complejidad: O(n)
     */
    explicit maxHeap(Nat n, Nat maxid);

    /** Agregar
     * Complejidad: O(log n)
     * */
    void agregar(Nodo elem);

    /** Maximo
     * Complejidad: O(1)
     * */
    Persona maximo() const;

    /** RemoverMáximo
     * Complejidad: O(log n)
     * */
    void removerMaximo();

    /** ModificarGasto
     * Complejidad: O(log n)
     * */
    void modificarGasto(Persona persona, Nat nuevoGasto);

   private:
    /** HacerMaxHeap (privado)
     * Descripción: Convierte al subtree con raíz en la i-ésima posición en un maxHeap válido.
     * Complejidad: O(log n)
     * */
    void hacerMaxHeap(Nat i);

    /** SiftUp (privado)
     * Dado un índice, swappea los índices necesarios en el arreglo de representación para siftear.
     * */
    void siftUp(Nat i);

    /** Swap (privado)
     * Intercambia dos índices de lugar.
     * */
    void swap(Nat i, Nat j);

    vector<Nodo> nodos;
    vector<Nat> indicesPersona;
    Nat tamActual;
};

#endif // MAX_HEAP_H