// Exercice3_Labyrinthes.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "maze.h"
#include <fstream>
#include <string>
int main()
{
	Maze labyrinthe = Maze("maze.txt", 24); //Create the labyrinthe from the maze.txt file and set the start to the 24 number (the last in this case).
	labyrinthe.solveMazeBFS();				//Solve with BFS.
	getchar();
}

