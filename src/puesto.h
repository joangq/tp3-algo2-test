#ifndef PUESTO
#define PUESTO

#include <map>
#include <list>
#include <vector>
#include "tipos.h"

using namespace std;

class Puesto {
    public:
        Puesto();
        /** CrearPuesto
         * Precondicion: Los stocks y los puestos tienen las mismas
         * claves. Las claves de descuentos estan contenidas en ellas.
         * Complejidad: O(I * (cant*log(cant) + log I))
        */
        Puesto(const Menu& precios, const Stock& stocks, const Promociones& descuentos);

        /** ObtenerStock
         * Precondicion: El item debe existir en el menu.
         * Complejidad: O(log I)
        */
        const Cantidad& obtenerStock(const Producto& item) const;

        /** ObtenerDescuento
         * Precondicion: El item debe existir en el menu.
         * Complejidad: O(log I + log cant)
        */
        Descuento obtenerDescuento(const Producto& item, const Cantidad& cant) const;

        /** ObtenerGasto
         * Precondicion: Nada
         * Complejidad: O(log A)
        */
        Dinero obtenerGasto(const Persona& persona) const;

        /** Vender
         * Precondicion: Debe haber suficiente stock del item.
         * Complejidad: O(log I + log A + log cant)
        */
        void vender(const Persona& persona, const Producto& item, const Cantidad& cant);

        /** OlvidarItem
         * Precondicion: El item debe existir y haber sido consumido sin promo.
         * Complejidad: O(log I + log A)
        */
        void olvidarItem(const Persona& persona, const Producto& item);

        /** ExisteEnStock?
         * Precondicion: Nada
         * Complejidad: O(log I)
        */
        bool existeEnStock(const Producto& item) const;

        /** CantComprasSinDesc
         * Precondicion: La persona debe haber comprado.
         * Complejidad: O(log I)
        */
        Nat cantComprasSinDesc(const Persona& persona, const Producto& item) const;

        /** PrecioConDescuento
         * Precondicion: El item debe existir en el menu.
         * Complejidad: O(log I + log cant)
        */
        Dinero precioConDescuento(const Producto& item, const Cantidad& cant) const;

        /** PrecioSinDescuento
         * Precondicion: El item debe existir en el menu.
         * Complejidad: O(log I)
        */
        Dinero precioSinDescuento(const Producto& item, const Cantidad& cant) const;

        /** ObtenerMenu
         * Precondicion: Nada
         * Complejidad: O(1)
        */
        const Menu& obtenerMenu();

        /** Getter - Stock
         * Precondicion: Nada
         * Complejidad: O(1)
        */
        const Stock& stock();

        /** Getter - Promociones
         * Precondicion: Nada
         * Complejidad: O(1)
        */
        const Promociones& promociones();

    private:
        /* comprasPorItem */
        struct comprasPorItem {
            diccLog<Producto, list<Cantidad>> conDesc;
            diccLog<Producto, list<Cantidad>> sinDesc;
            comprasPorItem();
        };

        /* estrPuesto */
        Stock _stock;
        Menu _precios;
        diccLog<Persona, comprasPorItem> _comprasPorPersona;
        diccLog<Persona, Dinero> _gastoPorPersona;
        diccLog<Producto, diccLog<Cantidad, Dinero>> _descuentos;
        diccLog<Producto, vector<Cantidad>> _descuentosPorItem;

};

#endif //PUESTO