#pragma once

#include <iostream>

//Single node of a list. There's no container for the whole list.
template<typename T>
class ListNode
{
public:
	ListNode<T>* next = nullptr;
	ListNode<T>* previous = nullptr;
	T data;

	void insert_after(T data)
	{
		if (next == nullptr)
		{
			next = new ListNode<T>(data, this);
		}
		else
		{
			ListNode<T>* new_node = new ListNode<T>(data, this);
			new_node->next = next;
			next->previous = new_node;
			next = new_node;
		}
	}

	bool is_not_last()
	{
		if (next == nullptr)
		{
			return false;
		}
		return true;
	}

	ListNode(T data, ListNode<T>* previous)
	{
		this->data = data;
		this->previous = previous;
	}

	//Destructor ties back the list
	~ListNode()
	{
		if (previous!=nullptr)
		{
			previous->next = next;
		}
		if (next != nullptr)
		{
			next->previous = previous;
		}
	}
};