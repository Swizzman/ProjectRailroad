#pragma once
#include <string>
#include "Connection.h"
#include <vector>
class Node
{
private:
	std::string name;
	std::vector<Connection*> connections;
	bool known;
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
	std::vector<Connection*> getUnusedConnectionsAsVector();
	std::vector<Connection*> getUsedConnectionsAsVector();
	virtual ~Node();
};

