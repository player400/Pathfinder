#pragma once

#include <iostream>

#define ASCI_TABLE_SIZE 128

template<typename T>
class QuickTree
{
private:
	template<typename T>
	class Node
	{
	private:
		T data = NULL;
		Node<T>* children[ASCI_TABLE_SIZE];

	public:
		void append(const char* key, int offset, T data)
		{
			if (key[offset] == '\0')
			{
				this->data = data;
				return;
			}
			if (children[key[offset]] != nullptr)
			{
				children[key[offset]]->append(key, offset + 1, data);
				return;
			}
			Node* new_node = new Node<T>;
			children[key[offset]] = new_node;
			new_node->append(key, offset + 1, data);
		}

		T get_data(const char* key, int offset)
		{
			if (key[offset] == '\0')
			{
				return data;
			}
			if (children[key[offset]] != nullptr)
			{
				return children[key[offset]]->get_data(key, offset + 1);
			}
			return NULL;
		}

		Node():children()
		{
		}

		~Node()
		{
			for (int i = 0; i < ASCI_TABLE_SIZE; i++)
			{
				if (children[i] != nullptr)
				{
					delete children[i];
				}
			}
		}
	};

	Node<T>* root;
	int size=0;

public:
	int get_size()
	{
		return size;
	}

	void add(T data, const char* key)
	{
		root->append(key, 0, data);
		size++;
	}

	T get_data(const char* key)
	{
		return root->get_data(key, 0);
	}

	QuickTree()
	{
		root = new Node<T>;
	}

	~QuickTree()
	{
		delete root;
	}
};

