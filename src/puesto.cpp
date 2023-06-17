#pragma once
#include <map>
#include <list>
#include <vector>
#include "tipos.h"
#include "puesto.h"

Puesto::Puesto(Menu precios, Stock stocks, Promociones descuentos) {
    // TODO
}

Cantidad Puesto::obtenerStock(Producto item) {
    // TODO
}

Descuento Puesto::obtenerDescuento(Producto item, Cantidad cant) {
    // TODO
}

Dinero Puesto::obtenerGasto(Persona persona) {
    // TODO
}

void Puesto::vender(Persona persona, Producto item, Cantidad cant) {
    // TODO
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