#include "TupleManager.hpp"


TupleManager::TupleManager()
{
}

void TupleManager::Point(Tuple& tuple)
{
	tuple.SetW(1.0f);
}

void TupleManager::Vector(Tuple& tuple)
{
	tuple.SetW(0.0f);
}

void TupleManager::Point(Tuple& tuple, float x, float y, float z)
{
	tuple.SetW(1.0f);
}

void TupleManager::Vector(Tuple& tuple, float x, float y, float z)
{
	tuple.SetW(0.0f);
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
