#include "gtest-1.8.1/gtest.h"
#include "../src/auxiliares.h"
#include "../src/heap/heap.h"
#include "../src/lollapatuza.h"

TEST(testsAuxiliares, binary_search_tipico) {
    vector<Nat> A = {5, 6, 9, 10, 20, 37, 38, 41, 42, 49};
    for (int i = 0; i < A.size(); i++) EXPECT_EQ(busquedaBinaria(A, A[i], 0, 10), i);
}

TEST(testsAuxiliares, binary_search_step) {
    vector<Nat> A = {1, 50, 100};
    for (int x = 0; x < 50; x++)    EXPECT_EQ(busquedaBinaria(A, x, 0, 3), 0);
    for (int x = 50; x < 99; x++)   EXPECT_EQ(busquedaBinaria(A, x, 0, 3), 1);
    for (int x = 100; x < 150; x++) EXPECT_EQ(busquedaBinaria(A, x, 0, 3), 2);
}

TEST(testsAuxiliares, merge_tipico) {
    vector<Nat> A = {3, 4, 5, 6, 7, 15, 27, 29, 46, 49};
    vector<Nat> B = {1, 2, 9, 13, 17, 20, 28, 35, 47, 50};
    vector<Nat> C = {1, 2, 3, 4, 5, 6, 7, 9, 13, 15, 17, 20,
                     27, 28, 29, 35, 46, 47, 49, 50};

    EXPECT_EQ(merge(A, B), C);
    EXPECT_EQ(merge(B, A), C);
}

TEST(testsAuxiliares, merge_sort_desordenada) {
    vector<Nat> A = {38, 8, 3, 23, 6, 41, 2, 47, 49, 36};
    vector<Nat> R = {2, 3, 6, 8, 23, 36, 38, 41, 47, 49};
    EXPECT_EQ(mergeSort(A), R);
}

TEST(testsAuxiliares, merge_sort_reves) {
    vector<Nat> A = {50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40,
                     39, 38, 37, 36, 35, 34, 33, 32, 31, 30,
                     29, 28, 27, 26, 25, 24, 23, 22, 21, 20,
                     19, 18, 17, 16, 15, 14, 13, 12, 11, 10,
                     9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    vector<Nat> R = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                     11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                     21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                     31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
                     41, 42, 43, 44, 45, 46, 47, 48, 49, 50};

    EXPECT_EQ(mergeSort(A), R);
}

TEST(testsAuxiliares, merge_sort_ordenados) {
    vector<Nat> A = {0, 7, 8, 13, 22, 23, 33, 34, 35, 36,
                     40, 52, 61, 65, 70, 74, 77, 85, 95, 97};

    EXPECT_EQ(mergeSort(A), A);
}

class MaxHeapTest : public testing::Test {
protected:
    const Nat n = 20;
    const Nat maxid = 30;
    maxHeap h;

    void SetUp() override {
        h = maxHeap(n, maxid);

        for (int i = 0; i <= 10; i++) {
            h.agregar(Nodo(i, i));
        }

        h.agregar(Nodo(80, 28));
        h.agregar(Nodo(100, 29));
        h.agregar(Nodo(100, 30));
    }
};

TEST_F(MaxHeapTest, Maximo) {
    EXPECT_EQ(h.maximo(), 29);
}

TEST_F(MaxHeapTest, RemoverMaximo) {
    h.removerMaximo();
    EXPECT_EQ(h.maximo(), 30);
    h.removerMaximo();
    EXPECT_EQ(h.maximo(), 28);
}

TEST_F(MaxHeapTest, ModificarGasto) {
    h.modificarGasto(29, 0);
    h.modificarGasto(30, 0);
    EXPECT_EQ(h.maximo(), 28);
    h.modificarGasto(10, 1000);
    EXPECT_EQ(h.maximo(), 10);
    h.modificarGasto(5, 20);
    EXPECT_EQ(h.maximo(), 10);
}

class MinHeapTest : public testing::Test {
protected:
    const Nat n = 20;
    minHeap h;
    Puesto p1, p2, p3;

    Menu menu;
    set<IdPuesto> idsPuestos;
    Stock stock1, stock2, stock3;
    Promociones descuentos1, descuentos2, descuentos3;
    Puesto puesto1, puesto2, puesto3;

    void SetUp() override {
        h = minHeap(n);

        menu = {{8, 300}, {9, 811}, {13, 1000}, {15, 127}};
        idsPuestos = {1, 2, 3};

        stock1 = {{8, 17}, {9, 5}, {13, 27}, {15, 30}};
        descuentos1 = {{8, {{3, 10}, {7, 25}}}};
        puesto1 = {menu, stock1, descuentos1};

        stock2 = {{8, 21}, {9, 39}, {13, 11}, {15, 9}};
        descuentos2 = {{9, {{4, 12}}}, {15, {{4, 23}}}};
        puesto2 = {menu, stock2, descuentos2};

        stock3 = {{8, 40}, {9, 12}, {13, 2}, {15, 91}};
        descuentos3 = {{13, {{7, 19}}}};
        puesto3 = {menu, stock3, descuentos3};

        h.agregar(TupPuesto(3, &puesto3));
        h.agregar(TupPuesto(1, &puesto1));
        h.agregar(TupPuesto(2, &puesto2));
    }
};

TEST_F(MinHeapTest, Minimo) {
    EXPECT_TRUE(h.minimo() == &puesto1);
}

TEST_F(MinHeapTest, RemoverMinimo) {
    h.removerMinimo();
    EXPECT_TRUE(h.minimo() == &puesto2);
}

// -------------------------------------------------------------------------------------------
class PuestoTest : public testing::Test {
protected:
    Menu menu;
    set<Persona> personas;
    set<IdPuesto> idsPuestos;
    Stock stock1, stock2, stock3, stock4;
    Promociones descuentos1, descuentos2, descuentos3, descuentos4;
    Puesto puesto1, puesto2, puesto3, puesto4;
    map<IdPuesto, Puesto> puestos;

    void SetUp() override {
        menu = {{8, 300}, {9, 811}, {13, 1000}, {15, 127}};
        personas = {3, 4, 6, 7};
        idsPuestos = {1, 2, 3};

        stock1 = {{8, 17}, {9, 5}, {13, 27}, {15, 30}};
        descuentos1 = {{8, {{3, 10}, {7, 25}}}};
        puesto1 = {menu, stock1, descuentos1};

        stock2 = {{8, 21}, {9, 39}, {13, 11}, {15, 9}};
        descuentos2 = {{9, {{4, 12}}}, {15, {{4, 23}}}};
        puesto2 = {menu, stock2, descuentos2};

        stock3 = {{8, 40}, {9, 12}, {13, 20}, {15, 91}};
        descuentos3 = {{13, {{7, 19}}}};
        puesto3 = {menu, stock3, descuentos3};

        stock4 = {{8,10}};
        descuentos4 = {};
        puesto4 = {menu, stock4, descuentos4};

        puestos = {{1, puesto1}, {2, puesto2}, {3, puesto3}};
    }
};




TEST_F(PuestoTest, obtenerStock){
    EXPECT_EQ(puesto1.obtenerStock(8), 17);
    EXPECT_EQ(puesto1.obtenerStock(9), 5);
    EXPECT_EQ(puesto2.obtenerStock(13), 11);
    EXPECT_EQ(puesto3.obtenerStock(15), 91);
    EXPECT_FALSE(puesto1.obtenerStock(15) == 22);
    EXPECT_FALSE(puesto2.obtenerStock(8) == 10);
    EXPECT_FALSE(puesto3.obtenerStock(9) == 25);


}

TEST_F(PuestoTest, obtenerDescuento){
    EXPECT_EQ(puesto1.obtenerDescuento(8, 2), 0);
    EXPECT_EQ(puesto1.obtenerDescuento(9, 2), 0);
    EXPECT_EQ(puesto1.obtenerDescuento(8, 3), 10);
    EXPECT_EQ(puesto1.obtenerDescuento(8, 6), 10);
    EXPECT_EQ(puesto1.obtenerDescuento(8, 10), 25);
    EXPECT_EQ(puesto2.obtenerDescuento(9, 4), 12);
    EXPECT_FALSE(puesto2.obtenerDescuento(9, 4) == 16);
    EXPECT_EQ(puesto2.obtenerDescuento(9, 10), 12);
    EXPECT_EQ(puesto2.obtenerDescuento(15, 7), 23);
}

TEST_F(PuestoTest, obtenerGasto){
    puesto1.vender(3, 8, 2);
    EXPECT_EQ(puesto1.obtenerGasto(3), 600);
    puesto1.vender(3, 8, 3);
    EXPECT_FALSE(puesto1.obtenerGasto(3) == 1409);
    EXPECT_EQ(puesto1.obtenerGasto(3), 1410);

    puesto2.vender(4, 9, 3);
    puesto2.vender(4, 13, 2);
    EXPECT_EQ(puesto2.obtenerGasto(4), 4433);
    puesto2.vender(4, 9, 1);
    EXPECT_FALSE(puesto2.obtenerGasto(4) == 5000);
    EXPECT_EQ(puesto2.obtenerGasto(4), 5244);
}

TEST_F(PuestoTest, existeEnStock){
    EXPECT_TRUE(puesto1.existeEnStock(8));
    EXPECT_FALSE(puesto4.existeEnStock(13));
    EXPECT_TRUE(puesto2.existeEnStock(9));
}


TEST_F(PuestoTest, cantComprasSinDesc){
    EXPECT_EQ(puesto1.cantComprasSinDesc(1,9), 0);
    puesto1.vender(3, 8, 2);
    EXPECT_EQ(puesto1.cantComprasSinDesc(3,8), 1);
    puesto1.vender(3, 8, 1);
    EXPECT_EQ(puesto1.cantComprasSinDesc(3,8), 2);
    puesto1.vender(1, 13, 1);
    EXPECT_EQ(puesto1.cantComprasSinDesc(1,13), 1);
    EXPECT_EQ(puesto1.cantComprasSinDesc(1,8), 0);

    puesto3.vender(2, 15, 2);
    EXPECT_EQ(puesto3.cantComprasSinDesc(2, 15), 1);
    puesto3.vender(3, 15, 1);
    EXPECT_EQ(puesto3.cantComprasSinDesc(3, 15), 1);
    EXPECT_EQ(puesto3.cantComprasSinDesc(3, 8), 0);

    puesto2.vender(1, 9, 7);
    EXPECT_EQ(puesto2.cantComprasSinDesc(1,9), 0);
    puesto2.vender(2, 9, 6);
    puesto2.vender(2, 15, 2);
    EXPECT_EQ(puesto2.cantComprasSinDesc(1,9), 0);
    EXPECT_EQ(puesto2.cantComprasSinDesc(2, 15), 1);
}

TEST_F(PuestoTest, precioConDescuento){
    EXPECT_EQ(puesto1.precioConDescuento(8, 1), 300);
    EXPECT_EQ(puesto1.precioConDescuento(8,3), 810);
    EXPECT_FALSE(puesto1.precioConDescuento(8, 2) == 540);

    EXPECT_FALSE(puesto3.precioConDescuento(8, 2) == 100);
}

TEST_F(PuestoTest, precioSinDescuento){
    EXPECT_EQ(puesto1.precioSinDescuento(8, 2), 600);
    EXPECT_FALSE(puesto1.precioSinDescuento(8, 3) == 810);
    EXPECT_EQ(puesto1.precioSinDescuento(13, 2), 2000);

    EXPECT_EQ(puesto3.precioSinDescuento(15, 2), 254);

}

TEST_F(PuestoTest, obtener){
    EXPECT_EQ(puesto1.stock(), stock1);
    EXPECT_EQ(puesto2.stock(), stock2);
    EXPECT_FALSE(puesto3.stock() == stock1);

    EXPECT_EQ(puesto1.obtenerMenu(), menu);

    EXPECT_EQ(puesto1.promociones(), descuentos1);
    EXPECT_FALSE(puesto2.promociones() == descuentos3);

}


// -------------------------------------------------------------------------------------------



int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
