#ifndef TUPLE_MANAGER_H
#include "Tuple.hpp"



class TupleManager {
public:
	TupleManager();

public:
	// DEFAULT CONSTRUCTOS
	static void Point(Tuple& tuple);
	static void Vector(Tuple& tuple);
	// SPECIFIC CONSTRUCTORS
	static void Point(Tuple& tuple, float x, float y, float z);
	static void Vector(Tuple& tuple, float x, float y, float z);
public:
	static void Init();
	static void Shutdown();
	static TupleManager* Instance();

};

static TupleManager* g_tuple_manger;
#endif // !TUPLE_MANAGER_H
