#pragma once

#include "MapElement.h"

class Town;

class Path : public MapElement
{
public:
	//A flag indicating if the Path was visited in BFS and if the town was visited in Dijkstra
	bool visited = false;

	void add_to_queue(Queue<Connection>* queue, int distance, Town* source, Vector<Connection>*visited);
	//Path will propagate, by calling ,,add to queue" method on all surrounding elements. Those elements will decide what to do with it (add themselves to the queue or not). 
	//Town inherites this method, but the only Town it should be used for is the source town in BFS (because towns will not add themselves to queue)
	virtual void propagate(MapElement*** map, Queue<Connection>* queue, Coords map_size, int distance, Town* source, Vector<Connection>*visited);
	using MapElement::MapElement;
};