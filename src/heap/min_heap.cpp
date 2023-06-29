#include "min_heap.h"

TupPuesto::TupPuesto(Nat id, Puesto* puesto): id(id), puesto(puesto) {}

TupPuesto::TupPuesto(): id(0), puesto(nullptr) {}

minHeap::minHeap(): tamActual(0) {}

minHeap::minHeap(Nat n) : tamActual(0) {
    Nat size = heap::potenciaDeDos(n);

    for (int i = 0; i < size; i++)
        nodos.emplace_back(0, nullptr);
}

void minHeap::agregar(TupPuesto tup) {
    Nat i = tamActual;
    nodos[i] = tup;
    tamActual++;

    // Sift up.
    while (i != 0 and nodos[i].id < nodos[heap::Padre(i)].id) {
        Nat j = heap::Padre(i);
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

void minHeap::hacerMinHeap(Nat i) {
    Nat izq = heap::Izq(i);
    Nat menor = i;
    Nat der = heap::Der(i);

    if (izq < tamActual and nodos[izq].id < nodos[menor].id)
        menor = izq;

    if (der < tamActual and nodos[der].id < nodos[menor].id)
        menor = der;

    if (menor != i) {
        swap(i, menor);
        hacerMinHeap(menor);
    }
}

void minHeap::swap(Nat i, Nat j) {
    TupPuesto temp = nodos[i];
    nodos[i] = nodos[j];
    nodos[j] = temp;
}