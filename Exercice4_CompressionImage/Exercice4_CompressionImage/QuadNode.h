#pragma once
using namespace std;

/*------------------------------------------------------------------------*
 * A branching node of a quadtree, whose leaves contain a value of type T *
 *------------------------------------------------------------------------*/

template <typename T>
class QuadNode : public QuadTree<T> {
	QuadTree<T>* sons[nQuadDir];	// The sons of this node for the 4 quadrant directions

	public:
		inline bool isLeaf() const { return false; }	// Tell if this quadtree is a leaf

		QuadNode();	// Construct a new branching node with empty (null) sons		
		QuadNode(QuadTree<T>* qtrees[]);	// Construct a new branching node given an array of 4 quadtrees 
		QuadNode(QuadTree<T>* son0, QuadTree<T>* son1, QuadTree<T>* son2, QuadTree<T>* son3);	// Construct a new branching node given 4 sons
		~QuadNode();	// Destruct this QuadNode and, recursively, subtrees

		// Return the number of leaves in this qtree
		inline int nLeaves() const {
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
		inline const T value() const { throw new domain_error("Not a QuadLeaf"); }	// Return the value of this QuadTree 
		inline T& value() { throw new domain_error("Not a QuadLeaf"); }				// Return a reference to the value of this QuadTree

		// QuadNode methods
		inline QuadTree<T>* const& son(int d) const {	// Return the son of this quadtree in direction d 
			if (!(0 <= d && d < nQuadDir)) {			// Make sure the direction makes sense
				ostringstream oss; oss << d;
				throw new out_of_range("Not a valid direction: " + oss.str());
			}
			return sons[d];
		}
};
