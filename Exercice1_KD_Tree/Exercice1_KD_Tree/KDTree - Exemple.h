#pragma once

#include <iostream>
#include <math.h>

template<int k, typename E>
class KdTree {
public:
	// constructeurs et destructeurs
	KdTree();
	~KdTree();
	// modificateurs
	void insert(E* p);
	void remove(E* p);
	// recherche de noeud
	bool search(E* p);
	// plus proche voisin
	E* nearestNeighbor(E* p);
	// affichage
	void printTree();

private:
	// modèle d'implantation
	class KdNode {
	public:
		E * point;
		KdNode* leftChild;
		KdNode* rightChild;
		KdNode(E* p) : point(_copyPoint(p)), leftChild(0), rightChild(0) {};
		~KdNode() { delete[] point; };
	};

	// noeud principal
	KdNode* rootNode;

	// méthodes auxiliaires
	void _insertAux(KdNode*& node, int depth, E* p);
	bool _searchAux(KdNode*& node, int depth, E* p);
	bool _removeAux(KdNode*& node, int depth, E* p);
	void _nearestNeighborAux(KdNode*& node, int depth, E* p, E*& bestPoint, double& bestDistance);
	E* _minimum(KdNode*& node, int depth, int d);
	void _printTreeAux(KdNode*& node, int depth);

	// opérations sur les points
	static bool _areEqual(E* p1, E* p2);
	static E* _copyPoint(E* p);
	static double _distance(E* p1, E* p2);
};

template<int k, typename E>
inline KdTree<k, E>::KdTree() {
	rootNode = 0;
}

template<int k, typename E>
inline KdTree<k, E>::~KdTree() {
}


/* AJOUT DE NOEUDS */
template<int k, typename E>
inline void KdTree<k, E>::insert(E* p) {
	_insertAux(rootNode, 0, p);
}

template<int k, typename E>
inline void KdTree<k, E>::_insertAux(KdNode*& node, int depth, E* p) {
	if (node == 0)
		node = new KdNode(p);
	else {
		int currentDim = depth % k;
		if (p[currentDim] < node->point[currentDim])
			_insertAux(node->leftChild, depth + 1, p);
		else
			_insertAux(node->rightChild, depth + 1, p);
	}
}

/* RECHERCHE DE NOEUDS */
template<int k, typename E>
inline bool KdTree<k, E>::search(E* p) {
	return _searchAux(rootNode, 0, p);
}

template<int k, typename E>
inline bool KdTree<k, E>::_searchAux(KdNode *& node, int depth, E * p) {
	if (node == 0)
		return false;
	else {
		if (_areEqual(node->point, p))
			return true;

		int currentDim = depth % k;
		if (p[currentDim] < node->point[currentDim])
			return _searchAux(node->leftChild, depth + 1, p);
		else
			return _searchAux(node->rightChild, depth + 1, p);
	}
}

/* SUPPRESSION DE NOEUDS */
template<int k, typename E>
inline void KdTree<k, E>::remove(E* p) {
	if (_removeAux(rootNode, 0, p)) {
		// si _removeAux a renvoyé true, c'est que le rootNode et une feuille et a été supprimé, le rootNode devient donc null
		rootNode = 0;
	}
}

// fonction auxiliaire de suppression de noeud, renvoie true si le noeud est une feuille et est supprimé lors de cette étape
template<int k, typename E>
inline bool KdTree<k, E>::_removeAux(KdNode *& node, int depth, E * p) {
	if (node == 0)
		return false;
	else {
		int currentDim = depth % k;

		if (_areEqual(node->point, p)) { // il faut supprimer le noeud courant
			if (node->rightChild != 0) {
				E* minRightChild = _minimum(node->rightChild, depth + 1, currentDim); // on récupère le minimum du fils droit de la dimension courante
				int i;
				for (i = 0; i < k; i++) { // on remplace le noeud par le minimum trouvé
					node->point[i] = minRightChild[i];
				}
				if (_removeAux(node->rightChild, depth + 1, minRightChild)) { // on supprime le minimum trouvé dans le fils droit
					// si _removeAux a renvoyé true, c'est que le fils droit et une feuille et a été supprimé, le fils droit devient donc null
					node->rightChild = 0;
					return false;
				}
			}
			else if (node->leftChild != 0) {
				E* minLeftChild = _minimum(node->leftChild, depth + 1, currentDim); // on récupère le minimum du fils gauche de la dimension courante
				int i;
				for (i = 0; i < k; i++) {
					node->point[i] = minLeftChild[i];
				}
				// la dimension courante du minimum trouvé est inférieur à tous ceux du fils gauche (par définition)
				// une fois le noeud courant remplacé par le minimum, on fait passer le fils gauche à droite pour conserver les propriété du KdTree
				node->rightChild = node->leftChild;
				node->leftChild = 0;
				if (_removeAux(node->rightChild, depth + 1, minLeftChild)) { // on supprime le minimum trouvé dans le fils gauche (maintenant fils droit)
					// si _removeAux a renvoyé true, c'est que le fils droit et une feuille et a été supprimé, le fils droit devient donc null
					node->rightChild = 0;
					return false;
				}
			}
			else { // on arrive sur une feuille, on supprime le noeud
				delete node;
				return true; // on renvoie true pour remplacer le noeud courant par null dans le noeud parent
			}
		}

		if (p[currentDim] < node->point[currentDim]) {
			if (_removeAux(node->leftChild, depth + 1, p))
				node->leftChild = 0; // si _removeAux a renvoyé true, c'est que le fils gauche et une feuille et a été supprimé, le fils gauche devient donc null
		}
		else {
			if (_removeAux(node->rightChild, depth + 1, p))
				node->rightChild = 0; // si _removeAux a renvoyé true, c'est que le fils droit et une feuille et a été supprimé, le fils droit devient donc null
		}

		return false;
	}
}

template<int k, typename E>
inline E * KdTree<k, E>::_minimum(KdNode *& node, int depth, int d) {
	if (node == 0)
		return 0;

	if (depth % k == d) { // la dimension courante est celle du minimum recherché
		if (node->leftChild == 0)
			return node->point; // pas de fils gauche, on a trouvé le minimum
		else
			return _minimum(node->leftChild, depth + 1, d); // on continue de chercher le minimum à gauche
	}
	else { // la dimension courante n'est pas celle du minimum recherché
		E* minLeft = _minimum(node->leftChild, depth + 1, d);
		E* minRight = _minimum(node->rightChild, depth + 1, d);
		E* current = node->point;
		// le minimum peut être partout (gauche, noeud courant ou droite)
		if (minLeft != 0 && (minRight == 0 || minLeft[d] <= minRight[d]) && minLeft[d] <= current[d])
			return minLeft;
		else if (minRight != 0 && (minLeft == 0 || minRight[d] <= minLeft[d]) && minRight[d] <= current[d])
			return minRight;
		else
			return current;
	}
}

/* RECHERCHE DU PLUS PROCHE VOISIN */
template<int k, typename E>
inline E * KdTree<k, E>::nearestNeighbor(E * p) {
	// initialisation
	double bestDistance = _distance(rootNode->point, p);
	E* bestPoint = rootNode->point;
	// recherche du plus proche voisin
	_nearestNeighborAux(rootNode, 0, p, bestPoint, bestDistance);
	return _copyPoint(bestPoint);
}

template<int k, typename E>
inline void KdTree<k, E>::_nearestNeighborAux(KdNode *& node, int depth, E * p, E *& bestPoint, double & bestDistance) {
	if (node == 0)
		return;

	double newDistance = _distance(p, node->point); // distance par rapport au point courant
	if (newDistance < bestDistance) {
		bestDistance = newDistance;
		bestPoint = node->point;
	}

	int currentDim = depth % k;
	if (p[currentDim] < node->point[currentDim]) { // on recherche d'abord dans la direction où se situe le point (ici à gauche)
		_nearestNeighborAux(node->leftChild, depth + 1, p, bestPoint, bestDistance);
		if (p[currentDim] + bestDistance >= node->point[currentDim]) { 
			// si l'hypersphère de rayon bestDistance et de centre bestPoint coupe l'hyperplan de séparation
			_nearestNeighborAux(node->rightChild, depth + 1, p, bestPoint, bestDistance); // on recherche de l'autre côté de l'arbre (ici à droite)
		} // si l'hypersphère ne coupe pas l'hyperplan, on ne trouvera pas de point plus proche de l'autre côté, inutile de rechercher
	}
	else { // idem si le point se situe à droite
		_nearestNeighborAux(node->rightChild, depth + 1, p, bestPoint, bestDistance);
		if (p[currentDim] - bestDistance <= node->point[currentDim]) {
			_nearestNeighborAux(node->leftChild, depth + 1, p, bestPoint, bestDistance);
		}
	}
}

/* METHODES SUR LES POINTS */
template<int k, typename E>
inline bool KdTree<k, E>::_areEqual(E* p1, E* p2) {
	int i;
	for (i = 0; i < k; i++) {
		if (p1[i] != p2[i])
			return false;
	}
	return true;
}

template<int k, typename E>
inline E* KdTree<k, E>::_copyPoint(E * p) {
	E* newPoint = new E[k];
	int i;
	for (i = 0; i < k; i++)
		newPoint[i] = p[i];
	return newPoint;
}

template<int k, typename E>
inline double KdTree<k, E>::_distance(E * p1, E * p2) {
	int i;
	double dist = 0;
	for (i = 0; i < k; i++) {
		dist += (p1[i] - p2[i]) * (p1[i] - p2[i]);
	}
	return sqrt(dist); // distance euclidienne
}

/* AFFICHAGE */
template<int k, typename E>
inline void KdTree<k, E>::printTree() {
	if (rootNode == 0)
		std::cout << "null";
	else
		_printTreeAux(rootNode, 0);
}

template<int k, typename E>
inline void KdTree<k, E>::_printTreeAux(KdNode *& node, int depth) {
	int i; 
	for (i = 0; i < depth; i++)
		std::cout << "    ";
	if (node == 0)
		std::cout << "null\n";
	else {
		std::cout << "(";
		for (i = 0; i < k; i++) {
			std::cout << node->point[i];
			if (i < k - 1)
				std::cout << ",";
		}
		std::cout << ")\n";
		_printTreeAux(node->leftChild, depth + 1);
		_printTreeAux(node->rightChild, depth + 1);
	}
}