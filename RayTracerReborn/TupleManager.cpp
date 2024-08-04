#include "TupleManager.hpp"


TupleManager::TupleManager() {
}
// CHOSE TO PASS IN REFERENCES INSTEAD OF RETURNING POINTERS
void TupleManager::Point(Tuple& tuple) const {
	tuple.SetW(1.0f);
}

void TupleManager::Vector(Tuple& tuple) const {
	tuple.SetW(0.0f);
}

void TupleManager::Point(Tuple& tuple, float x, float y, float z) const {
	tuple.SetX(x);
	tuple.SetY(y);
	tuple.SetZ(z);
	tuple.SetW(1.0f);
}

void TupleManager::Vector(Tuple& tuple, float x, float y, float z) const {
	tuple.SetX(x);
	tuple.SetY(y);
	tuple.SetZ(z);
	tuple.SetW(0.0f);
}

// ONLY USING ONE INSTANCE OF TUPLE MANAGER THAT WAY IF IT IS INCLUDED ANY CLASS CAN ACCESS IT
void TupleManager::Init() {
	g_tuple_manger = new TupleManager();
}

void TupleManager::Shutdown() {
	delete g_tuple_manger;
	g_tuple_manger = nullptr;
}

TupleManager* TupleManager::Instance() {
	return g_tuple_manger;
}

void TupleManager::CreationTest() {
	Tuple default_test_p, default_test_v, param_test_p, param_test_v;
	TupleManager::Instance()->Point(default_test_p);
	TupleManager::Instance()->Vector(default_test_v);
	TupleManager::Instance()->Point(param_test_p, 1.0f, 1.0f, 1.0f);
	TupleManager::Instance()->Vector(param_test_v, 1.0f, 1.0f, 1.0f);

	Tuple param_test_success_v(1.0f, 1.0f, 1.0f, 0.0f), param_test_success_p(1.0f, 1.0f, 1.0f, 1.0f);


	if (!(default_test_p.IsPoint())) {
		std::cout << "DEFAULT INITIALIZATION OF POINT FAILED" << std::endl;
		return;
	} else if (default_test_v.IsPoint()) {
		std::cout << "DEFAULT INITIALIZATION OF VECTOR FAILED" << std::endl;
		return;
	}

	if (!(param_test_p == param_test_success_p)) {
		std::cout << "PARAM INITIALIZATION OF POINT FAILED" << std::endl;
		return;
	} else if (!(param_test_v == param_test_success_v)) {
		std::cout << "PARAM INITIALIZATION OF VECTOR FAILED" << std::endl;
		return;
	} else {
		std::cout << "TUPLE FACTORY TEST PASSED" << std::endl;
	}
}
