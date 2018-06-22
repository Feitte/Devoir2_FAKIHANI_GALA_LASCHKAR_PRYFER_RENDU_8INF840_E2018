#include "stdafx.h"
#include "cell.h"

// visit cell, place neighbors into queue
// return true if solution is found
bool Cell::visit(deque<Cell *> & path) {
	if (visited) // already been here
		return false;
	visited = true; // mark as visited
	cout << "visiting cell " << number << endl;
	if (stopping) {
		cout << "Maze explored until node :" << number << endl;
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

bool Cell::visitAStar(deque<Cell *> & path) {
	if (visited) // already been here
		return false;
	visited = true; // mark as visited
	cout << "visiting cell " << number << endl;
	if (stopping) {
		cout << "Maze explored until node :" << number << endl;
		return true;
	}
	// put neighbors into deque
	list <Cell *>::iterator start, stop;
	start = neighbors.begin();
	stop = neighbors.end();
	Cell * choosing_node_to_push = NULL;
	
	for (; start != stop; ++start)
		if (!(*start)->visited) {
			(*start)->path_cost = path_cost + 1;
			actual_cost = (*start)->heuristic + path_cost;
			cout << heuristic << "__" << path_cost << endl;
			path.push_front(*start);
		}
	
	return false;
}
