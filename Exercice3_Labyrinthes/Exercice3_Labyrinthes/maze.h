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
	Maze(const char * nameOfFile, int starting_cell, int cell_stop);
	void solveMazeBFS();
	void solveMazeAStar();
protected:
	int numRows;
	int numCols;
	Cell * start;
	Cell * stop;
	bool finished;
	bool stopping(Cell * current) { return (current->number == stop->number) ? true : false;}
	void constructFromCode(Cell * cellule, int i);
	int pathCost = 0;
	deque <Cell *> grille;
	deque <Cell *> path;// double-ended queue = Stack + queue
};