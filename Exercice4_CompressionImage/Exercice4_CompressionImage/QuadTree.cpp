#include "stdafx.h"
#include "QuadTree.h"


// Forward declarations (so that the class names can be used in QuadTree)
template <typename T> class QuadLeaf; // The type of a QuadTree leaf
template <typename T> class QuadNode; // The type of a QuadTree node

template <typename T> QuadTree::QuadTree() {}
template <typename T> QuadTree::~QuadTree() {}
