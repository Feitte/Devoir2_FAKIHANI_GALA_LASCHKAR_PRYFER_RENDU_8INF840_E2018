// Exercice3_Labyrinthes.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "maze.h"

int main()
{
	Maze labyrinthe = Maze("maze.txt", 25, 1);	//Create the labyrinthe from the maze.txt file and set the start to the 25 and the last to 1.
	
	int choice = -1;
	cout << "For solving with BFS choose  \"0\" and press Enter." << endl;
	cout << "For solving with A*  choose  \"1\" and press Enter." << endl;
	cin >> choice;
	if (choice == 0) {
		cout << "Solving with BFS " << endl;
		labyrinthe.solveMazeBFS();					//Solve with BFS.
	}
	else if (choice == 1) {
		cout << "Solving with A* " << endl;
		labyrinthe.solveMazeAStar();				//Solve with BFS.
	}

	system("PAUSE");
}

