#include "KDTree.h"
#include <cmath>

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
	{
		if (p == root->p)
		{
			std::vector<Point> pointsToReinsert = root->getChildrenPoints();
			root = nullptr;
			for (auto& point : pointsToReinsert)
				this->insert(point);
		}
		else
			root->remove(p, Axis::X);
	}
	return this;
}

bool KDTree::exists(Point const & p) const
{
	if (isEmpty())
		return false;
	else
		root->exists(p, Axis::X);
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

KDTree::KDNode * KDTree::KDNode::remove(Point const & p, Axis const& axis)
{
	if (axis == Axis::X)
	{
		if (p.x >= this->p.x && right != nullptr)
		{
			if (p == right->p)
			{
				if (right->isLeaf())
					right = nullptr;
				else
				{
					std::vector<Point> pointsToReinsert = right->getChildrenPoints();
					right = nullptr;
					for (auto& point : pointsToReinsert)
						insert(point, axis);
				}
			}
			else
				right->remove(p, Axis::Y);
		}
		else if (p.x < this->p.x && left != nullptr)
		{
			if (p == left->p)
			{
				if (left->isLeaf())
					left = nullptr;
				else
				{
					std::vector<Point> pointsToReinsert = left->getChildrenPoints();
					left = nullptr;
					for (auto& point : pointsToReinsert)
						insert(point, axis);
				}
			}
			else
				left->remove(p, Axis::Y);
		}
	}
	else if (axis == Axis::Y)
	{
		if (p.y >= this->p.y && right != nullptr)
		{
			if (p == right->p)
			{
				if (right->isLeaf())
					right = nullptr;
				else
				{
					std::vector<Point> pointsToReinsert = right->getChildrenPoints();
					right = nullptr;
					for (auto& point : pointsToReinsert)
						insert(point, axis);
				}
			}
			else
				right->remove(p, Axis::X);
		}
		else if (p.x < this->p.x && left != nullptr)
		{
			if (p == left->p)
			{
				if (left->isLeaf())
					left = nullptr;
				else
				{
					std::vector<Point> pointsToReinsert = left->getChildrenPoints();
					left = nullptr;
					for (auto& point : pointsToReinsert)
						insert(point, axis);
				}
			}
			else
				left->remove(p, Axis::X);
		}
	}

	return this;
}

bool KDTree::KDNode::exists(Point const& p, Axis const& axis) const
{
	if (p == this->p)
		return true;
	else if (axis == Axis::X)
	{
		if (p.x >= this->p.x)
		{
			if (right == nullptr)
				return false;
			else
				return right->exists(p, Axis::Y);
		}

		else
		{
			if (left == nullptr)
				return false;
			else
				return left->exists(p, Axis::Y);
		}
			
	}

	else if (axis == Axis::Y)
	{
		if (p.y >= this->p.y)
		{
			if (right == nullptr)
				return false;
			else
				return right->exists(p, Axis::X);
		}

		else
		{
			if (left == nullptr)
				return false;
			else
				return left->exists(p, Axis::X);
		}
	}
}

bool KDTree::KDNode::isLeaf() const
{
	return right == nullptr && left == nullptr;
}

std::vector<Point> KDTree::KDNode::getChildrenPoints() const
{
	std::vector<Point> points = std::vector<Point>();
	return _getChildrenPoints(points);
}

std::vector<Point> KDTree::KDNode::_getChildrenPoints(std::vector<Point>& points) const
{
	if (left != nullptr)
	{
		points.push_back(left->p);
		left->_getChildrenPoints(points);
	}

	if (right != nullptr)
	{
		points.push_back(right->p);
		right->_getChildrenPoints(points);
	}

	return points;
}

/////////////////////////////////////////////
//////           Point                  /////
/////////////////////////////////////////////

float distance(Point const& a, Point const& b)
{
	int dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
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
		os << "End of KD-Tree";
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
