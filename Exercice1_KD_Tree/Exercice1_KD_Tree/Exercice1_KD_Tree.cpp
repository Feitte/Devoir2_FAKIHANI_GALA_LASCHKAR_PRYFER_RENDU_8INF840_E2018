#include <iostream>
#include "KDTree.h"

int main()
{
	KDTree tree;
	tree.insert({ 10,10 })
		->insert({ 10, 20 })
		->insert({ 10, 15 })
		->insert({ 14,165 });

	std::cout << tree;

	system("pause");
    return 0;
}

