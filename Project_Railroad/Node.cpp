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
	this->known = false;
}

Node::Node(std::string name)
{
	this->name = name;
	this->nrOfConnections = 0;
	this->connectionCap = 10;
	this->connections = new Connection * [connectionCap] {nullptr};
	this->known = false;
}

void Node::addConnection(Node* otherNode, int cost)
{
	if (nrOfConnections == connectionCap)
	{
		expandConnections();
	}
	connections[nrOfConnections] = new Connection(cost, this, otherNode);
	otherNode->addConnection(connections[nrOfConnections]);
	nrOfConnections++;
	std::cout << "Connection Added between " << name << " And " << otherNode->getName() << "\nCost: " << cost << std::endl;
}

void Node::addConnection(Connection* connection)
{
	if (nrOfConnections == connectionCap)
	{
		expandConnections();
	}
	connections[nrOfConnections++] = connection;
	std::cout << "Connection Added from other node\n";
}

void Node::removeConnection(Node* otherNode)
{
	bool removed = false;
	for (int i = 0; i < nrOfConnections && !removed; i++)
	{
		if (connections[i]->checkNode(otherNode))
		{
			otherNode->removedByOther(connections[i]);
			delete connections[i];
			for (int y = i; y < nrOfConnections; y++)
			{
				connections[y] = connections[y + 1];
			}
			nrOfConnections--;
			removed = true;

		}
	}
}

void Node::removedByOther(Connection* connection)
{
	bool found = false;
	for (int i = 0; i < nrOfConnections && !found; i++)
	{
		if (connections[i] == connection)
		{
			for (int y = i; y < nrOfConnections; y++)
			{
				connections[y] = connections[y + 1];
			}
			found = true;
			nrOfConnections--;
		}
	}
}

std::string Node::getName() const
{
	return this->name;
}

bool Node::getKnown() const
{
	return known;
}

void Node::setKnown()
{
	known = true;
}

Node* Node::getLowestCostNode()
{
	Connection* currentLowest = connections[0];
	Node* toReturn = nullptr;
	for (int i = 0; i < nrOfConnections; i++)
	{
		if (connections[i]->getCost() < currentLowest->getCost())
		{
			if (connections[i]->getOtherNode(this)->getKnown() == false)
			{
				currentLowest = connections[i];
			}
		}
	}
	if (currentLowest->getOtherNode(this)->getKnown() == false)
	{
		toReturn = currentLowest->getOtherNode(this);
	}
	return toReturn;
}

std::vector<Connection*> Node::getConnectionsAsVector() const
{
	std::vector<Connection*> toReturn;
	for (int i = 0; i < nrOfConnections; i++)
	{
		toReturn.push_back(connections[i]);
	}
	return toReturn;
}



Node::~Node()
{
	for (int i = 0; i < nrOfConnections; i++)
	{
		connections[i] = nullptr;
	}
	delete[] connections;
}
