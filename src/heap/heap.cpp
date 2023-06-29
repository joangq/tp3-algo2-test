#include "heap.h"

const Nat heap::Izq(Nat n){
    return 2*n + 1;
}

const Nat heap::Der(Nat n){
    return 2*n + 2;
}

const Nat heap::Padre(Nat n){
    return (n-1)/2;
}

const Nat heap::potenciaDeDos(Nat n) {
    Nat v = n;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}