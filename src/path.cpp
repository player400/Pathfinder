#include "Path.h"
#include "Connection.h"
#include "Town.h"

void Path::add_to_queue(Queue<Connection>* queue, int distance, Town* source, Vector<Connection>*visited)
{
	Connection new_connection;
	new_connection.distance = distance+1;
	new_connection.destination = this;
	if (this->visited)
	{
		return;
	}
	queue->push_back(new_connection);
	visited->push_back(new_connection);
	this->visited = true;
}

void Path::propagate(MapElement*** map, Queue<Connection>* queue, Coords map_size, int distance, Town* source, Vector<Connection>*visited)
{
	if (position.width > 0)
	{
		map[position.height][position.width-1]->add_to_queue(queue, distance, source, visited);
	}
	if (position.width < map_size.width - 1)
	{
		map[position.height][position.width+1]->add_to_queue(queue, distance, source, visited);
	}
	if (position.height > 0)
	{
		map[position.height-1][position.width]->add_to_queue(queue, distance, source, visited);
	}
	if (position.height < map_size.height - 1)
	{
		map[position.height+1][position.width]->add_to_queue(queue, distance, source, visited);
	}
}


