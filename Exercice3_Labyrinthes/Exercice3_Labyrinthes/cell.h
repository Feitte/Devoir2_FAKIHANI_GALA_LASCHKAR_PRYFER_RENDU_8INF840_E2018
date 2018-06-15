#pragma once
#include<deque>
#include<list>
#include <iostream>
using namespace std;

class Cell {
public:
	Cell(int c, int n) : code(c), number(n), visited(false) { }
	void addNeighbor(Cell * n) { neighbors.push_back(n); }
	bool visit(deque<Cell *> &);
	string toString();

	int code;
	int number;
protected:
	bool visited;
	list <Cell *> neighbors;
};
