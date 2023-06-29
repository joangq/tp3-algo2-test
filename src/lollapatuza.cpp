#include <map>
#include <set>
#include <utility>
#include "puesto.h"
#include "lollapatuza.h"

using namespace std;

Lollapatuza::infoCompras::infoCompras(Dinero gastoTotal, diccLog<Producto, minHeap> hackeables)
    : gastoTotal(gastoTotal), hackeables(std::move(hackeables)) {}

Lollapatuza::infoCompras::infoCompras()
    : gastoTotal(0), hackeables() {}

Lollapatuza::Lollapatuza()
    : _puestos(), _infoPersonas(), _gastosPersonas(), _personas() {}

Lollapatuza::Lollapatuza(const diccLog<IdPuesto, Puesto> &puestos, const set<Persona> &personas) {
    _gastosPersonas = maxHeap(puestos.size(), idMaximo(personas));
    // Creo una lista que contenga todos los items, y la lleno.
    set<Producto> totalItems = set<Producto>();

    // Itero sobre las tuplas de (IdPuesto, Puesto).
    for (auto const &tup: puestos) {
        // Utilizo referencias para evitar copiar la estructura.
        Puesto puesto = tup.second;
        const Stock &stock = puesto.stock();

        // Itero sobre las tuplas de (Item, Cant).
        for (auto const &itemTup: stock) {
            Producto item = itemTup.first;
            // std::set no inserta el elemento si ya está en el conjunto.
            totalItems.emplace(item);
        }
    }

    map<Nat, minHeap> dic = map<Nat, minHeap>();

    for (auto item: totalItems)
        dic[item] = minHeap(puestos.size()); // Copia implícita.

    for (auto persona: personas) {
        auto nodo = Nodo(0, persona);
        _gastosPersonas.agregar(nodo);

        // En las siguientes asignaciones, la copia es implícita.
        infoCompras compras = infoCompras(0, dic);
        this->_infoPersonas[persona] = compras;
    }

    this->_personas = personas;
    this->_puestos = puestos;
}

Lollapatuza& Lollapatuza::operator=(const Lollapatuza &lolla) = default;

void Lollapatuza::registrarCompra(IdPuesto pid, Persona persona, Producto item, Cantidad cant) {
    Puesto &puesto = this->_puestos.at(pid);
    (&puesto)->vender(persona, item, cant);

    infoCompras &compras = this->_infoPersonas[persona];
    const Nat precioConDescuento = (&puesto)->precioConDescuento(item, cant);
    compras.gastoTotal += precioConDescuento;

    if (precioConDescuento == puesto.precioSinDescuento(item, cant) && puesto.cantComprasSinDesc(persona, item) == 1)
        compras.hackeables[item].agregar(TupPuesto(pid, &puesto));

    _gastosPersonas.modificarGasto(persona, compras.gastoTotal);
}

// J: Cambié "infoCompras" por "compras" para que no colisionen
void Lollapatuza::hackear(Persona persona, Producto item) {
    infoCompras &compras = this->_infoPersonas[persona];
    minHeap &hackeablesItem = compras.hackeables[item];
    Puesto *puestoAHackear = hackeablesItem.minimo();

    if (puestoAHackear == nullptr)
        return;

    puestoAHackear->olvidarItem(persona, item);

    Cantidad cantCompras = puestoAHackear->cantComprasSinDesc(persona, item);

    if (cantCompras == 0)
        hackeablesItem.removerMinimo();


    Nat precioItem = puestoAHackear->precioSinDescuento(item, 1);
    compras.gastoTotal -= precioItem;

    _gastosPersonas.modificarGasto(persona, compras.gastoTotal);
}


Dinero Lollapatuza::gastoTotalPersona(Persona persona) const {
    return _infoPersonas.at(persona).gastoTotal;
}


Persona Lollapatuza::personaMayorGasto() const {
    return _gastosPersonas.maximo();
}

IdPuesto Lollapatuza::menorStock(Producto item) const {
    int menorStock = -1;
    int menorId = -1;
    Cantidad stockItem;

    // Itero sobre las tuplas (IdPuesto, Puesto)
    for (auto const &infoPuesto: _puestos) {
        const IdPuesto pid = infoPuesto.first;
        const Puesto puesto = infoPuesto.second;

        if (!puesto.existeEnStock(item)) continue; // Si el puesto no tiene el item, no hago nada.

        stockItem = puesto.obtenerStock(item);

        if (menorStock == -1) {
            menorStock = (int) stockItem;
            menorId = (int) pid;
        }

        if (stockItem > menorStock) continue; // Si el stock es mayor, no hago nada.

        // Únicamente cambio el menorId si el pid nuevo es menor al actual.
        if (stockItem != menorStock || pid < menorId) menorId = (int) pid;
        menorStock = (int) stockItem;
    }

    return menorId;
}

const set<Persona> &Lollapatuza::obtenerPersonas() const {
    return this->_personas;
}

const diccLog<IdPuesto, Puesto> &Lollapatuza::obtenerPuestos() {
    return this->_puestos;
}

Persona Lollapatuza::idMaximo(const set<Persona> &personas) {
    Nat idMax = 0; // El id mínimo es 0
    for (auto const &idPersona: personas)
        if (idPersona > idMax)
            idMax = idPersona;

    return idMax;
}

/* Funciones auxiliares utilizadas para el correcto funcionamiento de fachada_lollapatuza */

Nat Lollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const {
    return _puestos.at(idPuesto).obtenerStock(producto);;
}

Nat Lollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const {
    return _puestos.at(idPuesto).obtenerDescuento(producto, cantidad);;
}

Nat Lollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const {
    return _puestos.at(idPuesto).obtenerGasto(persona);;
}

set<IdPuesto> Lollapatuza::idsDePuestos() const {
    set<IdPuesto> ids;

    // Itero sobre las tuplas (IdPuesto, Puesto)
    for (auto const &infoPuesto: _puestos)
        ids.emplace(infoPuesto.first);

    return ids;
}