// Exercice3_Labyrinthes.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "maze.h"

int main()
{
	Maze labyrinthe = Maze("maze.txt", 25, 1);	//Create the labyrinthe from the maze.txt file and set the start to the 25 and the last to 1.
	labyrinthe.solveMazeAStar();					//Solve with BFS.
	getchar();
}

