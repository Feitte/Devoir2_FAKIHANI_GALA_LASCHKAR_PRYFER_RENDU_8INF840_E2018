#include "stdafx.h"
#include "maze.h"

Maze::Maze(const char * nameOfFile, int cell_start, int cell_stop)
{
	
	ifstream fichier(nameOfFile, ios::in);  // On ouvre en lecture
	if (fichier)							// Si l'ouverture a fonctionne
	{
		string ligne;
		fichier >> numCols >> numRows;		// Lecture de la premiere ligne pour initialiser le nombre de ligne et colonne.
		//cout << numCols << " " << numRows << " " << endl; // Log de creation

		// Formule pour l'heuristique
		int Xstop = (cell_stop-1)/ numCols;
		int Ystop = (cell_stop-1) % numRows;
		
		getline(fichier, ligne);
		int number = 1;
		for (int i = 0; i < numCols; i++)
		{
			getline(fichier, ligne);		//Lecture du fichier ligne par ligne
			std::istringstream iss(ligne);	
			for (int n = 0; n<numRows; n++)
			{
				int val;
				iss >> val;
				bool setStop = (Xstop==i && Ystop==n) ? true : false;
				int heuristic =  abs(Xstop-i)%(numCols) + abs(Ystop-n)%(numRows); // Formule pour l'heuristique (le nombre de case séparant de la sortie indépendament du mur
				//cout << i << " " << n << " " << heuristic << endl; //Affiche l'heuristique pour chaque case.
				Cell * cellule = new Cell(val, number++, heuristic, setStop);	// Creation des cellules avec leurs valeurs, attribution d'un nombre pour chacun d'entre eux.
				grille.push_back(cellule);					// Ajout des cellules dans la liste.
				//cout << val << endl; //Log de creation
			}
			//cout << endl; //Log de creation
		}
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;

	start = grille.at(cell_start - 1);	// Initialisation du depart du labyrinthe
	stop = grille.at(cell_stop - 1);		// Initialisation de l'arrivee du labyrinthe

	for (int i = 0; i < numCols*numRows; i++) {
		constructFromCode(grille.at(i), i); // Creation des voisins en fonction du code
	}
		
}

//BFS du cours mais ajout de la fonction stopping pour arreter l'exploration si on atteint l'arrivee
void Maze::solveMazeBFS() {
	start->visit(path);
	Cell * current;
	while ((!path.empty() && !finished))
	{
		current = path.front();
		path.pop_front();
		finished = current->visit(path);
		if (stopping(current)) {
			break;
		}
	} 
	
	if (!finished)
		cout << "Not all the cell of the maze have been explored";
}

void Maze::solveMazeAStar() {
	start->visitAStar(path);
	Cell * current;
	int current_check_cost = 9999999; //infinite
	int need_to_visit = -1;
	

	while ((!path.empty() && !finished))
	{
		for (int i = 0; i < path.size(); i++) {
			current = path.front();
			if (current->actual_cost <= current_check_cost) {
				current_check_cost = current->actual_cost;
				need_to_visit = i;
			}
		}
	
		current = path.at(need_to_visit);
		path.pop_back();
		finished = current->visitAStar(path);

	}
	if (!finished)
		cout << "Not all the cell of the maze have been explored";
}


void Maze::constructFromCode(Cell * cellule, int i) {
	
	switch (cellule->code) {
	case 0:
		cellule->addNeighbor(grille.at(i - numCols));
		cellule->addNeighbor(grille.at(i + numCols));
		cellule->addNeighbor(grille.at(i + 1));
		cellule->addNeighbor(grille.at(i - 1));
		break;
	case 1:
		cellule->addNeighbor(grille.at(i - numCols));
		cellule->addNeighbor(grille.at(i + 1));
		cellule->addNeighbor(grille.at(i - 1));
		break;
	case 2:
		cellule->addNeighbor(grille.at(i - numCols));
		cellule->addNeighbor(grille.at(i + numCols));
		cellule->addNeighbor(grille.at(i - 1));
		break;
	case 3:
		cellule->addNeighbor(grille.at(i - numCols));
		cellule->addNeighbor(grille.at(i - 1));
		break;
	case 4:
		cellule->addNeighbor(grille.at(i + numCols));
		cellule->addNeighbor(grille.at(i + 1));
		cellule->addNeighbor(grille.at(i - 1));
		break;
	case 5:
		cellule->addNeighbor(grille.at(i + 1));
		cellule->addNeighbor(grille.at(i - 1));
		break;
	case 6:
		cellule->addNeighbor(grille.at(i + numCols));
		cellule->addNeighbor(grille.at(i - 1));
		break;
	case 7:
		cellule->addNeighbor(grille.at(i - 1));
		break;
	case 8:
		cellule->addNeighbor(grille.at(i - numCols));
		cellule->addNeighbor(grille.at(i + numCols));
		cellule->addNeighbor(grille.at(i + 1));
		break;
	case 9:
		cellule->addNeighbor(grille.at(i - numCols));
		cellule->addNeighbor(grille.at(i + 1));
		break;
	case 10:
		cellule->addNeighbor(grille.at(i - numCols));
		cellule->addNeighbor(grille.at(i + numCols));
		break;
	case 11:
		cellule->addNeighbor(grille.at(i - numCols));
		break;
	case 12:
		cellule->addNeighbor(grille.at(i + numCols));
		cellule->addNeighbor(grille.at(i + 1));
		break;
	case 13:
		cellule->addNeighbor(grille.at(i + 1));
		break;
	case 14:
		cellule->addNeighbor(grille.at(i + numCols));
		break;
	case 15:
		break;
	}
}