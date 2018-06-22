#pragma once
#include<deque>
#include<list>
#include <iostream>
using namespace std;

class Cell {
public:
	Cell(int c, int n, int h, bool s) : code(c), number(n), heuristic(h), stopping(s), visited(false) { }
	void addNeighbor(Cell * n) { neighbors.push_back(n); }
	bool visit(deque<Cell *> &);
	bool visitAStar(deque<Cell *> & path);
	int code;
	int number;
	int heuristic;
	int actual_cost = 0; //infinite
	int path_cost = 0;
	bool stopping = false;
protected:
	bool visited;
	list <Cell *> neighbors;
	
};
