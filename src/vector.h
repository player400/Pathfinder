#pragma once

#include <iostream>
#define INIT_VECTOR_CAP 2

template<typename T>
class Vector
{
private:
	T* buffer = nullptr;
	int capacity;
	int size;

public:
	int get_size()
	{
		return size;
	}

	//FUNKCJA ZWRACA WSKAZNIK DO ZAWARTOSCI WEKTORA, ABY MOZNA BYLÅO ODNIESC SIEò DO NIEGO POZA KLASA
	T* get_ptr()
	{
		return buffer;
	}

	T get(int index) const
	{
		return buffer[index];
	}

	void clear()
	{
		size = 0;
	}

	void remove(int index)
	{
		size--;
		for (int i = index; i < size; i++)
		{
			buffer[i] = buffer[i + 1];
		}
	}

	bool contains(T needle)
	{
		for (int i = 0; i < size; i++)
		{
			if (buffer[i] == needle)
			{
				return true;
			}
		}
		return false;
	}

	void set_vector(T* array, int array_size)
	{
		free(buffer);
		buffer = (T*)malloc(array_size(sizeof(T)));
		for (int i = 0; i < array_size; i++)
		{
			buffer[i] = array[i];
		}
		size = array_size;
		capacity = array_size;
	}

	//FUNKCJA SPRAWDZA CZY JEST JESZCZE MIEJSCE W WEKTORZE, JESLI NIE DO POWIEKSZA GO DWUKROTNIE. NASTEòPNIE ZAPISUJE ELEMENT NA KONÉCU WEKTORA
	void push_back(T new_item)
	{
		if (size < capacity)
		{
			buffer[size] = new_item;
		}
		else
		{
			T* temp_buffer = (T*)malloc(sizeof(T) * capacity * 2);
			memcpy(temp_buffer, buffer, capacity * sizeof(T));
			temp_buffer[size] = new_item;
			capacity = capacity * 2;
			free(buffer);
			buffer = (T*)malloc(sizeof(T) * capacity);
			memcpy(buffer, temp_buffer, capacity * sizeof(T));
			free(temp_buffer);
		}
		size++;
	}

	//FUNKCJA EFEKTYWNIE USUWA OSTATNI ELEMENT WEKTORA (POD WARUNKIEM, ZE WEKTOR MA ROZMIAR WIEòKSZY OD 0)
	void pop_back()
	{
		if (size > 0)
		{
			size--;
		}
	}


	Vector()
	{
		size = 0;
		capacity = INIT_VECTOR_CAP;
		buffer = (T*)malloc(sizeof(T) * INIT_VECTOR_CAP);
	}

	Vector(const Vector<T>& copy)
	{
		size = copy.size;
		capacity = copy.capacity;
		buffer = (T*)malloc(sizeof(T) * capacity);
		for (int i = 0; i < size; i++)
		{
			buffer[i] = copy.buffer[i];
		}
	}

	~Vector()
	{
		buffer = (T*)malloc(sizeof(T) * INIT_VECTOR_CAP);
		free(buffer);
	}
};