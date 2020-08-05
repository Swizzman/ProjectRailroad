#include "Node.h"
#include <iostream>


Node::Node()
{
	this->name = "";

	this->known = false;
}

Node::Node(std::string name)
{
	this->name = name;

	this->known = false;
}

void Node::addConnection(Node* otherNode, int cost)
{
	Connection* temp = new Connection(cost, this, otherNode);
	connections.push_back(temp);
	otherNode->addConnection(temp);
}

void Node::addConnection(Connection* connection)
{
	connections.push_back(connection);

}

void Node::removeConnection(Node* otherNode)
{
	bool removed = false;
	for (int i = 0; i < connections.size() && !removed; i++)
	{
		if (connections.at(i)->checkNode(otherNode))
		{
			otherNode->removedByOther(connections.at(i));
			connections.erase(connections.begin() + i);

			removed = true;

		}
	}
}

void Node::removedByOther(Connection* connection)
{
	bool removed = false;
	for (int i = 0; i < connections.size() && !removed; i++)
	{
		if (connections.at(i) == connection)
		{
			connections.erase(connections.begin() + i);
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
	for (int i = 0; i < connections.size(); i++)
	{
		if (connections.at(i)->getCost() < currentLowest->getCost())
		{
			if (connections.at(i)->getOtherNode(this)->getKnown() == false)
			{
				currentLowest = connections.at(i);
			}
		}
	}
	if (currentLowest->getOtherNode(this)->getKnown() == false)
	{
		toReturn = currentLowest->getOtherNode(this);
	}
	return toReturn;
}

std::vector<Connection*> Node::getUnusedConnectionsAsVector()
{
	std::vector<Connection*> toReturn;
	for (int i = 0; i < connections.size(); i++)
	{
		if (!connections.at(i)->getUsed())
		{

			toReturn.push_back(connections.at(i));
		}

	}
	return toReturn;
}

std::vector<Connection*> Node::getUsedConnectionsAsVector()
{
	std::vector<Connection*> vec;
	for (int i = 0; i < connections.size(); i++)
	{
		if (connections.at(i)->getUsedVar() && connections.at(i)->checkIfFirst(this))
		{
			vec.push_back(connections.at(i));
		}
	}
	return vec;
}



Node::~Node()
{

}
