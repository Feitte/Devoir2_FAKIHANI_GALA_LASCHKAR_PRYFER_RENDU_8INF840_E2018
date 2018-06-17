#include "stdafx.h"
#include "cell.h"

// visit cell, place neighbors into queue
// return true if solution is found
bool Cell::visit(deque<Cell *> & path) {
	if (visited) // already been here
		return false;
	visited = true; // mark as visited
	cout << "visiting cell " << number << endl;
	if (number == 1) {
		cout << "Maze entirely explored\n";
		return true;
	}
	// put neighbors into deque
	list <Cell *>::iterator start, stop;
	start = neighbors.begin();
	stop = neighbors.end();
	for (; start != stop; ++start)
		if (!(*start)->visited)
			//path.push_front(*start); // depth-first
			path.push_back (*start); // breadth-first
	return false;
}
