// Exercice4_CompressionImage.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
using namespace std;

int main() {
	// The 4 quadrant directions
	const int NW = 0;	// North-West
	const int NE = 1;	// North-East
	const int SE = 2;	// South-East
	const int SW = 3;	// South-West
	const int nQuadDir = 4;	// The number of directions

    return 0;
}


/*---------------*
 * For debugging *
 *---------------*/

// Display a quadtree on standard output
template <typename T>
void display(QuadTree<T>* qt, string prefix = "", void(*prt)(T) = nullptr) {
	// If tree is not null
	if (qt != nullptr) {
		// If tree is leaf
		if (qt->isLeaf()) {
			cout << prefix << " = ";
			if (prt) { (*prt)(qt->value()); }
			else { cout << qt->value(); }
			cout << endl;
		}
		// Otherwise if tree is a branch node
		else {
			for (int d = 0; d < nQuadDir; d++) {	// For each direction
				string dirName[] = { "NW", "NE", "SE", "SW" };
				display(qt->son(d), prefix + "-" + dirName[d]);
			}
		}
	}
	else { cout << prefix << " ." << endl; }
}
