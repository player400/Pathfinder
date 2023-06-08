#pragma once

class Map
{
private:
	Vector<Town*> towns;
	MapElement*** map;

public:
	const Coords size;

	void add_town(Town* town)
	{
		towns.push_back(town);
	}

	void add_to_map(MapElement* new_element)
	{
		map[new_element->position.height][new_element->position.width] = new_element;
	}

	//Executes BFS algorithm by propagating from each town.
	void find_direct_connections(TownGraph* graph)
	{
		Queue<Connection>* queue = new Queue<Connection>;
		Vector<Connection>* visited = new Vector<Connection>;
		for (int i = 0; i < towns.get_size(); i++)
		{
			Town* town = towns.get(i);
			//Reusing containers for optimization (less reallocation)
			queue->clear();
			visited->clear();
			//Doing BFS until queue is empty
			town->propagate(map, queue, size, 0, town, visited);
			while (queue->get_size() > 0)
			{
				Connection current = queue->pop();
				current.destination->propagate(map, queue, size, current.distance, town, visited);
			}
			//Resetting flags for visisted map elements
			for (int i = 0; i < visited->get_size(); i++)
			{
				visited->get(i).destination->visited = false;
			}
		}
		delete queue;
		delete visited;
	}

	Map(Coords size) :size(size)
	{
		map = (MapElement***)malloc(sizeof(MapElement**) * size.height);
		for (int i = 0; i < size.height; i++)
		{
			map[i] = (MapElement**)malloc(sizeof(MapElement*) * size.width);
		}
	}
};