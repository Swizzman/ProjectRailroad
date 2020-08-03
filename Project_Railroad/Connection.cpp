#include "Connection.h"
#include "Node.h"
Connection::Connection()
{
	this->used = false;
	this->cost = 0;
	this->node1 = nullptr;
	this->node2 = nullptr;
}

Connection::Connection(int cost, Node* node1, Node* node2)
{
	this->used = false;
	this->cost = cost;
	this->node1 = node1;
	this->node2 = node2;
}

Connection::~Connection()
{
	node1 = nullptr;
	node2 = nullptr;
}

void Connection::addNode(Node* node)
{
}

bool Connection::checkNode(Node* node)
{
	bool found = false;
	if (node == node1 || node == node2)
	{
		found = true;
	}
	return found;
}

Node* Connection::getOtherNode(Node* thisNode) const
{
	return (thisNode == node1) ? node1 : node2;
}

Node* Connection::getUnkownNode() const
{
	Node* toReturn = nullptr;
	if (!node1->getKnown())
	{
		toReturn = node1;
	}
	else if (!node2->getKnown())
	{
		toReturn = node2;
	}
	return toReturn;
}

int Connection::getCost() const
{
	return cost;
}

void Connection::setUsed()
{
	this->used = true;
	node1->setKnown();
	node2->setKnown();
}

bool Connection::getUsed() const
{
	bool toReturn = false;
	if ((node1->getKnown() && node2->getKnown()) || used)
	{
		toReturn = true;
	}
	return toReturn;
}

bool Connection::getUsedVar() const
{
	return used;
}

bool Connection::checkIfFirst(Node* node) const
{
	bool isFirst = false;
	if (node == node1)
	{
		isFirst = true;
	}
	return isFirst;
}

std::string Connection::getInfo() const
{
	return  node1->getName() + '\t' + node2->getName() + '\t' + std::to_string(cost);
}

bool Connection::operator<(Connection& other)
{
	return cost < other.cost;
}

bool Connection::operator>(Connection& other)
{
	return cost > other.cost;
}

ostream& operator<<(ostream& out, const Connection& c)
{
	out << c.cost;
	return out;
}
