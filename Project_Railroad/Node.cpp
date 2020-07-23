#include "Node.h"
#include <iostream>
void Node::expandConnections()
{
	connectionCap += 10;
	Connection** temp = new Connection * [connectionCap] {nullptr};
	for (int i = 0; i < nrOfConnections; i++)
	{
		temp[i] = connections[i];
	}
	delete[] connections;
	connections = temp;
	temp = nullptr;
}

Node::Node()
{
	this->name = "";
	this->nrOfConnections = 0;
	this->connectionCap = 10;
	this->connections = new Connection * [connectionCap] {nullptr};
}

Node::Node(std::string name)
{
	this->name = name;
	this->nrOfConnections = 0;
	this->connectionCap = 10;
	this->connections = new Connection * [connectionCap] {nullptr};
}

void Node::addConnection(Node* otherNode, int cost)
{
	if (nrOfConnections == connectionCap)
	{
		expandConnections();
	}
	connections[nrOfConnections++] = new Connection(cost, this, otherNode);
	std::cout << "Connection Added between " << name << " And " << otherNode->getName() << "\nCost: " << cost << std::endl;
}

void Node::removeConnection(Node* otherNode)
{
	for (int i = 0; i < nrOfConnections; i++)
	{
		if (connections[i]->checkNode(otherNode))
		{

		}
	}
}

std::string Node::getName() const
{
	return this->name;
}


Node::~Node()
{
	for (int i = 0; i < nrOfConnections; i++)
	{
		connections[i] = nullptr;
	}
	delete[] connections;
}
