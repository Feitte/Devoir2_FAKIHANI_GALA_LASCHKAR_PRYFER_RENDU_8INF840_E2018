// Exercice4_QuadTree.cpp : définit le point d'entrée pour l'application console.
//


#include "stdafx.h"
#include "Exercice4_QuadTree.h"
#define cimg_use_png

#include "CImg.h"
using namespace std;

#define MAX_LENGTH 64	// taille maximale du nom de l'image


bool QuadTreeStructure::estEgal(QuadTreeStructure *structure) {
	if ((this->size_Struct == 0) || structure->size_Struct == 0)
		return true;
	else
		return this->estEgalDicho(structure);
}
bool QuadTreeStructure::estEgalCouleur(QuadTreeStructure *structure) {
	if ((this->size_Struct == 0) || structure->size_Struct == 0)
		return true;
	else
		return this->estEgalCouleurDicho(structure);
}
bool QuadTreeStructure::estEgalCouleurDicho(QuadTreeStructure *structure) {
	if ((this->rouge_Struct == structure->rouge_Struct) && (this->bleu_Struct == structure->bleu_Struct) && (this->vert_Struct == structure->vert_Struct))
		return true;
	else
		return false;
}
bool QuadTreeStructure::estEgalDicho(QuadTreeStructure *structure) {
	if (this->gris_Struct == structure->gris_Struct)
		return true;
	else
		return false;
}

static bool isMonochrome(QuadTree<QuadTreeStructure> * nw, QuadTree<QuadTreeStructure> * ne, QuadTree<QuadTreeStructure> * se, QuadTree<QuadTreeStructure> * sw) {
	return (sw->isLeaf() && nw->isLeaf() && ne->isLeaf() && se->isLeaf() && (nw->value().estEgal(&se->value())) && (nw->value().estEgal(&ne->value())) && (nw->value().estEgal(&sw->value())));
}
static bool isMonochromeColor(QuadTree<QuadTreeStructure> * nw, QuadTree<QuadTreeStructure> * ne, QuadTree<QuadTreeStructure> * se, QuadTree<QuadTreeStructure> * sw) {
	return (sw->isLeaf() && nw->isLeaf() && ne->isLeaf() && se->isLeaf() && (nw->value().estEgalCouleur(&se->value())) && (nw->value().estEgalCouleur(&ne->value())) && (nw->value().estEgalCouleur(&sw->value())));
}
static bool isMonochromeColorDicho(QuadTree<QuadTreeStructure> * nw, QuadTree<QuadTreeStructure> * ne, QuadTree<QuadTreeStructure> * se, QuadTree<QuadTreeStructure> * sw) {
	return (sw->isLeaf() && nw->isLeaf() && ne->isLeaf() && se->isLeaf() && (sw->value().estEgalCouleurDicho(&se->value())) && (sw->value().estEgalCouleurDicho(&ne->value())) && (sw->value().estEgalCouleurDicho(&nw->value())));
}
static bool isMonochromeDicho(QuadTree<QuadTreeStructure> * nw, QuadTree<QuadTreeStructure> * ne, QuadTree<QuadTreeStructure> * se, QuadTree<QuadTreeStructure> * sw) {
	return (sw->isLeaf() && nw->isLeaf() && ne->isLeaf() && se->isLeaf() && (sw->value().estEgalDicho(&se->value())) && (sw->value().estEgalDicho(&ne->value())) && (sw->value().estEgalDicho(&nw->value())));
}

CImg<int> imagecon;

// Encodage d'une image en QuadTree
QuadTree<QuadTreeStructure>* encodageStructure(int width, int i, int j, int height) {
	if ((width == 0) || (height == 0))
		return new QuadLeaf<QuadTreeStructure>(QuadTreeStructure());
	if ((width == 1) && (height == 1))
		return new QuadLeaf<QuadTreeStructure>(QuadTreeStructure(imagecon(i, j)));

	QuadTree<QuadTreeStructure> *sw;
	QuadTree<QuadTreeStructure> *nw;
	QuadTree<QuadTreeStructure> *ne;
	QuadTree<QuadTreeStructure> *se;

	if (width == 1) {
		sw = encodageStructure(1, i, j + 1, 1);
		nw = encodageStructure(1, i, j, 1);
		ne = encodageStructure(0, i + 1, j, 0);
		se = encodageStructure(0, i + 1, j + 1, 0);
	} else {
		if (height == 1) {
			sw = encodageStructure(0, i, j + 1, 0);
			nw = encodageStructure(1, i, j, 1);
			ne = encodageStructure(1, i + 1, j, 1);
			se = encodageStructure(0, i + 1, j + 1, 0);
		} else {
			int w = width / 2;
			int h = height / 2;
			int m = width % 2;
			int n = height % 2;
			int wm = w + m;
			int hn = h + n;

			sw = encodageStructure(wm, i, j + hn, h);
			nw = encodageStructure(wm, i, j, hn);
			ne = encodageStructure(w, i + wm, j, hn);
			se = encodageStructure(w, i + wm, j + hn, h);
		}
	}

	if (isMonochromeColor(nw, ne, se, sw)) {
		QuadTreeStructure structureleaf = nw->value();
		structureleaf.setDimensions(height, width);
		return new QuadLeaf<QuadTreeStructure>(structureleaf);
	}
	return new QuadNode<QuadTreeStructure>(nw, ne, se, sw);
}
QuadTree<QuadTreeStructure>* encodageStructureCouleur(int width, int i, int j, int height) {
	if ((width == 0) || (height == 0))
		return new QuadLeaf<QuadTreeStructure>(QuadTreeStructure());
	if ((width == 1) && (height == 1))
		return new QuadLeaf<QuadTreeStructure>(QuadTreeStructure(imagecon(i, j, 0), imagecon(i, j, 1), imagecon(i, j, 2)));

	QuadTree<QuadTreeStructure> *sw;
	QuadTree<QuadTreeStructure> *nw;
	QuadTree<QuadTreeStructure> *ne;
	QuadTree<QuadTreeStructure> *se;

	if (width == 1) {
		sw = encodageStructureCouleur(1, i, j + 1, 1);
		nw = encodageStructureCouleur(1, i, j, 1);
		ne = encodageStructureCouleur(0, i + 1, j, 0);
		se = encodageStructureCouleur(0, i + 1, j + 1, 0);
	} else {
		if (height == 1) {
			sw = encodageStructureCouleur(0, i, j + 1, 0);
			nw = encodageStructureCouleur(1, i, j, 1);
			ne = encodageStructureCouleur(1, i + 1, j, 1);
			se = encodageStructureCouleur(0, i + 1, j + 1, 0);
		} else {
			int w = width / 2;
			int h = height / 2;
			int m = width % 2;
			int n = height % 2;
			int wm = w + m;
			int hn = h + n;

			sw = encodageStructureCouleur(wm, i, j + hn, h);
			nw = encodageStructureCouleur(wm, i, j, hn);
			ne = encodageStructureCouleur(w, i + wm, j, hn);
			se = encodageStructureCouleur(w, i + wm, j + hn, h);
		}
	}

	if (isMonochromeColor(nw, ne, se, sw)) {
		QuadTreeStructure structureleaf = nw->value();
		structureleaf.setDimensions(height, width);
		return new QuadLeaf<QuadTreeStructure>(structureleaf);
	}
	return new QuadNode<QuadTreeStructure>(nw, ne, se, sw);
}
QuadTree<QuadTreeStructure>* encodageStructureCouleurDicho(int size, int i, int j) {
	if (size == 1)
		return new QuadLeaf<QuadTreeStructure>(QuadTreeStructure(imagecon(i, j, 0), imagecon(i, j, 1), imagecon(i, j, 2)));

	int s = size / 2;
	int is = i + s;
	int js = j + s;

	QuadTree<QuadTreeStructure> *sw = encodageStructureCouleurDicho(s, i, js);
	QuadTree<QuadTreeStructure> *nw = encodageStructureCouleurDicho(s, i, j);
	QuadTree<QuadTreeStructure> *ne = encodageStructureCouleurDicho(s, is, j);
	QuadTree<QuadTreeStructure> *se = encodageStructureCouleurDicho(s, is, js);

	if (isMonochromeColorDicho(nw, ne, se, sw)) {
		QuadTreeStructure structureleaf = sw->value();
		structureleaf.setSize(size);
		return new QuadLeaf<QuadTreeStructure>(structureleaf);
	}
	return new QuadNode<QuadTreeStructure>(nw, ne, se, sw);
}
QuadTree<QuadTreeStructure>* encodageStructureDicho(int size, int i, int j) {
	if (size == 1)
		return new QuadLeaf<QuadTreeStructure>(QuadTreeStructure(imagecon(i, j)));

	int s = size / 2;
	int js = j + s;
	int is = i + s;

	QuadTree<QuadTreeStructure> *sw = encodageStructureDicho(s, i, js);
	QuadTree<QuadTreeStructure> *nw = encodageStructureDicho(s, i, j);
	QuadTree<QuadTreeStructure> *ne = encodageStructureDicho(s, is, j);
	QuadTree<QuadTreeStructure> *se = encodageStructureDicho(s, is, js);

	if (isMonochromeDicho(nw, ne, se, sw)) {
		QuadTreeStructure structureleaf = sw->value();
		structureleaf.setSize(size);
		return new QuadLeaf<QuadTreeStructure>(structureleaf);
	}
	return new QuadNode<QuadTreeStructure>(nw, ne, se, sw);
}

// Decodage du QuadTree en image
CImg<int> decodageStructure(QuadTree<QuadTreeStructure> *quadStruct) {
	if (quadStruct != NULL) {
		if (quadStruct->isLeaf()) {
			QuadTreeStructure monochromeStructure = quadStruct->value();
			int width = monochromeStructure.getWidth();
			int height = monochromeStructure.getHeight();
			if (width == 0) {
				CImg<int> leafimg;
				return leafimg;
			}
			CImg<int> leafimg(1, 1, 1, 1, monochromeStructure.getGris());
			for (int k = 0; k < std::ceil(log2(std::max(width, height))); k++) { leafimg.resize_doubleXY(); }
			leafimg.crop(0, 0, width - 1, height - 1);
			
			return leafimg;
		} else {
			CImg<int> nw = decodageStructure(quadStruct->son(0));
			CImg<int> ne = decodageStructure(quadStruct->son(1));
			CImg<int> se = decodageStructure(quadStruct->son(2));
			CImg<int> sw = decodageStructure(quadStruct->son(3));

			nw.append(sw, 'y');
			ne.append(se, 'y');
			nw.append(ne, 'x');

			return nw;
		}
	}
}
CImg<int> decodageStructureCouleur(QuadTree<QuadTreeStructure> *quadStruct) {
	if (quadStruct != NULL) {
		if (quadStruct->isLeaf()) {
			QuadTreeStructure monochromeStructure = quadStruct->value();
			int width = monochromeStructure.getWidth();
			int height = monochromeStructure.getHeight();
			if (width == 0) {
				CImg<int> leafimg;
				return leafimg;
			}
			CImg<int> leafimg(1, 1, 1, 3, monochromeStructure.getRouge(), monochromeStructure.getVert(), monochromeStructure.getBleu());
			for (int k = 0; k < std::ceil(log2(std::max(width, height))); k++) { leafimg.resize_doubleXY(); }
			leafimg.crop(0, 0, width - 1, height - 1);
			
			return leafimg;
		} else {
			CImg<int> nw = decodageStructureCouleur(quadStruct->son(0));
			CImg<int> ne = decodageStructureCouleur(quadStruct->son(1));
			CImg<int> se = decodageStructureCouleur(quadStruct->son(2));
			CImg<int> sw = decodageStructureCouleur(quadStruct->son(3));

			nw.append(sw, 'y');
			ne.append(se, 'y');
			nw.append(ne, 'x');

			return nw;
		}
	}
}
CImg<int> decodageStructureCouleurDicho(QuadTree<QuadTreeStructure> *quadStruct) {
	if (quadStruct != NULL) {
		if (quadStruct->isLeaf()) {
			QuadTreeStructure monochromeStructure = quadStruct->value();
			int size = monochromeStructure.getSize();
			CImg<int> leafimg(1, 1, 1, 3, monochromeStructure.getRouge(), monochromeStructure.getVert(), monochromeStructure.getBleu());
			for (int k = 0; k < log2(size); k++) { leafimg.resize_doubleXY(); }
			
			return leafimg;
		} else {
			CImg<int> nw = decodageStructureCouleurDicho(quadStruct->son(0));
			CImg<int> ne = decodageStructureCouleurDicho(quadStruct->son(1));
			CImg<int> se = decodageStructureCouleurDicho(quadStruct->son(2));
			CImg<int> sw = decodageStructureCouleurDicho(quadStruct->son(3));

			nw.append(sw, 'y');
			ne.append(se, 'y');
			nw.append(ne, 'x');

			return nw;
		}
	}
}
CImg<int> decodageStructureDicho(QuadTree<QuadTreeStructure> *quadStruct) {
	if (quadStruct != NULL) {
		if (quadStruct->isLeaf()) {
			QuadTreeStructure monochromeStructure = quadStruct->value();
			int size = monochromeStructure.getSize();
			CImg<int> leafimg(1, 1, 1, 1, monochromeStructure.getGris());
			for (int k = 0; k < log2(size); k++) { leafimg.resize_doubleXY(); }
			
			return leafimg;
		}
		else {
			CImg<int> nw = decodageStructureDicho(quadStruct->son(0));
			CImg<int> ne = decodageStructureDicho(quadStruct->son(1));
			CImg<int> se = decodageStructureDicho(quadStruct->son(2));
			CImg<int> sw = decodageStructureDicho(quadStruct->son(3));

			nw.append(sw, 'y');
			ne.append(se, 'y');
			nw.append(ne, 'x');

			return nw;
		}
	}
}

bool isColor;

ostream & operator<<(ostream & out, QuadTreeStructure & structure) {
	if (structure.getSize() == 0)
		out << "no pixel";
	else {
		if (isColor)
			out << structure.getRouge() << "/" << structure.getVert() << "/" << structure.getBleu();
		else
			out << structure.getGris();
	}
	return out;
}


int main(int argc, char* argv[]) {

	/* --------------------- *
	 * Chargement de l'image *
	 * --------------------- */

	
	cout << "Veuillez entrer le nom de l'image que vous voulez traiter : ";
	char* filename = new char[MAX_LENGTH];
	cin >> filename;
	//const char* filename = "tableau.png";
	
	imagecon = CImg<unsigned char>(filename);
	imagecon.save("Resultat.png");

	cout << "Specify the name of the file where the decoded image will be saved:";
	char* filesave = new char[MAX_LENGTH];
	cin >> filesave;


	/* -------------------- *
	 * Création du QuadTree *
	 * -------------------- */

	int height = imagecon.height();
	int width = imagecon.width();

	QuadTree<QuadTreeStructure> *quadImage;
	CImg<int> newimage;

	if ((width == height) && (log2(height) == floor(log2(height)))) {
		if (imagecon.spectrum() == 1) {
			isColor = false;
			cout << "début encodage ...\n";
			quadImage = encodageStructureDicho(width, 0, 0);
			cout << "fin encodage ...\n";

			cout << "début decodage ...\n";
			newimage = decodageStructureDicho(quadImage);
			cout << "fin encodage ...\n";
		} else {
			isColor = true;
			cout << "début encodage ...\n";
			quadImage = encodageStructureCouleurDicho(width, 0, 0);
			cout << "fin encodage ...\n";

			cout << "début decodage ...\n";
			newimage = decodageStructureCouleurDicho(quadImage);
			cout << "fin decodage ...\n";
		}
	} else {
		if (imagecon.spectrum() == 1) {
			isColor = false;
			cout << "début encodage ...\n";
			quadImage = encodageStructure(width, 0, 0, height);
			cout << "fin encodage ...\n";

			cout << "début decodage ...\n";
			newimage = decodageStructure(quadImage);
			cout << "fin decodage ...\n";
		} else {
			isColor = true;
			cout << "début encodage ...\n";
			quadImage = encodageStructureCouleur(width, 0, 0, height);
			cout << "fin encodage ...\n";

			cout << "début decodage ...\n";
			newimage = decodageStructureCouleur(quadImage);
			cout << "fin decodage ...\n";
		}
	}

	newimage.save(filesave);
	cout << "L'image décodée a été sauvegardée. \n";
	cout << "Voulez vous voir le QuadTree correspondant ? [o/n]";
	char input;
	cin >> input;
	if (input == 'o' || input == 'y') {
		display(quadImage);
		getchar();
	}
}
