#ifndef LOLLAPATUZA
#define LOLLAPATUZA
#include <map>
#include <set>
#include <list>
#include <vector>
#include "tipos.h"
#include "puesto.h"
#include "../src/max_heap.h"
#include "../src/min_heap.h"
#include "../src/heap_aux.h"

using namespace std;

class Lollapatuza {
    public:
        Lollapatuza();
        /** CrearLolla
         * Precondicion: Todos los puestos deben
         * tener el mismo precio para los mismos items,
         * ninguno vendió, y ni las personas ni
         * los puestos pueden ser vacios.
         * 
         * Complejidad: O(I^2 P + (I log I) + A (I*P + log A))
         * */
        Lollapatuza(const diccLog<IdPuesto, Puesto>& puestos, const set<Persona>& personas);
        
        // Operador de asignación
        Lollapatuza& operator=(const Lollapatuza& lolla);

        /** RegistrarCompra
         * Precondicion: La persona y el puesto deben ser
         * validos, y el puesto debe tener suficiente stock.
         * 
         * Complejidad: O(log A + log I + log P + log cant)
         */
        void registrarCompra(IdPuesto pid, Persona persona, Producto item, Cantidad cant);

        /** Hackear
         * Precondicion: La persona consumio sin promo en algun puesto
         * Complejidad: O(log A + log I)
        */
        void hackear(Persona persona, Producto item);

        /** GastoTotalPersona
         * Precondicion: La persona debe ser valida
         * Complejidad: O(log A)
        */
        Dinero gastoTotalPersona(Persona persona) const;

        /** PersonaMayorGasto
         * Precondicion: Deben haber personas en el festibal
         * Complejidad: O(1)
        */
        Persona personaMayorGasto() const;

        /** MenorStock
         * Precondicion: El puesto existe y vende el item.
         * Complejidad: O(P log I)
        */
        IdPuesto menorStock(Producto item) const;

        /** ObtenerPersonas
         * Precondicion: Ninguna
         * Complejidad: O(1)
        */
        const set<Persona>& obtenerPersonas() const;

        /** ObtenerPuestos
         * Precondicion: Ninguna
         * Complejidad: O(1)
        */
        const diccLog<IdPuesto, Puesto>& obtenerPuestos();

    // Funciones no presentes directamente en el TP2, pero utilizadas
    // para el adecuado funcionamiento de fachada_lollapatuza.h
    Nat stockEnPuesto(IdPuesto idPuesto, const Producto& producto) const;
    Nat descuentoEnPuesto(IdPuesto idPuesto, const Producto& producto, Nat cantidad) const;
    Nat gastoEnPuesto(IdPuesto idPuesto, Persona persona) const;
    set<IdPuesto> idsDePuestos() const;

    private:
    struct infoCompras {
        Dinero gastoTotal;
        diccLog<Producto, minHeap> hackeables;

        infoCompras();
        infoCompras(Dinero gastoTotal, diccLog<Producto, minHeap> hackeables);  
    };
        /** idMaximo (privado)
         * Precondicion: Deben haber personas en el festival.
         * Complejidad: O(A)
         * Descripcion: Devuelve el ID maximo de todas las personas.
        */
        Persona idMaximo(const set<Persona>& p);

        /* estrLolla */
        diccLog<IdPuesto, Puesto> _puestos;
        diccLog<Persona, infoCompras> _infoPersonas;
        maxHeap _gastosPersonas;
        set<Persona> _personas;
};

#endif //LOLLAPATUZA