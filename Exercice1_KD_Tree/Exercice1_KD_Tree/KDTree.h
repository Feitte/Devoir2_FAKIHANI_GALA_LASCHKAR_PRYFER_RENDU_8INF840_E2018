#pragma once

#include <iostream>
#include <vector>

struct Point
{
	bool operator==(Point const& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator!=(Point const& rhs) const
	{
		return !(*this == rhs);
	}

	int x;
	int y;
};

float distance(Point const& a, Point const& b);
std::ostream& operator<<(std::ostream& os, Point const& p);

enum class Axis {X,Y};

class KDTree
{

public:
	KDTree * insert(Point const& p);
	KDTree * remove(Point const& p);
	bool exists(Point const& p) const;
	bool isEmpty() const;
	

private:
	class KDNode
	{
	public:
		KDNode(Point const& p);
		KDNode * insert(Point const& p, Axis const& axis);
		KDNode * remove(Point const& p, Axis const& axis);
		bool exists(Point const& p, Axis const& axis) const;
		bool isLeaf() const;

		friend std::ostream& operator<<(std::ostream& os, KDNode const& node);
		void displayInfix(std::ostream& os, int i = 1) const;

	private:

		std::vector<Point> getChildrenPoints() const;

		Point p;
		std::unique_ptr<KDNode> left;
		std::unique_ptr<KDNode> right;

	};

	std::unique_ptr<KDNode> root = nullptr;

	friend std::ostream& operator<<(std::ostream& os, KDTree::KDNode const& node);
	friend std::ostream& operator<<(std::ostream& os, KDTree const& tree);
};
