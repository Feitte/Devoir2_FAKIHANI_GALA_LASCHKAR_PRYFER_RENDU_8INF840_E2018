#include "KDTree.h"

/////////////////////////////////////////////
//////           KD-TREE                /////
/////////////////////////////////////////////

KDTree * KDTree::insert(Point const & p)
{
	if (isEmpty())
		root = std::unique_ptr<KDNode>(new KDNode(p));
	else
		root->insert(p, Axis::X);
	return this;
}

KDTree * KDTree::remove(Point const & p)
{
	if (!isEmpty())
		root->remove(p);
	return this;
}

bool KDTree::exists(Point const & p) const
{
	return isEmpty() ? false : root->exists(p);
}

bool KDTree::isEmpty() const
{
	return root == nullptr;
}

/////////////////////////////////////////////
//////           KD-NODE                /////
/////////////////////////////////////////////

KDTree::KDNode::KDNode(Point const& p) : p(p)
{}

KDTree::KDNode * KDTree::KDNode::insert(Point const & p, Axis const & axis)
{
	if (this->p != p)
	{
		if (axis == Axis::X)
		{
			if (p.x >= this->p.x)
			{
				if (right == nullptr) right = std::unique_ptr < KDTree::KDNode >(new KDTree::KDNode(p));
				else right->insert(p, Axis::Y);
			}
			else if(p.x < this->p.x)
			{
				if (left == nullptr)	left = std::unique_ptr<KDTree::KDNode>(new KDTree::KDNode(p));
				else					left->insert(p, Axis::Y);
			}
		}
		else if (axis == Axis::Y)
		{
			if (p.y >= this->p.y)
			{
				if (right == nullptr) right = std::unique_ptr < KDTree::KDNode >(new KDTree::KDNode(p));
				else right->insert(p, Axis::X);
			}
			else if (p.y < this->p.y)
			{
				if (left == nullptr)	left = std::unique_ptr<KDTree::KDNode>(new KDTree::KDNode(p));
				else					left->insert(p, Axis::X);
			}
		}
	}

	return this;
}

KDTree::KDNode * KDTree::KDNode::remove(Point const & p)
{
	return nullptr;
}

bool KDTree::KDNode::exists(Point const& p) const
{
	return false;
}

/////////////////////////////////////////////
//////           Display                /////
/////////////////////////////////////////////


std::ostream & operator<<(std::ostream & os, Point const & p)
{
	os << "{" << p.x << "," << p.y << "}";
	return os;
}

std::ostream& operator<<(std::ostream & os, KDTree::KDNode const& node)
{
	os << node.p;
	return os;
}

std::ostream& operator<<(std::ostream& os, KDTree const& tree)
{
	if (tree.isEmpty())
		os << "This KD-Tree is empty";
	else
	{
		os << "Starting infix KD-Tree display :" << std::endl;
		tree.root->displayInfix(os);
	}
	return os;
}

/*
	Affiche récursivement l'arbre dans le flux en numérotant les noeuds comme si on faisait un parcours en largeur d'un arbre complet
	Cela permet de mieux se rendre compte d'où les noeuds ont été ajoutés
*/
void KDTree::KDNode::displayInfix(std::ostream& os, int i) const
{
	os << "Noeud #" << i << ": " << *this << std::endl;
	if (left != nullptr) left->displayInfix(os, 2*i);
	if (right != nullptr) right->displayInfix(os, 2*i+1);
}
