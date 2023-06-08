#pragma once

class Path;

//Struct used for Dijkstra algorithm, for BFS algorithm and for saving connections between towns
struct Connection
{
	int distance = 0;
	Path* destination = nullptr;
	//This pointer is used in Dijkstra algoritm only. It is not used for BFS at all. 
	Connection* path = nullptr;
};
