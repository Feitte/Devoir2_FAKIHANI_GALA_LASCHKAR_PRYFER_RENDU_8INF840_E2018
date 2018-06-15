#include "stdafx.h"
#include "maze.h"

Maze::Maze(const char * nameOfFile, int starting_cell)
{
	ifstream fichier("maze.txt", ios::in);  // on ouvre en lecture
	if (fichier)  // si l'ouverture a fonctionné
	{
		string ligne;
		fichier >> numCols >> numRows;
		//cout << numCols << " " << numRows << " " << endl;
		getline(fichier, ligne);
		int number = 1;
		
		for (int i = 0; i < numCols; i++)
		{
			getline(fichier, ligne);
			std::istringstream iss(ligne);
			for (int n = 0; n<numRows; n++)
			{
				int val;
				iss >> val;
				Cell * cellule = new Cell(val, number++);
				grille.push_back(cellule);
				//cout << val << endl;
			}
			//cout << endl;
		}
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	start = grille.at(starting_cell);
	//Mettre un while et boucler sur le voisin sinon c'est pas un growing tree !
	for (int i = 0; i < numCols*numRows; i++) {
		constructFromCode(grille.at(i), i);
	}
		
}

void Maze::solveMazeBFS() {
	start->visit(path);
	while ((!finished) && (!path.empty())) {
		Cell * current = path.front();
		path.pop_front();
		finished = current->visit(path);
	}
	if (!finished)
		cout << "no solution found\n";
}

void Maze::print()
{
}

int Maze::getCode(int r, int c)
{
	return 0;
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