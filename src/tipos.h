#ifndef SOLUCION_TIPOS_H
#define SOLUCION_TIPOS_H

#include <string>
#include <map>

using namespace std;

using Nat = unsigned int;

/* Renombres especificos del TP */
using Cantidad = Nat;
using Descuento = Nat;
using Dinero = Nat;

template<typename K, typename V>
using diccLog = map<K, V>;

// Los cambié para que sean Nat
using Persona = Nat;
using IdPuesto = Nat;
using Producto = Nat;

using Stock = map<Producto, Nat>;
using Promociones = map<Producto, map<Nat, Nat>>;
using Menu = map<Producto, Nat>;

struct aed2_Puesto {
    Stock stock;
    Promociones promociones;
    Menu menu;
};

#endif //SOLUCION_TIPOS_H
