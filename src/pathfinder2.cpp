#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

#include "TownGraph.h"
#include "Map.h"
#include "Input.h"

int main()
{
	int width, height;
	scanf("%d", &width);
	scanf("%d", &height);
	Input input({ height, width });
	input.read_map();
	TownGraph graph;
	Map map({height, width});
	input.parse_map(&graph, &map);
	map.find_direct_connections(&graph);
	graph.read_air_connections();
	graph.read_paths();
	return 0;
}
