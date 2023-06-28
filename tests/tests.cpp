#include "gtest-1.8.1/gtest.h"
#include "../src/auxiliares.h"
#include "../src/max_heap.h"
#include "../src/min_heap.h"
#include "../src/heap_aux.h"

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

TEST(testsPuestos, Primero) {
	EXPECT_EQ(1,1);
}

TEST(testsLolla, Primero) {
	EXPECT_EQ(1,1);
}

TEST(testsMaxHeap, Primero) {
	maxHeap h = {1, 123456};
	h.agregar(Nodo(89, 123456));
	EXPECT_EQ(h.maximo(), 123456);
}

TEST(testsMaxHeap, Multiples) {
	maxHeap h = {4, 13};
	h.agregar(Nodo(67, 10));
	h.agregar(Nodo(66, 11));
	h.agregar(Nodo(65, 12));
	h.agregar(Nodo(1, 13));
	EXPECT_EQ(h.maximo(), 10);
}

// -------------------------------------------------------------------------------------------
// FIXME: puesto no tiene un constructor default
class PuestoTest : public testing::Test {
protected:
    Menu menu = {{8, 300}, {9, 811}, {13, 1000}, {15, 127}};
    set<Persona> personas34, personas67;
    set<Persona> personas = {3, 4, 6, 7};
    set<IdPuesto> idsPuestos = {1, 2, 3};
    
    Stock stock1 = {{8, 17}, {9, 5}, {13, 27}, {15, 30}};
	Puesto puesto1 = {menu, stock1, descuentos1};
    Promociones descuentos1 = {{8, {{3, 10}, {7, 25}}}};
    
    Stock stock2 = {{8, 21}, {9, 39}, {13, 11}, {15, 9}};
	Puesto puesto2 = {menu, stock2, descuentos2};
    Promociones descuentos2 = {{9, {{4, 12}}}, {15, {{4, 23}}}};
    
    Stock stock3 = {{8, 40}, {9, 12}, {13, 2}, {15, 91}};
	Puesto puesto3 = {menu, stock3, descuentos3};
    Promociones descuentos3 = {{13, {{7, 19}}}};

    map<IdPuesto, Puesto> puestos = {{1, puesto1}, {2, puesto2}, {3, puesto3}};;
};

TEST_F(PuestoTest, crearPuesto){
    EXPECT_EQ(puesto1.obtenerStock(8), 17);
    EXPECT_EQ(puesto1.obtenerStock(9), 5);
    EXPECT_EQ(puesto1.obtenerStock(13), 27);
    EXPECT_EQ(puesto1.obtenerStock(15), 30);
}

// -------------------------------------------------------------------------------------------


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
