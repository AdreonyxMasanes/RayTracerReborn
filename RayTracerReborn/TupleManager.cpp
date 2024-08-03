#include "TupleManager.hpp"


TupleManager::TupleManager()
{
}

void TupleManager::Point(Tuple& tuple)
{
}

void TupleManager::Vector(Tuple& tuple)
{
}

// ONLY USING ONE INSTANCE OF TUPLE MANAGER THAT WAY IF IT IS INCLUDED ANY CLASS CAN ACCESS IT
void TupleManager::Init()
{
	g_tuple_manger = new TupleManager();
}

void TupleManager::Shutdown()
{
	delete g_tuple_manger;
	g_tuple_manger = nullptr;
}

TupleManager* TupleManager::Instance()
{
	return g_tuple_manger;
}
