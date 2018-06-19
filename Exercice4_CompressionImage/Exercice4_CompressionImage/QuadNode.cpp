#include "stdafx.h"
#include "QuadNode.h"


template <typename T> QuadNode::QuadNode() {
	for (int i = 0; i < nQuadDir; i++)
		sons[i] = nullptr;
}
template <typename T> QuadNode::QuadNode(QuadTree<T>* qtrees[]) {
	for (int i = 0; i < nQuadDir; i++)
		sons[i] = qtrees[i];
}
template <typename T> QuadNode::QuadNode(QuadTree<T>* son0, QuadTree<T>* son1, QuadTree<T>* son2, QuadTree<T>* son3) {
	// Assign sons
	sons[0] = son0;
	sons[1] = son1;
	sons[2] = son2;
	sons[3] = son3;
}
template <typename T> QuadNode::~QuadNode() {
	for (int i = 0; i < nQuadDir; i++)	// For each direction
		if (sons[i] && !(sons[i]->isLeaf() && QuadTree<T>::protect_leaves_from_destruction))
			delete sons[i];
}
