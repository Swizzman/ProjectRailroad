#pragma once
#include <string>
#include "Connection.h"
class Node
{
private:
	std::string name;
	int nrOfConnections;
	int connectionCap;
	Connection** connections;
	void expandConnections();
public:
	Node();
	Node(std::string name);
	void addConnection(Node* otherNode, int cost);
	void removeConnection(Node* otherNode);
	std::string getName() const;
	virtual ~Node();
};

