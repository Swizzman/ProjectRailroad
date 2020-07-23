#pragma once
class Node;
class Connection
{
private:
	int cost;
	Node* node1;
	Node* node2;
public:
	Connection();
	Connection(int cost, Node* node1, Node* node2);
	virtual ~Connection();
	void addNode(Node* node);
	bool checkNode(Node* node);
	int getCost() const;
};

