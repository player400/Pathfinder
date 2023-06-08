#pragma once

#include "MapElement.h"

class Town;

class Field : public MapElement
{
public:
	using MapElement::MapElement;
	void add_to_queue(Queue<Connection>* queue, int distance, Town* source, Vector<Connection>*visited);
};