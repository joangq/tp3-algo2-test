#ifndef AUXILIARES
#define AUXILIARES
#include "tipos.h"
#include <vector>

Nat busquedaBinaria(const vector<Nat>& A, Nat x, Nat low, Nat high) {
    if (high - low == 1) return low;

    Nat mid = (low + high) / 2;

    return x < A[mid]? busquedaBinaria(A, x, low, mid) : busquedaBinaria(A, x, mid, high);
}

vector<Nat> merge(const vector<Nat>& A, const vector<Nat>& B) {
    Nat n = A.size();
    Nat m = B.size();

    vector<Nat> result(n + m);

    Nat i = 0;
    Nat j = 0;
    Nat k = 0;
    
    while (i < n and j < m)
        result[k++] = A[i] <= B[j]? A[i++] : B[j++];

    // Agrego los elementos restantes
    while (i < n) result[k++] = A[i++];
    while (j < m) result[k++] = B[j++];

    return result;
}

vector<Nat> mergeSort(vector<Nat> A) {
    Nat n = A.size();
    if (n <= 1) return A;

    Nat mid = n / 2;
    vector<Nat> left(A.begin(), A.begin()+mid);
    vector<Nat> right(A.begin()+mid, A.end());

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

#endif //AUXILIARES