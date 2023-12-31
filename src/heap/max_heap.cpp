#include "max_heap.h"
#include "heap.h"

Nodo::Nodo() : gasto(0), id(0) {}

Nodo::Nodo(Nat gasto, Persona id) : gasto(gasto), id(id) {}

maxHeap::maxHeap() : tamActual(0) {}

maxHeap::maxHeap(Nat n, Nat maxid) : tamActual(0) {
    Nat size = heap::potenciaDeDos(n);

    for (int i = 0; i < size; i++)
        nodos.emplace_back(0, 1);

    for (int i = 0; i < maxid + 1; i++)
        indicesPersona.push_back(0);
}

void maxHeap::agregar(Nodo elem) {
    /* Creo una copia y le sumo 1 al id para poder representar a personas
       con id = 0. Ver TP2 para una aclaración más precisa. */
    Nodo copia_elem = elem;
    copia_elem.id += 1;

    Nat i = tamActual;
    nodos[i] = copia_elem;
    indicesPersona[elem.id] = i;

    tamActual++;

    siftUp(i);
}

Persona maxHeap::maximo() const {
    // Le sumo 1 porque antes le había restado 1.
    return nodos[0].id - 1;
}

void maxHeap::removerMaximo() {
    nodos[tamActual] = Nodo(0, 0);
    tamActual--;
    nodos[0] = nodos[tamActual];
    hacerMaxHeap(0);
}


void maxHeap::modificarGasto(Persona persona, Nat nuevoGasto) {
    Nat i = indicesPersona[persona];
    Dinero gasto = nodos[i].gasto;
    nodos[i].gasto = nuevoGasto;

    if (nuevoGasto < gasto)
        hacerMaxHeap(i);
    else if (nuevoGasto > gasto)
        siftUp(i);

}

void maxHeap::hacerMaxHeap(Nat i) {
    Nat izq = heap::Izq(i);
    Nat der = heap::Der(i);
    Nat mayor = i;

    Nodo nMayor  = nodos[mayor];

    /*
    Estrategia de comparación:
        Quiero hacer sift down. Sé que el nodo actual fue actualizado con un valor menor.
        Primero, ordeno por gastos. Entonces, me fijo si alguno de los dos hijos tiene un gasto mayor
        (o igual) al nodo actual.
        
        Si vale nIzq (o nDer) >= nMayor.gasto, me fijo si los gastos son iguales, pues para ese caso hay una
        condición especial.

        Si los gastos son iguales, hago sift down únicamente si el id del nodo actual es mayor al del hijo.
        Si no son iguales, como vale mayor o igual, entonces va a ser mayor, por lo que directamente intercambio.
    */

    if (izq < tamActual) {
        Nodo nIzq = nodos[izq];
        if (nIzq.gasto >= nMayor.gasto) {
            if (nIzq.gasto == nMayor.gasto) {
                if (nMayor.id > nIzq.id)
                    mayor = izq;
            } else {
                mayor = izq;
            }
        }
    }

    if (der < tamActual) {
        Nodo nDer = nodos[der];
        if (nDer.gasto >= nMayor.gasto) {
            if (nDer.gasto == nMayor.gasto) {
                if (nMayor.id > nDer.id)
                    mayor = der;
            } else {
                mayor = der;
            }
        }
    }

    if (mayor != i) {
        swap(i, mayor);
        hacerMaxHeap(mayor);
    }
}

void maxHeap::swap(Nat i, Nat j) {
    // Primero, swappeo los indices en el diccionario de índices.
    // Les resto 1 porque las ids guardadas en nodos son 1 más que las reales.
    Nat tempIndice = indicesPersona[nodos[i].id - 1];
    indicesPersona[nodos[i].id - 1] = indicesPersona[nodos[j].id - 1];
    indicesPersona[nodos[j].id - 1] = tempIndice;

    Nodo temp = nodos[i];
    nodos[i] = nodos[j];
    nodos[j] = temp;
}

void maxHeap::siftUp(Nat i) {
    // Sift up.
    while (i != 0 && nodos[i].gasto > nodos[heap::Padre(i)].gasto) {
        Nat j = heap::Padre(i);
        swap(i, j);
        i = j;
    }

    Nat j = heap::Padre(i);

    // Sift up.
    while (i != 0 && nodos[i].gasto == nodos[j].gasto && nodos[i].id < nodos[j].id) {
        j = heap::Padre(i);
        swap(i, j);
        i = j;
    }
}