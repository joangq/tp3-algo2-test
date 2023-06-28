#include <map>
#include <list>
#include <vector>
#include "tipos.h"
#include "puesto.h"
#include "auxiliares.h"

Puesto::Puesto() {
    
}

Puesto::Puesto(Menu precios, Stock stocks, Promociones descuentos) {
    // Itero sobre las tuplas (Item, map<Nat, Nat>)
    for (auto& tup : descuentos) {
        Item item = tup.first;
        map<Cant, Nat>& dicc = tup.second;

        vector<Cant> temp(dicc.size());

        int k = 0;
        // Itero sobre las tuplas (Cant, Nat)
        for (auto& tup : dicc) {
            temp[k] = tup.first;
            ++k;
        }

        temp = mergeSort(temp);

        // En esta asignación, la copia es implícita.
        this->_descuentosPorItem[item] = temp;
    }

    this->_stock = stocks;
    this->_precios = precios;
    this->_descuentos = descuentos;
}

Cantidad Puesto::obtenerStock(Producto item) {
    return this->_stock.at(item);
}

// J: Removí unos "else" innecesarios
Descuento Puesto::obtenerDescuento(Producto item, Cantidad cant) {
    if (cant == 0 || _descuentosPorItem.count(item) == 0)
        return 0;
    
    const vector<Cant>& cantidades = _descuentosPorItem.at(item);

    if (cant < cantidades[0])
        return 0;
    
    
    int i = busquedaBinaria(cantidades, cant, 0, cantidades.size());
    return _descuentos[item][cantidades[i]];
}

Dinero Puesto::obtenerGasto(Persona persona) {
     return this->_gastoPorPersona.at(persona);
}

// J: Cambié "compras" por "diccLog<...>"
void Puesto::vender(Persona persona, Producto item, Cantidad cant) {
    Cant stockItem = _stock[item];
    Dinero gastoPersona = _gastoPorPersona[persona];

    Dinero precioBase = precioSinDescuento(item, cant);
    Dinero precioFinal = precioConDescuento(item, cant);

    comprasPorItem& comprasPersona = _comprasPorPersona[persona];

    _stock[item] = stockItem - cant;
    gastoPersona += precioFinal;

    diccLog<Producto, list<Cantidad>>& compras = comprasPersona.sinDesc;

    if (precioBase != precioFinal)
        compras = comprasPersona.conDesc;

    compras[item].push_front(cant);
}

void Puesto::olvidarItem(Persona persona, Producto item) {
    comprasPorItem& comprasPersonas = _comprasPorPersona[persona];
    list<Cant>& comprasItem = comprasPersonas.sinDesc[item];
    Nat& compra = comprasItem.front();

    compra -= 1;

    if (compra == 0)
        comprasItem.pop_front();
}

bool Puesto::existeEnStock(Producto item) {
    return _stock.count(item) == 1;
}

// J: Cambié "compras" por "diccLog<...>" y "sinDesc" por "d".
Nat Puesto::cantComprasSinDesc(Persona persona, Producto item) {
    diccLog<Producto, list<Cantidad>>& d = _comprasPorPersona[persona].sinDesc;

    if (d.count(item) == 1)
        return d[item].size();
    
    return 0;
}

Dinero Puesto::precioConDescuento(Producto item, Cantidad cant) {
    Descuento descuento = obtenerDescuento(item, cant);
    Dinero precioBase = precioSinDescuento(item, cant);

    return (precioBase - (precioBase / descuento));
}

Dinero Puesto::precioSinDescuento(Producto item, Cantidad cant) {
     return _precios.at(item) * cant;
}

Menu Puesto::obtenerMenu() {
    return this->_precios;
}

// FIXME: Debería ser una referencia para evitar la copia?
Stock Puesto::stock() {
    return this->_stock;
}

// FIXME: Debería ser una referencia para evitar la copia?
Promociones Puesto::promociones() {
    return this->_descuentos;
}