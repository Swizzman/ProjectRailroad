#pragma once
#include <string>
#include "Connection.h"
#include <vector>
class Node
{
private:
	std::string name;
	int nrOfConnections;
	int connectionCap;
	Connection** connections;
	bool known;
	void expandConnections();
public:
	Node();
	Node(std::string name);
	void addConnection(Node* otherNode, int cost);
	void addConnection(Connection* connection);
	void removeConnection(Node* otherNode);
	void removedByOther(Connection * connection);
	std::string getName() const;
	bool getKnown() const;
	void setKnown();
	Node* getLowestCostNode();
	std::vector<Connection*> getConnectionsAsVector() const;
	virtual ~Node();
};

