#include "TupleManager.hpp"


TupleManager::TupleManager() {
}
// CHOSE TO PASS IN REFERENCES INSTEAD OF RETURNING POINTERS
std::unique_ptr<Tuple> TupleManager::Point() const {
	return std::make_unique<Tuple>(0.0f, 0.0f, 0.0f, 1.0f);
}

std::unique_ptr<Tuple> TupleManager::Vector() const {
	return std::make_unique<Tuple>(0.0f, 0.0f, 0.0f, 0.0f);
}

std::unique_ptr<Tuple> TupleManager::Color() const {
	return std::make_unique<Tuple>(0.0f, 0.0f, 0.0f, 0.0f);
}

std::unique_ptr<Tuple> TupleManager::Point(float x, float y, float z) const {
	return std::make_unique<Tuple>(x, y, z, 1.0f);
}

std::unique_ptr<Tuple> TupleManager::Vector(float x, float y, float z) const {
	return std::make_unique<Tuple>(x, y, z, 0.0f);
}

std::unique_ptr<Tuple> TupleManager::Color(float r, float g, float b) const {
	return std::make_unique<Tuple>(r, g, b, 0.0f);
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
	std::unique_ptr<Tuple> default_test_p, default_test_v, param_test_p, param_test_v;
	default_test_p = TupleManager::Instance()->Point();
	default_test_v = TupleManager::Instance()->Vector();
	param_test_p = TupleManager::Instance()->Point(1.0f, 1.0f, 1.0f);
	param_test_v = TupleManager::Instance()->Vector(1.0f, 1.0f, 1.0f);

	Tuple param_test_success_v(1.0f, 1.0f, 1.0f, 0.0f), param_test_success_p(1.0f, 1.0f, 1.0f, 1.0f);


	if (!(default_test_p->IsPoint())) {
		std::cout << "DEFAULT INITIALIZATION OF POINT FAILED" << std::endl;
		return;
	} else if (default_test_v->IsPoint()) {
		std::cout << "DEFAULT INITIALIZATION OF VECTOR FAILED" << std::endl;
		return;
	}

	if (!(*param_test_p == param_test_success_p)) {
		std::cout << "PARAM INITIALIZATION OF POINT FAILED" << std::endl;
		return;
	} else if (!(*param_test_v == param_test_success_v)) {
		std::cout << "PARAM INITIALIZATION OF VECTOR FAILED" << std::endl;
		return;
	} else {
		std::cout << "TUPLE FACTORY TEST PASSED" << std::endl;
	}
}
