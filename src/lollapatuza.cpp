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

Lollapatuza::Lollapatuza() : _puestos(), _infoPersonas(), _gastosPersonas(), _personas() {};

Lollapatuza::Lollapatuza(const diccLog<IdPuesto, Puesto>& puestos, const set<Persona>& personas) : _gastosPersonas(puestos.size(), idMaximo(personas)) {
    // Creo una lista que contenga todos los items, y la lleno.
    set<Item> totalItems = set<Item>();

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

    map<Nat, minHeap> dic = map<Nat, minHeap>();

    for (auto item : totalItems)
        dic[item] = minHeap(puestos.size()); // Copia implícita.

    for (auto persona : personas) {
        auto nodo = Nodo(0, persona);
        _gastosPersonas.agregar(nodo);

        // En las siguientes asignaciones, la copia es implícita.
        infoCompras compras = infoCompras(0, dic);
        this->_infoPersonas[persona] = compras;
    }

    this->_personas = personas;
    this->_puestos = puestos;
}

Lollapatuza Lollapatuza::operator=(const Lollapatuza& lolla) {
    _personas = lolla._personas;
    _puestos = lolla._puestos;
    _infoPersonas = lolla._infoPersonas;
    _gastosPersonas = lolla._gastosPersonas;

    return *this;
}

void Lollapatuza::registrarCompra(IdPuesto pid, Persona persona, Producto item, Cantidad cant) {
    Puesto puesto = this->_puestos.at(pid);
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
    int menorStock = -1;
    int menorId = -1;
    Cant stockItem;

    // Itero sobre las tuplas (IdPuesto, Puesto)
    for (auto const& tup : _puestos) {
        IdPuesto pid = tup.first;
        Puesto puesto = tup.second;

        if (puesto.existeEnStock(item)) {
            stockItem = puesto.obtenerStock(item);

            if (menorStock == -1) {
                menorStock = stockItem;
                menorId = pid;
            }

            if (stockItem <= menorStock) {
                // Si son iguales, únicamente cambio el menorId si
                // el pid nuevo es menor al actual.
                if (stockItem == menorStock) {
                    if (pid < menorId) 
                        menorId = pid; 
                } 
                else {
                    menorId = pid;    
                }
                menorStock = stockItem;
            }
        }
    }

    return menorId;
}

const set<Persona>& Lollapatuza::obtenerPersonas() const {
    return this->_personas;
}

const diccLog<IdPuesto, Puesto>& Lollapatuza::obtenerPuestos() {
    return this->_puestos;
}

Persona Lollapatuza::idMaximo(const set<Persona>& personas) {
    // Utilizo 0 para que la comparación en el ciclo for
    // valga siempre la primera vez que ocurre (como mínimo, estos valores son 0).
    int idMax = 0;

    for (auto const& persona : personas) {
        if (persona > idMax) {
            idMax = persona;
        }
    }

    return idMax;
}

// Funciones no presentes directamente en el TP2, pero utilizadas
// para el adecuado funcionamiento de fachada_lollapatuza.h
Nat Lollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto& producto) const {
    return _puestos.at(idPuesto).obtenerStock(producto);
}

Nat Lollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto& producto, Nat cantidad) const {
    return _puestos.at(idPuesto).obtenerDescuento(producto, cantidad);
}

Nat Lollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const {
    return _puestos.at(idPuesto).obtenerGasto(persona);
}

set<IdPuesto> Lollapatuza::idsDePuestos() const {
    set<IdPuesto> ids;

    // Itero sobre las tuplas (IdPuesto, Puesto)
    for (auto const& tup : _puestos) {
        ids.emplace(tup.first);
    }

    return ids;
}