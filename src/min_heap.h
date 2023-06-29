#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <vector>

#include "heap_aux.h"
#include "puesto.h"
#include "tipos.h"

struct TupPuesto {
    Nat id;
    Puesto* puesto;

    TupPuesto();
    TupPuesto(Nat id, Puesto* puesto);
};

class minHeap {
   public:
    minHeap();
    minHeap(Nat n);

    void agregar(TupPuesto tup);
    Puesto* minimo() const;
    void removerMinimo();

   private:
    vector<TupPuesto> nodos;
    int tamActual;

    void hacerMinHeap(int i);
    void swap(int i, int j);
};

#endif  // MIN_HEAP_H