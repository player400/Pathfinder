#pragma once

#define INIT_QUEUE_CAP 2

template<typename T>
class Queue
{
protected:
	int capacity;
	int size;
	T* buffer = nullptr;

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

	Queue()
	{
		size = 0;
		capacity = INIT_QUEUE_CAP;
		buffer = (T*)malloc(sizeof(T) * INIT_QUEUE_CAP);
	}

	~Queue()
	{
		free(buffer);
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

	T pop()
	{

		T result = buffer[0];
		for (int i = 0; i < size - 1; i++)
		{
			buffer[i] = buffer[i + 1];
		}
		size--;
		return result;
	}
};