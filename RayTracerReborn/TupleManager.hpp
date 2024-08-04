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
	// SPECIFIC CONSTRUCTORS
	void Point(Tuple& tuple, float x, float y, float z) const;
	void Vector(Tuple& tuple, float x, float y, float z) const;
public:
	static void Init();
	static void Shutdown();
	static TupleManager* Instance();

	static void CreationTest();

};

static TupleManager* g_tuple_manger;
#endif // !TUPLE_MANAGER_H
