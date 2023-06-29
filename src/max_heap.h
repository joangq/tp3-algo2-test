#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <vector>

#include "heap_aux.h"
#include "tipos.h"

struct Nodo {
    Nat gasto;
    Id id;

    Nodo();
    Nodo(Nat gasto, Id id);
};

class maxHeap {
   public:
    maxHeap();
    maxHeap(int n, int maxid);

    void agregar(Nodo elem);
    Id maximo() const;
    void removerMaximo();

    void modificarGasto(Persona persona, Nat nuevoGasto);

   private:
    void hacerMaxHeap(int i);
    void siftUp(int i);
    void swap(int i, int j);

    vector<Nodo> nodos;
    vector<Nat> indicesPersona;
    Nat tamActual;
};

#endif // MAX_HEAP_H