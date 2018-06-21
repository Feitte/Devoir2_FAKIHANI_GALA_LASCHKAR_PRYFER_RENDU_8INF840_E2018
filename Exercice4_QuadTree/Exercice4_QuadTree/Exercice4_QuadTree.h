#pragma once

#include "CImg.h"
#include "QuadTree.h"
using namespace cimg_library;

class QuadTreeStructure {
	public:
		QuadTreeStructure(int bleu, int rouge, int vert) {	// Image Tricolore
			bleu_Struct = bleu;
			rouge_Struct = rouge;
			vert_Struct  = vert;

			size_Struct = 1;
			width_Struct = 1;
			height_Struct = 1;
		}
		QuadTreeStructure(int gris) { // Image Monochrome
			gris_Struct = gris;

			height_Struct = 1;
			size_Struct   = 1;
			width_Struct  = 1;
		}
		QuadTreeStructure() {
			height_Struct = 0;
			size_Struct   = 0;
			width_Struct  = 0;
		}

		int getBleu()  { return bleu_Struct;  }
		int getGris()  { return gris_Struct;  }
		int getRouge() { return rouge_Struct; }
		int getVert()  { return vert_Struct;  }

		int getHeight() { return height_Struct; }
		int getWidth() { return width_Struct; }
		int getSize()   { return size_Struct;  }

		void setSize(int size) { size_Struct = size; }
		void setDimensions(int height, int width) { height_Struct = height; width_Struct = width; }

		inline bool estEgal(QuadTreeStructure *structure);
		inline bool estEgalCouleur(QuadTreeStructure *structure);
		inline bool estEgalCouleurDicho(QuadTreeStructure *structure);
		inline bool estEgalDicho(QuadTreeStructure *structure);

	private:
		int bleu_Struct;
		int gris_Struct;
		int rouge_Struct;
		int vert_Struct;
		
		int height_Struct;
		int width_Struct;
		int size_Struct;
};
