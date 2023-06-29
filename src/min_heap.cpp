#include "min_heap.h"

TupPuesto::TupPuesto(Nat id, Puesto* puesto) {
    this->id = id;
    this->puesto = puesto;
}

TupPuesto::TupPuesto() {
    id = 0;
    puesto = nullptr;
}

minHeap::minHeap() {
    tamActual = 0;
}

minHeap::minHeap(int n) {
    unsigned int v = n;

    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;

    for (int i = 0; i < v; i++)
        nodos.push_back(TupPuesto(0, nullptr));

    tamActual = 0;
}

void minHeap::agregar(TupPuesto tup) {
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

Puesto* minHeap::minimo() const {
    if (tamActual == 0)
        return nullptr;

    return nodos[0].puesto;
}

void minHeap::removerMinimo() {
    tamActual--;
    nodos[0] = nodos[tamActual];
    hacerMinHeap(0);
}

void minHeap::hacerMinHeap(int i) {
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

void minHeap::swap(int i, int j) {
    TupPuesto temp = nodos[i];
    nodos[i] = nodos[j];
    nodos[j] = temp;
}