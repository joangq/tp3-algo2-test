#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <vector>

#include "heap.h"
#include "../tipos.h"

struct Nodo {
    Nat gasto;
    Id id;

    Nodo();
    Nodo(Nat gasto, Id id);
};

class maxHeap {
   public:
    maxHeap();
    maxHeap(Nat n, Nat maxid);

    void agregar(Nodo elem);
    Id maximo() const;
    void removerMaximo();

    void modificarGasto(Persona persona, Nat nuevoGasto);

   private:
    void hacerMaxHeap(Nat i);
    void siftUp(Nat i);
    void swap(Nat i, Nat j);

    vector<Nodo> nodos;
    vector<Nat> indicesPersona;
    Nat tamActual;
};

#endif // MAX_HEAP_H