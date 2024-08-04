#ifndef TUPLE_MANAGER_H
#define TUPLE_MANAGER_H
#include "Tuple.hpp"



class TupleManager {
public:
	TupleManager();

public:
	// DEFAULT CONSTRUCTOS
	void Point(Tuple& tuple) const;
	void Vector(Tuple& tuple) const;
	void Color(Tuple& tuple) const;
	// SPECIFIC CONSTRUCTORS
	void Point(Tuple& tuple, float x, float y, float z) const;
	void Vector(Tuple& tuple, float x, float y, float z) const;
	void Color(Tuple& tuple, float r, float g, float b) const;
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
