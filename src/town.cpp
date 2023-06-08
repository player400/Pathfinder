#include "Town.h"

void Town::push_back_name(char letter)
{
	name->push_back(letter);
}

void Town::print() const
{
	for (int i = 0; i < name->get_size()-1; i++)
	{
		cout << name->get(i);
	}
}

//This function adds element to the list in the right place (making sure that the list is sorted)
ListNode<Connection*>* Town::add_to_list(Connection* needle, ListNode<Connection*>* root)
{
	if (!(root->is_not_last()))
	{
		root->insert_after(needle);
		return root->next;
	}
	if (root->next->data->distance >= needle->distance)
	{
		root->insert_after(needle);
		return root->next;
	}
	ListNode<Connection*>* current = root;
	while (current->is_not_last())
	{
		current = current->next;
		if (current->data->distance <= needle->distance)
		{
			current->insert_after(needle);
			return current->next;
		}
	}
	current->insert_after(needle);
	return current->next;
}

void Town::update_paths(Vector<Connection*>* visited, ListNode<Connection*>* to_search, QuickTree<ListNode<Connection*>*>* search_tree, Connection* connection_to_source)
{
	//1 is added to the distance, because the town counts as a road.
	int distance = connection_to_source->distance + 1;
	//This loop goes through all direct connections of the town and updates distances to the source
	for (int i = 0; i < connections->get_size();i++)
	{
		Town* town = (Town*)connections->get(i)->destination;
		//If the town has not been visisted, a temporary Connection object is created for it and it's flags are set.
		if (town->visited == false)
		{
			town->visited = true;
			town->dijkstra_search_executed = false;
			Connection* new_connection = new Connection;
			new_connection->destination = town;
			new_connection->distance = distance + connections->get(i)->distance;
			new_connection->path = connection_to_source;
			//The object is added to the Visited vector (so the porgram knows to delete it later)
			visited->push_back(new_connection);
			//The town's object is also added to the list and pointer to this list element is saved in the trie for fast searching
			search_tree->add(add_to_list(new_connection, to_search), town->get_name());
		}
		//Because we are looking for distance to only one node of the graph, not all, we update visited town's distance only if it will have impact on the overall result (ie. only if this town did not uptade it's connections yet).
		else if (town->dijkstra_search_executed == false)
		{
			//Searching in the trie for the existing target town's Connection object (would be faster if all data was in the town instead of a temporary object, but this way there's less stuff to reset in the town itself (less bug - prone and cleaner code) and the trie is super-fast anyway)).
			ListNode<Connection*>* proper_node = search_tree->get_data(town->get_name());
			Connection* proper = proper_node->data;
			//If the new distance to a visisted town is smaller than the old distance, the distance is updated
			if (proper->distance > distance + connections->get(i)->distance)
			{
				proper->distance = distance + connections->get(i)->distance;
				proper->path = connection_to_source;
				//In order to keep the list sorted we check if after updating the Connection object is still in the right place. If it's not - we fix it by deleting this list node and adding the object again.
				if ((proper_node->is_not_last() && proper_node->next->data->distance < proper->distance) || (proper_node != to_search && proper_node->previous != to_search && proper_node->previous->data->distance > proper->distance))
				{
					delete proper_node;
					search_tree->add(add_to_list(proper, to_search), town->get_name());
				}
			}
		}
	}
}

char* Town::get_name() const
{
	return name->get_ptr();
}

void Town::add_connection(int distance, Town* destination)
{
	Connection* new_connection = new Connection;
	new_connection->distance = distance;
	new_connection->destination = destination;
	connections->push_back(new_connection);
}

void Town::add_to_queue(Queue<Connection>* queue, int distance, Town* source, Vector<Connection>*visisted)
{
	if (source == this)
	{
		return;
	}
	for (int i = 0; i < connections->get_size(); i++)
	{
		//If a connection to this town already exists
		if (connections->get(i)->destination == source)
		{
			//And if the new connection has smaller distance
			if (connections->get(i)->distance > distance)
			{
				//Overwrite the distance
				connections->get(i)->distance = distance;
			}
			return;
		}
	}
	add_connection(distance, source);
}

Town::Town(Coords position) :Path(position)
{
	name = new Vector<char>;
	connections = new Vector<Connection*>;
	dijkstra_search_executed = false;
}

Town::~Town()
{
	delete name;
	for (int i = 0; i < connections->get_size(); i++)
	{
		delete connections->get(i);
	}
	delete connections;
}
