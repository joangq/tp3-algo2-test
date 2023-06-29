#include "heap_aux.h"

Nat Izq(Nat n){
    return 2*n + 1;
}

Nat Der(Nat n){
    return 2*n + 2;
}

Nat Padre(Nat n){
    return (n-1)/2;
}