This program utilizes Breath First Search and Dijkstra Algorithm to find the shortest path between two points on an ASCII drawing of a map.
____________________________________________________________________

In order to optimize the code data structures such as a priority list and a trie. Recursion is not used, because the sheer amount of data would cause stack overflow. This software is capable of working out the best path within seconds on maps consisting of tens of thousands of characters.
It was developed as a university assignment.

On the map '*' symbolizes a city (next to each of those symbol there's a name of the city), '#' symbolizes a traversable path and '.' symbolizes an untraversable field.
Every city and every path take one unit of time to traverse.

Aside from the map, a set of additional one-way connections is given, in the format:
<n = number of connection>
<point of origin 1> <destination 1> <travel time 1>
<point of origin 2> <destination 2> <travel time 2>
...
<point of origin n> <destination n> <travel time n>

Finally, a set of queries is given in the format:
<n = number of queries>
<point of origin 1> <destination 1> <x1>
<point of origin 2> <destination 2> <x2>
...
<point of origin n> <destination n> <xn>

x is an indicator:
0 = only print length of the shortest path
1 = print both length of the shortest path and all cities it passes through


Example input:
______________________________

20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
0
3
KIELCE KRAKOW 0
KRAKOW GDANSK 0
KRAKOW GDANSK 1


Output for the example input
______________________________

5
40
40 KIELCE SZCZECIN


How to to test the program
______________________________

To the code there is a set of 14 tests attached. .in files are input, .out files are desired output to check the actual output
Tests can be pasted into the command line, or files can be redirected to the program using '<' on both Linux and Windows.
When using and IDE, it is advised to compile on Release mode for better performance. Those tests really are huge.


How it all works?
____________________________________________________________________

To determines the right answers, program parses the map and builds a graph using Breath First Search algorithm.
Graph is represented as adjacency list.
To shorten the search time for cities pointers to all graph elements are saved in a trie.
Then additional connections are read and added to the graph.
When the graph is finished, a modified (to stop after finding the destination town) Dijkstra algorithm is ran on the graph.


Final notes
____________________________________________________________________

The program was fully developed by me, however all the tests have been provided be the university.
Software is thereby released under MIT Licence. See opensource.org for details. 
Copy of the license below:

Copyright 2023 Mateusz Nurczyński

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.