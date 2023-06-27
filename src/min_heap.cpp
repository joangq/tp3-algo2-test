#include "min_heap.h"

TupPuesto::TupPuesto(Nat id, Puesto* puesto) {
        this->id = id;
        this->puesto = puesto;
}

MinHeap::MinHeap(int n) {
    this->nodos.reserve(n);
    this->tamActual = 0;
}

void MinHeap::agregar(TupPuesto tup) {
    int i = tamActual;
    nodos[i] = tup;
    tamActual++;

    // Sift up.
    while (i != 0 and nodos[i].id < nodos[Padre(i)].id) {
        int j = Padre(i);
        swap(i, j);
        i = j;
    }
}

Puesto* MinHeap::minimo() const {
    return nodos[0].puesto;
}

void MinHeap::removerMinimo() {
    tamActual--;
    nodos[0] = nodos[tamActual];
    hacerMinHeap(0);
}

void MinHeap::hacerMinHeap(int i) {
    int izq = Izq(i);
    int der = Der(i);
    int menor = i;

    if (izq < tamActual and nodos[izq].id < nodos[menor].id) {
        menor = izq;
    }

    if (der < tamActual and nodos[der].id < nodos[menor].id) {
        menor = der;
    }

    if (menor != i) {
        swap(i, menor);
        hacerMinHeap(menor);
    }
}

void MinHeap::swap(int i, int j) {
    TupPuesto temp = nodos[i];
    nodos[i] = nodos[j];
    nodos[j] = temp;
}