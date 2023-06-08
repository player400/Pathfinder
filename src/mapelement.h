#pragma once

#include <iostream>

using namespace std;

#include "Queue.h"
#include "Coords.h"
#include "vector.h"
#include "Connection.h"

class Path;
class Town;

class MapElement
{
public:
	const Coords position;

	//Method for handling BFS. Depending on the type of the MapElement, it will add itself to queue or not
	virtual void add_to_queue(Queue<Connection>* queue, int distance, Town* source, Vector<Connection>*visited) = 0;
	MapElement(Coords position);
};