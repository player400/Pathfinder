#pragma once

#include "MapElement.h"
#include "Path.h"
#include "Connection.h"
#include "QuickTree.h"
#include "ListNode.h"

class Town : public Path
{
private:
	Vector<char>* name;
	Vector<Connection*>* connections;

	static ListNode<Connection*>* add_to_list(Connection* needle, ListNode<Connection*>* root);

public:
	//This flag is in the Town class instead of Connection struct for optimization (avoiding unnecesarry searches)
	bool dijkstra_search_executed = false;

	void push_back_name(char letter);
	void print() const;
	char* get_name() const;
	void add_connection(int distance, Town* destination);
	//This is the main function that executes Dijkstra algorithm for a given town.
	void update_paths(Vector<Connection*>* visited, ListNode<Connection*>* to_search, QuickTree< ListNode<Connection*>*>*search_tree, Connection* connection_to_source);
	//For the Town, this function never actually adds object to the queue, but adds a connection to the source town.
	void add_to_queue( Queue<Connection>* queue, int distance, Town* source, Vector<Connection>*visited);
	Town(Coords position);
	~Town();
};
