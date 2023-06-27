#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <vector>

#include "heap_aux.h"
#include "tipos.h"

struct Nodo {
    Nat gasto;
    Id id;

    Nodo(Nat gasto, Id id) {
        this->gasto = gasto;
        this->id = id;
    }
};

class MaxHeap {
   public:
    MaxHeap(int n, int maxid);

    void agregar(Nodo elem);
    Id maximo() const;
    void removerMaximo();

    void modificarGasto(Persona persona, Nat nuevoGasto);

   private:
    void hacerMaxHeap(int i);
    void swap(int i, int j);

    vector<Nodo> nodos;
    vector<Nat> indicesPersona;
    Nat tamActual;
};

#endif MAX_HEAP_H