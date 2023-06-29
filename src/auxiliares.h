#ifndef AUXILIARES
#define AUXILIARES
#include "tipos.h"
#include <vector>

Nat busquedaBinaria(const vector<Nat>& A, Nat x, Nat low, Nat high);

vector<Nat> merge(const vector<Nat>& A, const vector<Nat>& B);

vector<Nat> mergeSort(vector<Nat> A);

#endif //AUXILIARES