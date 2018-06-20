#pragma once


/*----------------------------------------------------*
 * A leaf of a quadtree, containing a value of type T *
 *----------------------------------------------------*/

template <typename T>
class QuadLeaf : public QuadTree<T> {
	T val;

	public:
		QuadLeaf(T value) : val(value) {}	// Construct a QuadLeaf with the given value

		inline bool isLeaf() const { return true; }
		inline int nLeaves() const { return 1; }	// Return the number of leaves in this qtree
		inline int nNodes()  const { return 0; }	// Return the number of nodes in this qtree (excluding leaves)
		inline int nTrees()  const { return 1; }	// Return the number of (sub)trees in this qtree (nodes and leaves)

		// QuadLeaf methods
		inline const T value() const { return val; }	// Return the value of this QuadLeaf
		inline T& value() { return val; }				// Return a reference to the value of this QuadLeaf (for assignments)

		// QuadNode methods
		inline QuadTree<T>* const& son(int d) const { throw new std::domain_error("Not a QuadNode"); }	// Return the son of this quadtree in direction d
		inline QuadTree<T>*& son(int d) { throw new std::domain_error("Not a QuadNode"); }				// Return a reference to the son of this quadtree in direction d
};
