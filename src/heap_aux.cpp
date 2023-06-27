#include "heap_aux.h"

int Izq(int n){
    return 2*n + 1;
}

int Der(int n){
    return 2*n + 2;
}

int Padre(int n){
    return (n-1)/2;
}