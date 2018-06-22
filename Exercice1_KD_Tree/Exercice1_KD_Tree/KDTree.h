#pragma once

#include <iostream>

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
		KDNode * remove(Point const& p);
		bool exists(Point const& p) const;

		friend std::ostream& operator<<(std::ostream& os, KDNode const& node);
		void displayInfix(std::ostream& os, int i = 1) const;

	private:

		Point p;
		std::unique_ptr<KDNode> left;
		std::unique_ptr<KDNode> right;

	};

	std::unique_ptr<KDNode> root = nullptr;

	friend std::ostream& operator<<(std::ostream& os, KDTree::KDNode const& node);
	friend std::ostream& operator<<(std::ostream& os, KDTree const& tree);
};
