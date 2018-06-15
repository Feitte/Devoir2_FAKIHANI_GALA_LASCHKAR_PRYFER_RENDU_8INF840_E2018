#pragma once
#include<iostream>
#include<vector>
#include "cell.h"
#include <string>
#include <fstream> 
#include <sstream>
using namespace std;

class Maze {
public:
	Maze(const char * nameOfFile, int starting_cell);
	void solveMazeBFS();
	void print();
	int getCode(int r, int c);
protected:
	int numRows;
	int numCols;
	vector<int> codes;
	Cell * start;
	bool finished;
	void constructFromCode(Cell * cellule, int i);
	deque <Cell *> grille;
	deque <Cell *> path;// double-ended queue = Stack + queue
};