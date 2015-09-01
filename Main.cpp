#include <iostream>
#include "DependencyGraph.h"
#include <list>

int main(int argc, char *argv[])
{
	DependencyGraph<int> *myGraph = new DependencyGraph<int>();

	myGraph->addDirectedEdge((int)1, (int)2);
	myGraph->addDirectedEdge((int)1, (int)3);

	myGraph->addDirectedEdge((int)8, (int)2);
	myGraph->addDirectedEdge((int)6, (int)3);

	myGraph->addDirectedEdge((int)4, (int)5);
	myGraph->addDirectedEdge((int)4, (int)6);
	myGraph->addDirectedEdge((int)4, (int)7);
	myGraph->addDirectedEdge((int)4, (int)8);
	myGraph->addDirectedEdge((int)4, (int)1);

	myGraph->addDirectedEdge((int)2, (int)9);
	myGraph->addDirectedEdge((int)3, (int)9);

	std::list<Node<int>*> *depList = myGraph->populateDependencyList();

	for (auto it : *depList)
	{
		std::cout << it->getValue() << ",";
	}

	std::cout << std::endl;

	myGraph->refreshDepList();

	myGraph->addDirectedEdge((int)9, (int)4);
	depList = myGraph->populateDependencyList();

	std::cout << std::endl;

	for (auto it : *depList)
	{
		std::cout << it->getValue() << ",";
	}

	std::cout << std::endl;
	delete myGraph;

	std::cin.ignore();
}