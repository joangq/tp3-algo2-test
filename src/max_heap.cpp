#include "max_heap.h"
#include "heap_aux.h"

maxHeap::maxHeap() { }

maxHeap::maxHeap(int n, int maxid) : indicesPersona(maxid + 1) {
    this->nodos.reserve(n);
    tamActual = 0;
}


void maxHeap::agregar(Nodo elem) { 
    // Creo una copia y le sumo 1 al id para poder representar a personas
    // con id = 0. Ver TP2 para una aclaración más precisa.
    Nodo copia_elem = elem;
    copia_elem.id += 1;

    int i = tamActual;
    nodos[i] = copia_elem;
    indicesPersona[elem.id] = i;

    tamActual++;

    siftUp(i); 
}

Id maxHeap::maximo() const { 
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
    int i = indicesPersona[persona];
    Dinero gasto = nodos[i].gasto;
    nodos[i].gasto = nuevoGasto;

    if (nuevoGasto < gasto) {
        hacerMaxHeap(i);
    } else if (nuevoGasto > gasto) {
        siftUp(i);
    }
}

void maxHeap::hacerMaxHeap(int i) { 
    int izq = Izq(i);
    int der = Der(i);
    int mayor = i;

    Nodo nIzq = nodos[izq];
    Nodo nDer = nodos[der];
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

    if (izq < tamActual && nIzq.gasto >= nMayor.gasto) {
        if (nIzq.gasto == nMayor.gasto) {
            if (nMayor.id > nIzq.id)
                mayor = izq;
        } else {
            mayor = izq;
        }
        
    }

    if (der < tamActual && nDer.gasto >= nMayor.gasto) {
        if (nDer.gasto == nMayor.gasto) {
            if (nMayor.id > nDer.id)
                mayor = der;
        } else {
            mayor = der;
        }
    }

    if (mayor != i) {
        swap(i, mayor);
        hacerMaxHeap(mayor);
    }
}

void maxHeap::swap(int i, int j) { 
    // Primero, swappeo los indices en el diccionario de índices.
    // Les resto 1 porque las ids guardadas en nodos son 1 más que las reales.
    int tempIndice = indicesPersona[nodos[i].id - 1];
    indicesPersona[nodos[i].id - 1] = indicesPersona[nodos[j].id - 1];
    indicesPersona[nodos[j].id - 1] = tempIndice;

    Nodo temp = nodos[i];
    nodos[i] = nodos[j];
    nodos[j] = temp;
}

void maxHeap::siftUp(int i) {
    // Sift up.
    while (i != 0 && nodos[i].gasto > nodos[Padre(i)].gasto) {
        int j = Padre(i);
        swap(i, j);
        i = j;
    }

    int j = Padre(i);

    // Sift up.
    while (i != 0 && nodos[i].gasto == nodos[j].gasto && nodos[i].id < nodos[j].id) {
        int j = Padre(i);
        swap(i, j);
        i = j;
    }   
}