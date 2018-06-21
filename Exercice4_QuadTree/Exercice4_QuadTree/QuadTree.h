#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>

// Compatibility with old C++ compilers
#if __cplusplus < 201103L
#ifndef NULL
#define NULL 0
#endif
#ifndef nullptr
#define nullptr NULL
#endif
#endif



/* ------------------------- *
 * The 4 quadrant directions *
 * ------------------------- */

const int NW = 0; // North-West
const int NE = 1; // North-East
const int SE = 2; // South-East
const int SW = 3; // South-West
const int nQuadDir = 4;	// The number of directions

// Forward declarations (so that the class names can be used in QuadTree)
template <typename T> class QuadLeaf; // The type of a QuadTree leaf
template <typename T> class QuadNode; // The type of a QuadTree node



/* -------------------------------------------------------------------- *
 * Abstract class for quadtrees, whose leaves contain a value of type T *
 * -------------------------------------------------------------------- */

template <typename T>
class QuadTree {
	public:
		virtual ~QuadTree() {}

		virtual bool isLeaf() const = 0;	// Tell if this quadtree is a leaf
		inline virtual bool isNode() const { return !isLeaf(); }	// Tell if this quadtree is a node

		virtual int nLeaves() const = 0;
		virtual int nNodes() const = 0;
		virtual int nTrees() const = 0;
		static bool protect_leaves_from_destruction;

		// QuadLeaf methods
		virtual const T value() const = 0;
		virtual T& value() = 0;

		// QuadNode methods
		virtual QuadTree<T>* const& son(int d) const = 0;
		virtual QuadTree<T>*& son(int d) = 0;
};

template <typename T>
bool QuadTree<T>::protect_leaves_from_destruction = false;



/*----------------------*
 * A leaf of a quadtree *
 *----------------------*/

template <typename T>
class QuadLeaf : public QuadTree<T> {
	T val;

	public:
		inline bool isLeaf() const { return true; }	// Tell if this quadtree is a leaf

		QuadLeaf(T value) : val(value) {}
		
		inline int nLeaves() const { return 1; }	// Return the number of leaves in this qtree
		inline int nNodes()  const { return 0; }	// Return the number of nodes in this qtree (excluding leaves)
		inline int nTrees()  const { return 1; }	// Return the number of (sub)trees in this qtree (nodes and leaves)

		// QuadLeaf methods
		inline const T value() const { return val; }
		inline T& value() { return val; }

		// QuadNode methods
		inline QuadTree<T>* const& son(int d) const { throw new std::domain_error("Not a QuadNode"); }
		inline QuadTree<T>*& son(int d) { throw new std::domain_error("Not a QuadNode"); }
};



/* ------------------------------ *
 * A branching node of a quadtree *
 * ------------------------------ */

template <typename T>
class QuadNode : public QuadTree<T> {
	QuadTree<T>* sons[nQuadDir];	// The sons of this node for the 4 quadrant directions

public:	
	inline bool isLeaf() const { return false; }	// Tell if this quadtree is a leaf

	QuadNode() { for (int i = 0; i < nQuadDir; i++) { sons[i] = nullptr; } }	// Construct a new branching node with empty (null) sons
	QuadNode(QuadTree<T>* qtrees[]) { for (int i = 0; i < nQuadDir; i++) { sons[i] = qtrees[i]; } }	// Construct a new branching node given an array of 4 quadtrees
	QuadNode(QuadTree<T>* son0, QuadTree<T>* son1, QuadTree<T>* son2, QuadTree<T>* son3) {	// Construct a new branching node given 4 sons
		// Assign sons
		sons[0] = son0;
		sons[1] = son1;
		sons[2] = son2;
		sons[3] = son3;
	}
	~QuadNode() {
		for (int i = 0; i < nQuadDir; i++)	// For each direction
			if (sons[i] && !(sons[i]->isLeaf() && QuadTree<T>::protect_leaves_from_destruction))
				delete sons[i];
	}

	// Return the number of leaves in this qtree
	inline int nLeaves() const 	{
		int n = 0;
		for (int i = 0; i < nQuadDir; i++)
			if (sons[i] != nullptr)
				n += sons[i]->nLeaves();
		return n;
	}

	// Return the number of nodes in this qtree (excluding leaves)
	inline int nNodes() const {
		int n = 1;
		for (int i = 0; i < nQuadDir; i++)
			if (sons[i] != nullptr)
				n += sons[i]->nNodes();
		return n;
	}

	// Return the number of (sub)trees in this qtree (nodes and leaves)
	inline int nTrees() const {
		int n = 1;
		for (int i = 0; i < nQuadDir; i++)
			if (sons[i] != nullptr)
				n += sons[i]->nTrees();
		return n;
	}

	// QuadLeaf methods
	inline const T value() const { throw new std::domain_error("Not a QuadLeaf"); }
	inline T& value() { throw new std::domain_error("Not a QuadLeaf"); }

	// QuadNode methods
	inline QuadTree<T>* const& son(int d) const	{
		if (!(0 <= d && d < nQuadDir)) {	// Make sure the direction makes sense
			std::ostringstream oss; oss << d;
			throw new std::out_of_range("Not a valid direction: " + oss.str());
		}
		return sons[d];
	}

	// Return a reference to the son of this quadtree in direction d
	inline QuadTree<T>*& son(int d) {
		if (!(0 <= d && d < nQuadDir)) {	// Make sure the direction makes sense
			std::ostringstream oss; oss << d;
			throw new std::out_of_range("Not a valid direction: " + oss.str());
		}
		return sons[d];
	}
};



/* ------------- *
 * For debugging *
 * ------------- */

template <typename T>
void display(QuadTree<T>* qt, std::string prefix = "", void(*prt)(T) = nullptr) {
	if (qt != nullptr) {	// If tree is not null
		if (qt->isLeaf()) {	// If tree is leaf
			std::cout << prefix << " = ";
			if (prt)
				(*prt)(qt->value());
			else
				std::cout << qt->value();
			std::cout << std::endl;
		}
		// Otherwise if tree is a branch node
		else
			for (int d = 0; d < nQuadDir; d++) {	// For each direction
				std::string dirName[] = { "NW", "NE", "SE", "SW" };	// Get direction name
				display(qt->son(d), prefix + "-" + dirName[d]);		// Dump son in this direction
			}
	}
	// Otherwise, if tree is null pointer
	else
		std::cout << prefix << " ." << std::endl;
}
