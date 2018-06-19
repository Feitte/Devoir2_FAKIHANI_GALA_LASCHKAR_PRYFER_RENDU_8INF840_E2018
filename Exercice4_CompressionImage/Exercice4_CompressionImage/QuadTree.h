#pragma once
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>


 /*------------------------------*
  * Abstract class for quadtrees *
  *------------------------------*/

template <typename T>
class QuadTree {
	public:
		virtual ~QuadTree() {}

		virtual bool isLeaf() const = 0;	// Tell if this quadtree is a leaf
		inline virtual bool isNode() const { return !isLeaf(); }	// Tell if this quadtree is a node

		virtual int nLeaves() const = 0;	// Return the number of leaves in this qtree
		virtual int nNodes()  const = 0;	// Return the number of nodes in this qtree (excluding leaves)
		virtual int nTrees()  const = 0;	// Return the number of (sub)trees in this qtree (nodes and leaves)

		static bool protect_leaves_from_destruction;

		// QuadLeaf methods
		virtual const T value() const = 0;
		virtual T& value() = 0;

		// QuadNode methods
		virtual QuadTree<T>* const& son(int d) const = 0;
		virtual QuadTree<T>*& son(int d) = 0;
};

template <typename T>
bool QuadTree<T>::protect_leaves_from_destruction = false;	// Indicate whether leaves should be excluded from deletion
