#include <map>
#include <set>
#include <list>
#include <vector>
#include "tipos.h"
#include "puesto.h"
#include "lollapatuza.h"

using namespace std;

Lollapatuza::infoCompras::infoCompras(Dinero gastoTotal, diccLog<Producto, minHeap> hackeables): gastoTotal(gastoTotal), hackeables(hackeables) { };

Lollapatuza::infoCompras::infoCompras() : gastoTotal(0), hackeables() { };

Lollapatuza::Lollapatuza(diccLog<IdPuesto, Puesto> puestos, set<Persona> personas) : _gastosPersonas(puestos.size(), idMaximo(personas)){
    // Creo una lista que contenga todos los items, y la lleno.
    set<Item> totalItems;

    // Itero sobre las tuplas de (IdPuesto, Puesto).
    for (auto const& tup : puestos) {
        // Utilizo referencias para evitar copiar la estructura.
        Puesto puesto = tup.second;
        const Stock& stock = puesto.stock();

        // Itero sobre las tuplas de (Item, Cant).
        for (auto const& itemTup : stock) {
            Item item = itemTup.first;
            // std::set no inserta el elemento si ya está en el conjunto.
            totalItems.emplace(item);
        }
    }

    map<Nat, minHeap> dic;

    // J: Moví el constructor para que esté inline
    for (auto item : totalItems)
        dic[item] = minHeap(puestos.size()); // Copia implícita.

    for (auto persona : personas) {
        _gastosPersonas.agregar(Nodo(0, persona));

        // En las siguientes asignaciones, la copia es implícita.
        infoCompras compras = infoCompras(0, dic);
        this->_infoPersonas[persona] = compras;
    }

    this->_puestos = puestos;
    this->_personas = personas;
}

// J: Cambié "infoCompras" por "compras" para que no colisionen
void Lollapatuza::registrarCompra(IdPuesto pid, Persona persona, Producto item, Cantidad cant) {
    Puesto puesto = this->_puestos[pid];
    puesto.vender(persona, item, cant);

    infoCompras& compras = this->_infoPersonas[persona];
    int precioConDescuento = puesto.precioConDescuento(item, cant);
    compras.gastoTotal += precioConDescuento;

    // J: Se puede resumir en el mismo if?
    if (precioConDescuento == puesto.precioSinDescuento(item, cant))
        if (puesto.cantComprasSinDesc(persona, item) == 0)
            compras.hackeables[item].agregar(TupPuesto(pid, &puesto));

    _gastosPersonas.modificarGasto(persona, compras.gastoTotal);
}

// J: Cambié "infoCompras" por "compras" para que no colisionen
void Lollapatuza::hackear(Persona persona, Producto item) {
    infoCompras& compras = this->_infoPersonas[persona];
    minHeap& hackeablesItem = compras.hackeables[item];
    Puesto& puestoAHackear = *(hackeablesItem.minimo());

    Cant cantItem = puestoAHackear.cantComprasSinDesc(persona, item);

    if (cantItem == 1)
        hackeablesItem.removerMinimo();

    puestoAHackear.olvidarItem(persona, item);

    int precioItem = puestoAHackear.precioSinDescuento(item, 1);
    compras.gastoTotal -= precioItem;

    _gastosPersonas.modificarGasto(persona, compras.gastoTotal);
}


Dinero Lollapatuza::gastoTotalPersona(Persona persona) const {
    return this->_infoPersonas.at(persona).gastoTotal;
}


Persona Lollapatuza::personaMayorGasto() const {
    return _gastosPersonas.maximo();
}

IdPuesto Lollapatuza::menorStock(Producto item) const {
    // Utilizo INT32_MAX para que la comparación en el ciclo for
    // valga siempre la primera vez que ocurre.
    int32_t menorStock = INT32_MAX;
    int32_t menorId = INT32_MAX;
    Cant stockItem;

    // Itero sobre las tuplas (IdPuesto, Puesto)
    for (auto const& tup : _puestos) {
        IdPuesto pid = tup.first;
        /* FIXME: (J) En el código original esto es
                  const Puesto&, el tema es que
                  "existeEnStock" y "obtenerStock"
                  no podían aplicarse a algo de ese tipo
                  y no lo pude solucionar desreferenciando. */
        Puesto puesto = tup.second;

        if (puesto.existeEnStock(item)) {
            stockItem = puesto.obtenerStock(item);

            if (stockItem <= menorStock) {
                // Si son iguales, únicamente cambio el menorId si
                // el pid nuevo es menor al actual.
                if (stockItem == menorStock) {
                    if (pid < menorId) // FIXME (J) Este if está raro.
                        menorId = pid; // {stockIt == menSt /\ pid < menorID}
                } 
                else {               // \/ {stockIt != menSt}
                    menorId = pid;     // No son la misma condición?
                }
                menorStock = stockItem;
            }
        }
    }

    return menorId;
}

set<Persona>& Lollapatuza::obtenerPersonas() {
    return this->_personas;
}

diccLog<IdPuesto, Puesto>& Lollapatuza::obtenerPuestos() {
    return this->_puestos;
}

Persona Lollapatuza::idMaximo(const set<Persona>& personas) {
    // Utilizo INT32_MIN para que la comparación en el ciclo for
    // valga siempre la primera vez que ocurre.
    int32_t idMax = INT32_MIN;

    for (auto const& persona : personas) {
        if (persona > idMax) {
            idMax = persona;
        }
    }

    return idMax;
}