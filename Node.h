#ifndef _NODE_H
#define _NODE_H

#include <unordered_map>

template<typename K>
class Node
{
private:
	K value;
	std::unordered_map<K, Node*> *adjList;
	int status;

public:
	enum
	{
		UNVISITED,
		VISITING,
		VISITED
	};
	Node(K newValue)
		: value(newValue)
		, adjList(new std::unordered_map<K, Node*>())
		, status(Node::UNVISITED)
	{}

	~Node()
	{
		delete adjList;
	}

	std::unordered_map<K, Node*> *getAdjList()
	{
		return adjList;
	}

	void addAdjNode(Node* adjNode)
	{
		adjList->insert(std::pair<K, Node*> (adjNode->getValue(), adjNode));
	}

	int getStatus()
	{
		return status;
	}

	void setStatus(int newStatus)
	{
		status = newStatus;
	}

	K getValue()
	{
		return value;
	}
};

#endif