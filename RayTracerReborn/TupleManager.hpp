#ifndef TUPLE_MANAGER_H
#include "Tuple.hpp"



 class TupleManager {
public:
	TupleManager();

public:
	static void Point(Tuple& tuple);
	static void Vector(Tuple& tuple);
public:
	static void Init();
	static void Shutdown();
	static TupleManager* Instance();

};

static TupleManager* g_tuple_manger;
#endif // !TUPLE_MANAGER_H
