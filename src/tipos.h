#ifndef SOLUCION_TIPOS_H
#define SOLUCION_TIPOS_H

#include <string>
#include <map>
#include <queue>

using namespace std;

using Nat = unsigned int;

/* Renombres especificos del TP */
using Cantidad = Nat;
using Descuento = Nat;
using Dinero = Nat;

template<typename K, typename V>
using diccLog = map<K, V>;

/* FIXME FIXME FIXME FIXME 
   ACA DEBERIA IR NUESTRO
   MIN HEAP */
template<typename T>
using minHeap = queue<T>;

/* FIXME FIXME FIXME FIXME 
   ACA DEBERIA IR NUESTRO
   MAX HEAP */
template<typename T>
using maxHeap = queue<T>;

// Los cambié para que sean Nat
using Persona = Nat;
using IdPuesto = Nat;
using Producto = Nat;

using Stock = map<Producto, Nat>;
using Promociones = map<Producto, map<Nat, Nat>>;
using Menu = map<Producto, Nat>;

// Tipos agregados por nosotros
using Cant = int;
//using Descuento = int;
// using Dinero = int;
using Id = int;
using Item = int;

struct aed2_Puesto {
    Stock stock;
    Promociones promociones;
    Menu menu;
};

#endif //SOLUCION_TIPOS_H
