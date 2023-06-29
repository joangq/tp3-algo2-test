#include <map>
#include <list>
#include <utility>
#include <vector>
#include "puesto.h"
#include "auxiliares.h"

Puesto::Puesto() = default;

Puesto::comprasPorItem::comprasPorItem(): conDesc(), sinDesc() {}

Puesto::Puesto(const Menu& precios, const Stock& stocks, const Promociones& descuentos) {
    // Itero sobre las tuplas (Item, map<Nat, Nat>)
    for (auto& itemDescuentos : descuentos) {
        Producto item = itemDescuentos.first;
        const map<Cantidad, Nat>& dicc = itemDescuentos.second;

        vector<Cantidad> descPorItem(dicc.size());

        // Itero sobre las tuplas (Cant, Nat)
        int k = 0;
        for (auto& infoDescuento : dicc) descPorItem[k++] = infoDescuento.first;

        descPorItem = mergeSort(descPorItem);

        this->_descuentosPorItem[item] = std::move(descPorItem);
    }

    this->_stock = stocks;
    this->_precios = precios;
    this->_descuentos = descuentos;


}

const Cantidad& Puesto::obtenerStock(const Producto& item) const {
    return this->_stock.at(item);
}

Descuento Puesto::obtenerDescuento(const Producto& item, const Cantidad& cant) const {
    if (cant == 0 || _descuentosPorItem.count(item) == 0) return 0;

    const vector<Cantidad>& cantidades = _descuentosPorItem.at(item);

    if (cant < cantidades[0]) return 0;

    Nat i = busquedaBinaria(cantidades, cant, 0, cantidades.size());
    return _descuentos.at(item).at(cantidades[i]);
}

Dinero Puesto::obtenerGasto(const Persona& persona) const {
    return _gastoPorPersona.count(persona) != 0 ? _gastoPorPersona.at(persona) : 0;

}

void Puesto::vender(const Persona& persona, const Producto& item, const Cantidad& cant) {
    const Cantidad& stockItem = _stock[item];
    Dinero& gastoPersona = _gastoPorPersona[persona];

    const Dinero& precioBase = precioSinDescuento(item, cant);
    const Dinero& precioFinal = precioConDescuento(item, cant);

    comprasPorItem& comprasPersona = _comprasPorPersona[persona];

    _stock[item] = stockItem - cant;
    gastoPersona += precioFinal;

    diccLog<Producto, list<Cantidad>>* compras = &(precioBase != precioFinal
                                               ? comprasPersona.conDesc
                                               : comprasPersona.sinDesc);

    (*compras)[item].push_front(cant);
}

void Puesto::olvidarItem(const Persona& persona, const Producto& item) {
    comprasPorItem& comprasPersonas = _comprasPorPersona[persona];
    list<Cantidad>& comprasItem = comprasPersonas.sinDesc[item];
    Nat& compra = comprasItem.front();

    compra -= 1;

    if (compra == 0)
        comprasItem.pop_front();

    this->_stock[item] += 1;

    _gastoPorPersona[persona] -= precioSinDescuento(item, 1);
}

bool Puesto::existeEnStock(const Producto& item) const {
    return _stock.count(item) == 1;
}

Nat Puesto::cantComprasSinDesc(const Persona& persona, const Producto& item) const {
    if (_comprasPorPersona.count(persona) != 1) return 0;

    const diccLog<Producto, list<Cantidad>>& d = _comprasPorPersona.at(persona).sinDesc;

    if (d.count(item) == 1)
        return d.at(item).size();

    return 0;
}

Dinero Puesto::precioConDescuento(const Producto& item, const Cantidad& cant) const {
    Descuento descuento = obtenerDescuento(item, cant);
    Dinero precioBase = precioSinDescuento(item, cant);

    if (descuento == 0)
        return precioBase;

    float calculoDescuento = (float) precioBase * ((float) descuento / 100);

    return (int) ((float) precioBase - calculoDescuento);
}

Dinero Puesto::precioSinDescuento(const Producto& item, const Cantidad& cant) const {
    return _precios.at(item) * cant;
}

const Menu& Puesto::obtenerMenu() {
    return this->_precios;
}

const Stock& Puesto::stock() {
    return this->_stock;
}

const Promociones& Puesto::promociones() {
    return this->_descuentos;
}