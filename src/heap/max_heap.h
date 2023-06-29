#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <vector>

#include "heap.h"
#include "../tipos.h"

struct Nodo {
    Nat gasto;
    Persona id;

    Nodo();
    Nodo(Nat gasto, Persona id);
};

class maxHeap {
   public:
    maxHeap();
    maxHeap(Nat n, Nat maxid);

    void agregar(Nodo elem);
    Persona maximo() const;
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