#pragma once
#include <iostream>
using namespace std;
class Node;
class Connection
{
private:
	bool used;
	int cost;
	Node* node1;
	Node* node2;
public:
	Connection();
	Connection(int cost, Node* node1, Node* node2);
	virtual ~Connection();
	void addNode(Node* node);
	bool checkNode(Node* node);
	Node* getOtherNode(Node* thisNode) const;
	Node* getUnkownNode()const;
	int getCost() const;
	void setUsed();
	bool getUsed() const;
	bool getUsedVar() const;
	bool checkIfFirst(Node* node)const;
	std::string getInfo()const;
	bool operator <(Connection& other);
	bool operator >(Connection& other);
	friend ostream& operator<<(ostream& out, const Connection& c);
};

