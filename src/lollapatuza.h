#ifndef LOLLAPATUZA
#define LOLLAPATUZA
#include <map>
#include <set>
#include <list>
#include <vector>
#include "tipos.h"
#include "puesto.h"

using namespace std;

class Lollapatuza {
    public:
        /** CrearLolla
         * Precondicion: Todos los puestos deben
         * tener el mismo precio para los mismos items,
         * ninguno vendió, y ni las personas ni
         * los puestos pueden ser vacios.
         * 
         * Complejidad: O(I^2 P + (I log I) + A (I*P + log A))
         * */
        Lollapatuza(diccLog<IdPuesto, Puesto> puestos, set<Persona> personas);

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
        Dinero gastoTotalPersona(Persona persona);

        /** PersonaMayorGasto
         * Precondicion: Deben haber personas en el festibal
         * Complejidad: O(1)
        */
        Persona personaMayorGasto();

        /** MenorStock
         * Precondicion: El puesto existe y vende el item.
         * Complejidad: O(P log I)
        */
        IdPuesto menorStock(Producto item);

        /** ObtenerPersonas
         * Precondicion: Ninguna
         * Complejidad: O(1)
        */
        set<Persona> obtenerPersonas();

        /** ObtenerPuestos
         * Precondicion: Ninguna
         * Complejidad: O(1)
        */
        diccLog<IdPuesto, Puesto> obtenerPuestos();
    
    private:
        /** idMaximo (privado)
         * Precondicion: Deben haber personas en el festival.
         * Complejidad: O(A)
         * Descripcion: Devuelve el ID maximo de todas las personas.
        */
        Persona idMaximo(set<Persona> p);

        /* infoCompras */
        struct infoCompras {
            Dinero gastoTotal;

            // FIXME: ACLARAR EL TIPO DEL MINHEAP
            diccLog<Producto, minHeap<Nat>> hackeables;
        };

        /* estrLolla */
        diccLog<IdPuesto, Puesto> puestos;
        diccLog<Persona, infoCompras> infoPersonas;

        // FIXME: ACLARAR EL TIPO DEL MAXHEAP
        maxHeap<Dinero> gastosPersonas;
};

#endif //LOLLAPATUZA