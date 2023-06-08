#pragma once

#include "vector.h"
#include "QuickTree.h"
#include "Queue.h"
#include "ListNode.h"

#include "Field.h"
#include "Town.h"


class TownGraph
{
private:
	QuickTree<Town*> town_tree;

public:
	void add_town(Town* new_town)
	{
		town_tree.add(new_town, new_town->get_name());
	}

	Town* find_town(const char* name)
	{
		return town_tree.get_data(name);
	}

	void pathfind(Town* source, Town* target, int display_path)
	{
		//If source is also the target the algorith is not executed (optimization)
		if (source == target)
		{
			cout << 0 << endl;
			return;
		}
		//Vector of temporary Connection objects with all visited Towns (purely to know wchich towns's flags should be reset and to have a list of objects to destroy)
		Vector<Connection*> visited;
		//True for searching throught the list
		QuickTree<ListNode<Connection*>*> search_tree;
		//Creating temporary Connection object for the source Town (each visisted Town gets one, flags are stored in the Town object itself, but other data needed for Dijkstra algorithm is stored in a temporary object).
		Connection* src = new Connection;
		src->destination = source;
		source->dijkstra_search_executed = true;
		src->distance = 0;
		src->path = nullptr;
		ListNode<Connection*> to_search_root(src, nullptr);
		search_tree.add(&to_search_root, source->get_name());
		ListNode<Connection*>* current_root = &to_search_root;
		visited.push_back(src);
		source->visited = true;
		source->update_paths(&visited, &to_search_root, &search_tree, src);
		//Instead of removing first element of the list, a temporary pointer is moved along it. The loop stops, when the temporary pointer reaches the end of the list.
		while (current_root->is_not_last())
		{
			//Next object is pulled (part of the list following the temporary pointer is always sorted).
			Connection* current = current_root->next->data;
			Town* town = (Town*)current->destination;
			if (town == target)
			{
				break;
			}
			//Moving the temporary pointer
			current_root = current_root->next;
			//Setting the flag
			town->dijkstra_search_executed = true;
			//Temporary pointer is passed as parameter to the main function doing the Dijkstra algorithm
			town->update_paths(&visited, current_root, &search_tree, current);
		}
		Connection* final = search_tree.get_data(target->get_name())->data;
		cout << final->distance;
		if (display_path)
		{
			Vector<Connection*> best_path;
			Connection* current = final->path;
			while (true)
			{
				best_path.push_back(current);
				if (current->path == nullptr)
				{
					break;
				}
				current = current->path;
			}
			for (int i = best_path.get_size() - 2; i >= 0; i--)
			{
				cout << " ";
				((Town*)best_path.get(i)->destination)->print();
			}
		}
		cout << endl;
		//Resetting the flags in the Town objects (the ones that are in Towns for optimization) and deleting temporary Connection objects
		for (int i = 0; i < visited.get_size(); i++)
		{
			visited.get(i)->destination->visited = false;
			((Town*)visited.get(i)->destination)->dijkstra_search_executed = false;
			delete visited.get(i);
		}
		source->visited = false;
		source->dijkstra_search_executed = false;
		//Deleting the list
		while (to_search_root.is_not_last())
		{
			delete to_search_root.next;
		}
	}

	static void read_word(Vector<char>* word)
	{
		word->clear();
		char c = getchar();
		while (c <= ' ')
		{
			c = getchar();
		}
		while (c > ' ')
		{
			word->push_back(c);
			c = getchar();
		}
		word->push_back('\0');
	}

	void read_air_connections()
	{
		int n;
		scanf("%d", &n);
		Vector<char> word;
		for (int i = 0; i < n; i++)
		{
			int distance;
			read_word(&word);
			Town* source = find_town(word.get_ptr());
			read_word(&word);
			Town* target = find_town(word.get_ptr());
			scanf("%d", &distance);
			source->add_connection(distance - 1, target);
		}
	}

	void read_paths()
	{
		int n;
		scanf("%d", &n);
		Vector<char>word;
		for (int i = 0; i < n; i++)
		{
			int show_path;
			read_word(&word);
			Town* src = find_town(word.get_ptr());
			read_word(&word);
			Town* dst = find_town(word.get_ptr());
			scanf("%d", &show_path);
			pathfind(src, dst, show_path);
		}
	}
};