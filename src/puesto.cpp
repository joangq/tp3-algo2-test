#pragma once
#include <map>
#include <list>
#include <vector>
#include "tipos.h"
#include "puesto.h"
#include "auxiliares.h"

Puesto::Puesto(Menu precios, Stock stocks, Promociones descuentos) {
    // Itero sobre las tuplas (Item, map<Nat, Nat>)
    for (auto& tup : descuentos) {
        Producto item = tup.first;
        map<Nat, Nat>& dicc = tup.second;

        vector<Cantidad> temp(dicc.size());

        int k = 0;
        // Itero sobre las tuplas (Cant, Nat)
        for (auto& tup : dicc) {
            temp[k] = tup.first;
            ++k;
        }

        temp = mergeSort(temp);

        // En esta asignación, la copia es implícita.
        _descuentosPorItem[item] = temp;
    }

    this->_stock = stocks;
    this->_precios = precios;
    this->_descuentos = descuentos;
}

Cantidad Puesto::obtenerStock(Producto item) {
    return _stock.at(item);
}

Descuento Puesto::obtenerDescuento(Producto item, Cantidad cant) {
    if (cant = 0 || _descuentosPorItem.count(item) == 0) {
        return 0;
    } else {
        const vector<Cantidad>& cantidades = _descuentosPorItem.at(item);

        if (cant < cantidades[0]) {
            return 0;
        } else {
            int i = busquedaBinaria(cantidades, cant, 0, cantidades.size());
            return cantidades[i];
        }
    }
}

Dinero Puesto::obtenerGasto(Persona persona) {
    return _gastoPorPersona.at(persona);
}

void Puesto::vender(Persona persona, Producto item, Cantidad cant) {
    Cantidad stockItem = _stock[item];
    Dinero gastoPersona = _gastoPorPersona[persona];

    Dinero precioBase = precioSinDescuento(item, cant);
    Dinero precioFinal = precioConDescuento(item, cant);

    comprasPorItem& comprasPersona = _comprasPorPersona[persona];

    _stock[item] = stockItem - cant;
    gastoPersona += precioFinal;

    Compras& diccCompras = comprasPersona.sinDesc;

    if(precioBase != precioFinal){
        diccCompras = comprasPersona.conDesc;
    }
    diccCompras[item].push_front(cant);
}

void Puesto::olvidarItem(Persona persona, Producto item) {
    // TODO
}

bool Puesto::existeEnStock(Producto item) {
    // TODO
}

Nat Puesto::cantComprasSinDesc(Persona persona, Producto item) {
    // TODO
}

Dinero Puesto::precioConDescuento(Producto item, Cantidad cant) {
    // TODO
}

Dinero Puesto::precioSinDescuento(Producto item, Cantidad cant) {
    // TODO
}

Menu Puesto::obtenerMenu() {
    // TODO
}
