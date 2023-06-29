#include "fachada_lollapatuza.h"

FachadaLollapatuza::FachadaLollapatuza(
    const set<Persona> &personas,
    const map<IdPuesto, aed2_Puesto> &infoPuestos) {
    
    map<IdPuesto, Puesto> copiaPuestos;

    // Itero sobre las tuplas <IdPuesto, aed2_Puesto>
    for (auto const &tup : infoPuestos) {
        IdPuesto id = tup.first;
        const aed2_Puesto &puesto = tup.second;
        copiaPuestos[id] =
            Puesto(puesto.menu, puesto.stock, puesto.promociones);
    }
    
    _lolla = Lollapatuza(copiaPuestos, personas); 
}
void FachadaLollapatuza::registrarCompra(Persona persona, Producto producto,
                                         Nat cant, IdPuesto idPuesto) {
    _lolla.registrarCompra(idPuesto, persona, producto, cant);
}

void FachadaLollapatuza::hackear(Persona persona, Producto producto) {
    _lolla.hackear(persona, producto);
}

Nat FachadaLollapatuza::gastoTotal(Persona persona) const {
    return _lolla.gastoTotalPersona(persona);
}

Persona FachadaLollapatuza::mayorGastador() const {
    return _lolla.personaMayorGasto();
}

IdPuesto FachadaLollapatuza::menorStock(Producto producto) const {
    return _lolla.menorStock(producto);
}

const set<Persona> &FachadaLollapatuza::personas() const {
    return _lolla.obtenerPersonas();
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto,
                                      const Producto &producto) const {
    return _lolla.stockEnPuesto(idPuesto, producto);
}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto,
                                          const Producto &producto,
                                          Nat cantidad) const {
    return _lolla.descuentoEnPuesto(idPuesto, producto, cantidad);
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto,
                                      Persona persona) const {
    return _lolla.gastoEnPuesto(idPuesto, persona);
}

set<IdPuesto> FachadaLollapatuza::idsDePuestos() const {
    return _lolla.idsDePuestos();
}
