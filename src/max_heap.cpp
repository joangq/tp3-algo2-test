#include "max_heap.h"
#include "heap_aux.h"


MaxHeap::MaxHeap(int n, int maxid) : indicesPersona(maxid + 1) {
    this->nodos.reserve(n);
    tamActual = 0;
}


void MaxHeap::agregar(Nodo elem) { 
    // Creo una copia y le sumo 1 al id para poder representar a personas
    // con id = 0. Ver TP2 para una aclaración más precisa.
    Nodo copia_elem = elem;
    copia_elem.id += 1;

    int i = tamActual;
    nodos[i] = copia_elem;
    indicesPersona[elem.id] = i;

    tamActual++;

    // Sift up.
    while (i != 0 and nodos[i].gasto > nodos[Padre(i)].gasto) {
        int j = Padre(i);
        swap(i, j);
        i = j;
    }

    int j = Padre(i);

    // Sift up.
    while (i != 0 and nodos[i].gasto == nodos[j].gasto and nodos[i].id > nodos[j].id) {
        int j = Padre(i);
        swap(i, j);
        i = j;
    }    
}

Id MaxHeap::maximo() const { 
    // Le sumo 1 porque antes le había restado 1.
    return nodos[0].id + 1;
}

void MaxHeap::removerMaximo() { 
    nodos[tamActual] = Nodo(0, 0);
    tamActual--;
    nodos[0] = nodos[tamActual];
    hacerMaxHeap(0);
}


void MaxHeap::modificarGasto(Persona persona, Nat nuevoGasto) { 
    int i = indicesPersona[persona];
    Dinero gasto = nodos[i].gasto;


    if (gasto < nuevoGasto) {
        nodos[i].gasto = nuevoGasto;
        hacerMaxHeap(i);
    } else if (gasto > nuevoGasto) {
        while (i != 0 and nodos[i].gasto > nodos[Padre(i)].gasto) {
            int j = Padre(i);
            swap(i, j);
            i = j;
        }
    }
}

void MaxHeap::hacerMaxHeap(int i) { 
    int izq = Izq(i);
    int der = Der(i);
    int mayor = i;

    if (izq < tamActual and nodos[izq].id > nodos[mayor].id) {
        mayor = izq;
    }

    if (der < tamActual and nodos[der].id > nodos[mayor].id) {
        mayor = der;
    }

    if (mayor != i) {
        swap(i, mayor);
        hacerMaxHeap(mayor);
    }
}

void MaxHeap::swap(int i, int j) { 
    // Primero, swappeo los indices en el diccionario de índices.
    // Les resto 1 porque las ids guardadas en nodos son 1 más que las reales.
    int tempIndice = nodos[i].id;
    indicesPersona[nodos[i].id - 1] = indicesPersona[nodos[j].id - 1];
    indicesPersona[nodos[j].id - 1] = tempIndice - 1;

    Nodo temp = nodos[i];
    nodos[i] = nodos[j];
    nodos[j] = temp;
}