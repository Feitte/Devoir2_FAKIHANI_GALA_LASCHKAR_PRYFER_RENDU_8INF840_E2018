#include <iostream>
#include <random>
#include "KDTree.h"

int main()
{
	std::cout << distance({ 0,0 }, { 1,1 }) << std::endl;

	KDTree tree;
	int const NUMBER_OF_POINTS = 5;
	int const MIN_COORD = -5;
	int const MAX_COORD = 5;

	tree.insert({ 14,20 });

	//Initialize RNG to generate random points to fill the tree
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(MIN_COORD, MAX_COORD);
	
	for (int i = 0; i < NUMBER_OF_POINTS; i++)
		tree.insert({ uniform_dist(e1), uniform_dist(e1) });

	std::cout << tree
		<< std::boolalpha
		<< tree.exists({  3, 5 }) << std::endl
		<< tree.exists({ 14,20 }) << std::endl
		<< tree.exists({ -2, 4 }) << std::endl;

	tree.remove({ 14,20 });
	std::cout << tree << std::endl;

	system("pause");
    return EXIT_SUCCESS;
}

