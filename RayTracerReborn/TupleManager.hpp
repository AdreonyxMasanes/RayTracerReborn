#ifndef TUPLE_MANAGER_H
#define TUPLE_MANAGER_H
#include "Tuple.hpp"



class TupleManager {
public:
	TupleManager();

public:
	// DEFAULT CONSTRUCTOS
	Tuple Point() const;
	Tuple Vector() const;
	Tuple Color() const;
	// SPECIFIC CONSTRUCTORS
	Tuple Point(float x, float y, float z) const;
	Tuple Vector(float x, float y, float z) const;
	Tuple Color(float r, float g, float b) const;
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
