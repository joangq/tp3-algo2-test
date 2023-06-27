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
        Puesto(Menu precios, Stock stocks, Promociones descuentos);

        /** ObtenerStock
         * Precondicion: El item debe existir en el menu.
         * Complejidad: O(log I)
        */
        Cantidad obtenerStock(Producto item);

        /** ObtenerDescuento
         * Precondicion: El item debe existir en el menu.
         * Complejidad: O(log I + log cant)
        */
        Descuento obtenerDescuento(Producto item, Cantidad cant);

        /** ObtenerGasto
         * Precondicion: Nada
         * Complejidad: O(log A)
        */
        Dinero obtenerGasto(Persona persona);

        /** Vender
         * Precondicion: Debe haber suficiente stock del item.
         * Complejidad: O(log I + log A + log cant)
        */
        void vender(Persona persona, Producto item, Cantidad cant);

        /** OlvidarItem
         * Precondicion: El item debe existir y haber sido consumido sin promo.
         * Complejidad: O(log I + log A)
        */
        void olvidarItem(Persona persona, Producto item);

        /** ExisteEnStock?
         * Precondicion: Nada
         * Complejidad: O(log I)
        */
        bool existeEnStock(Producto item);

        /** CantComprasSinDesc
         * Precondicion: La persona debe haber comprado.
         * Complejidad: O(log I)
        */
        Nat cantComprasSinDesc(Persona persona, Producto item);

        /** PrecioConDescuento
         * Precondicion: El item debe existir en el menu. FIXME: Y tener desc?
         * Complejidad: O(log I + log cant)
        */
        Dinero precioConDescuento(Producto item, Cantidad cant);

        /** PrecioSinDescuento
         * Precondicion: El item debe existir en el menu.
         * Complejidad: O(log I)
        */
        Dinero precioSinDescuento(Producto item, Cantidad cant);

        /** ObtenerMenu
         * Precondicion: Nada
         * Complejidad: O(1)
        */
        Menu obtenerMenu();

        /** FIXME: Deberiamos tener "obtenerStock" y 
                  "obtenerPromociones"? */
        Stock stock();
        Promociones promociones();

    private:
        /* comprasPorItem */
        struct comprasPorItem {
            diccLog<Producto, list<Cantidad>> conDesc;
            diccLog<Producto, list<Cantidad>> sinDesc;
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