#pragma once
#include <iostream>
#include "Connection.h"
class Priority_Queue
{
private:
	struct Node
	{
		Connection* element;
		Node* next = nullptr;
		Node(Connection*& element)
		{
			this->element = element;
		}
		virtual ~Node()
		{
			element = nullptr;
			next = nullptr;
		}

	};
	Node* root;
	void removeSpecificNode(Node* node);
public:
	Priority_Queue();
	virtual  ~Priority_Queue();
	void insert(Connection* element);
	bool getEmpty() const;
	Connection* getMin();
	void emptyQueue();
	
};



