#include <map>
#include <set>
#include <list>
#include <vector>
#include "tipos.h"
#include "puesto.h"
#include "lollapatuza.h"

using namespace std;

Lollapatuza::Lollapatuza(diccLog<IdPuesto, Puesto> puestos, set<Persona> personas) {
    // TODO
}

void Lollapatuza::registrarCompra(IdPuesto pid, Persona persona, Producto item, Cantidad cant) {
    // TODO
}

void Lollapatuza::hackear(Persona persona, Producto item) {
    // TODO
}


Dinero Lollapatuza::gastoTotalPersona(Persona persona) {
    // TODO
}


Persona Lollapatuza::personaMayorGasto() {
    // TODO
}

IdPuesto Lollapatuza::menorStock(Producto item) {
    // TODO
}


set<Persona> Lollapatuza::obtenerPersonas() {
    // TODO
}


diccLog<IdPuesto, Puesto> Lollapatuza::obtenerPuestos() {
    // TODO
}