#include <map>
#include <list>
#include <utility>
#include <vector>
#include "puesto.h"
#include "auxiliares.h"

Puesto::Puesto() = default;

Puesto::comprasPorItem::comprasPorItem(): conDesc(), sinDesc() {};

Puesto::Puesto(const Menu& precios, const Stock& stocks, const Promociones& descuentos) {
    // Itero sobre las tuplas (Item, map<Nat, Nat>)
    for (auto& itemDescuentos : descuentos) {
        Item item = itemDescuentos.first;
        const map<Cant, Nat>& dicc = itemDescuentos.second;

        vector<Cant> temp(dicc.size());

        // Itero sobre las tuplas (Cant, Nat)
        int k = 0;
        for (auto& infoDescuento : dicc)
            temp[k++] = infoDescuento.first;

        temp = mergeSort(temp);

        // En esta asignación, la copia es implícita.
        this->_descuentosPorItem[item] = std::move(temp);
    }

    this->_stock = stocks;
    this->_precios = precios;
    this->_descuentos = descuentos;


}

Cantidad Puesto::obtenerStock(const Producto& item) const {
    return this->_stock.at(item);
}

Descuento Puesto::obtenerDescuento(const Producto& item, const Cantidad& cant) const {
    if (cant == 0 || _descuentosPorItem.count(item) == 0)
        return 0;

    const vector<Cant>& cantidades = _descuentosPorItem.at(item);

    if (cant < cantidades[0])
        return 0;


    Nat i = busquedaBinaria(cantidades, cant, 0, cantidades.size());
    return _descuentos.at(item).at(cantidades[i]);
}

Dinero Puesto::obtenerGasto(Persona persona) const {
    if (_gastoPorPersona.count(persona) == 1) {
        return _gastoPorPersona.at(persona);
    }

    return 0;
}

// J: Cambié "compras" por "diccLog<...>"
void Puesto::vender(Persona persona, Producto item, Cantidad cant) {
    Cant stockItem = _stock[item];
    Dinero& gastoPersona = _gastoPorPersona[persona];

    Dinero precioBase = precioSinDescuento(item, cant);
    Dinero precioFinal = precioConDescuento(item, cant);

    comprasPorItem& comprasPersona = _comprasPorPersona[persona];

    // Accede al item y no al indice del item

    _stock[item] = stockItem - cant;
    gastoPersona += precioFinal;

    diccLog<Producto, list<Cantidad>>* compras;

    if (precioBase != precioFinal)
        compras = &comprasPersona.conDesc;
    else
        compras = &comprasPersona.sinDesc;

    (*compras)[item].push_front(cant);
}

void Puesto::olvidarItem(Persona persona, Producto item) {
    comprasPorItem& comprasPersonas = _comprasPorPersona[persona];
    list<Cant>& comprasItem = comprasPersonas.sinDesc[item];
    Nat& compra = comprasItem.front();

    compra -= 1;

    if (compra == 0)
        comprasItem.pop_front();

    this->_stock[item] += 1;

    _gastoPorPersona[persona] -= precioSinDescuento(item, 1);
}

bool Puesto::existeEnStock(Producto item) const {
    return _stock.count(item) == 1;
}

Nat Puesto::cantComprasSinDesc(Persona persona, Producto item) const {
    if (_comprasPorPersona.count(persona) == 1) {
        const diccLog<Producto, list<Cantidad>>& d = _comprasPorPersona.at(persona).sinDesc;
        if (d.count(item) == 1)
            return d.at(item).size();
    }

    return 0;
}

Dinero Puesto::precioConDescuento(Producto item, Cantidad cant) const {
    Descuento descuento = obtenerDescuento(item, cant);
    Dinero precioBase = precioSinDescuento(item, cant);

    if (descuento == 0)
        return precioBase;

    float calculoDescuento = (float) precioBase * ((float) descuento / 100);

    return (int) ((float) precioBase - calculoDescuento);
}

Dinero Puesto::precioSinDescuento(Producto item, Cantidad cant) const {
    return _precios.at(item) * cant;
}

Menu& Puesto::obtenerMenu() {
    return this->_precios;
}

Stock& Puesto::stock() {
    return this->_stock;
}

Promociones& Puesto::promociones() {
    return this->_descuentos;
}