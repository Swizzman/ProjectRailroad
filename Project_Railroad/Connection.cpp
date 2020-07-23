#include "Connection.h"
#include "Node.h"
Connection::Connection()
{
	this->cost = 0;
	this->node1 = nullptr;
	this->node2 = nullptr;
}

Connection::Connection(int cost, Node* node1, Node* node2)
{
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

int Connection::getCost() const
{
	return 0;
}
