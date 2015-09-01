#ifndef _DEPENDENCY_GRAPH
#define _DEPENDENCY_GRAPH

#include "Node.h"
#include <unordered_map>

template<typename K>
class DependencyGraph
{
private:
	std::unordered_map<K, Node<K>*> *graphNodes;
	std::list<Node<K>*>* depList;

public:
	void addDirectedEdge(K source, K dest);
	Node<K> *createNode(K value);

	std::list<Node<K>*>* populateDependencyList();
	void dfsVisit(Node<K>* curNode);
	void refreshDepList();

	DependencyGraph();
	~DependencyGraph();
};

template<typename K>
void DependencyGraph<K>::addDirectedEdge(K source, K dest)
{
	Node<K>* srcNode = createNode(source);
	Node<K>* destNode = createNode(dest);

	if (srcNode == NULL || destNode == NULL)
	{
		std::cerr << "Cannot create a node" << std::endl;
		exit(1);
	}


	if (srcNode->getAdjList()->find(dest) == srcNode->getAdjList()->end())
	{
		srcNode->addAdjNode(destNode);
	}
}

template<typename K>
Node<K>* DependencyGraph<K>::createNode(K value)
{
	std::unordered_map<K, Node<K>*>::iterator it = graphNodes->find(value);

	if (it == graphNodes->end())
	{
		Node<K>* newNode = new Node<K>(value);
		graphNodes->insert(std::pair<K, Node<K>*>(value, newNode));
		return newNode;
	}
	else
	{
		return it->second;
	}
}

template<typename K>
std::list<Node<K>*>* DependencyGraph<K>::populateDependencyList()
{
	for (auto it : *graphNodes)
	{
		if (it.second->getStatus() == Node<K>::UNVISITED)
		{
			dfsVisit(it.second);
		}
	}

	return depList;
}

template<typename K>
void DependencyGraph<K>::dfsVisit(Node<K>* curNode)
{
	curNode->setStatus(Node<K>::VISITING);
	std::unordered_map<K, Node<K>*> *curAdjList = curNode->getAdjList();

	for (auto it : *(curAdjList))
	{
		if (it.second->getStatus() == Node<K>::UNVISITED)
		{
			dfsVisit(it.second);
		}
		else if (it.second->getStatus() == Node<K>::VISITING)
		{
			std::cerr << "Detected Cycle" << std::endl;
			std::cin.ignore();
			exit(1);
		}
	}
	curNode->setStatus(Node<K>::VISITED);
	depList->push_front(curNode);
}

template<typename K>
DependencyGraph<K>::DependencyGraph()
{
	graphNodes = new std::unordered_map<K, Node<K>*>();
	depList = new std::list<Node<K>*>();
}

template<typename K>
DependencyGraph<K>::~DependencyGraph()
{
	for (auto it : *graphNodes)
	{
		delete it.second;
	}

	delete graphNodes;
	delete depList;
}

template<typename K>
void DependencyGraph<K>::refreshDepList()
{
	for (auto it : *graphNodes)
	{
		it.second->setStatus(Node<K>::UNVISITED);
	}

	delete depList;
	depList = new std::list<Node<K>*>();
}

#endif