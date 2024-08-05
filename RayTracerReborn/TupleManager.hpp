#ifndef TUPLE_MANAGER_H
#define TUPLE_MANAGER_H
#include "Tuple.hpp"



class TupleManager {
public:
	TupleManager();

public:
	// DEFAULT CONSTRUCTOS
	std::unique_ptr<Tuple> Point() const;
	std::unique_ptr<Tuple> Vector() const;
	std::unique_ptr<Tuple> Color() const;
	// SPECIFIC CONSTRUCTORS
	std::unique_ptr<Tuple> Point(float x, float y, float z) const;
	std::unique_ptr<Tuple> Vector(float x, float y, float z) const;
	std::unique_ptr<Tuple> Color(float r, float g, float b) const;
	// GET FUNCTION
	static TupleManager* Instance();

	// LIFETIME MANAGER FUNCTIONS
public:
	static void Init();
	static void Shutdown();

	// TEST FUNCTIONS
public:
	static void CreationTest();

};

static TupleManager* g_tuple_manger;
#endif // !TUPLE_MANAGER_H
