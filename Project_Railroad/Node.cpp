#include "Node.h"
#include <iostream>
//void Node::expandConnections()
//{
//	connectionCap += 10;
//	Connection** temp = new Connection * [connectionCap] {nullptr};
//	for (int i = 0; i < nrOfConnections; i++)
//	{
//		temp[i] = connections[i];
//	}
//	delete[] connections;
//	connections = temp;
//	temp = nullptr;
//}

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
	//connections[nrOfConnections] = new Connection(cost, this, otherNode);
	otherNode->addConnection(temp);
	//nrOfConnections++;
	//std::cout << "Connection Added between " << name << " And " << otherNode->getName() << "\nCost: " << cost << std::endl;
}

void Node::addConnection(Connection* connection)
{
	connections.push_back(connection);
	//connections[nrOfConnections++] = connection;
	//std::cout << "Connection Added from other node\n";
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
			//otherNode->removedByOther(connections[i]);
			//delete connections[i];
			//for (int y = i; y < nrOfConnections; y++)
			//{
			//	connections[y] = connections[y + 1];
			//}
			//nrOfConnections--;
			removed = true;

		}
	}
}

void Node::removedByOther(Connection* connection)
{
	bool removed = false;
	for (int i = 0; i < nrOfConnections && !removed; i++)
	{
		if (connections.at(i) == connection)
		{
			connections.erase(connections.begin() + i);
			//for (int y = i; y < nrOfConnections; y++)
			//{
			//	connections[y] = connections[y + 1];
			//}
			//removed = true;
			//nrOfConnections--;
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

std::vector<Connection*> Node::getUnusedConnectionsAsVector()
{
	std::vector<Connection*> toReturn;
	//std::cout << connections.size() << std::endl;
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
