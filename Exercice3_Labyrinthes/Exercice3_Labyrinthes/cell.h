#pragma once
#include<deque>
#include<list>
#include <iostream>
using namespace std;

class Cell {
public:
	Cell(int c, int n, int h) : code(c), number(n), heuristic(h), visited(false) { }
	void addNeighbor(Cell * n) { neighbors.push_back(n); }
	bool visit(deque<Cell *> &);
	int code;
	int number;
	int heuristic;
	int cost;
protected:
	bool visited;
	list <Cell *> neighbors;
};
