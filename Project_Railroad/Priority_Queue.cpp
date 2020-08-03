#include "Priority_Queue.h"
void Priority_Queue::removeSpecificNode(Node* node)
{
	if (node->next != nullptr)
	{
		//std::cout << "Node has next\n";
		Node* temp = node->next;
		node->element = temp->element;
		node->next = temp->next;
		delete temp;
		temp = nullptr;
	}
	else
	{
		if (node == root && root->next == nullptr)
		{
			delete root;
		}
		else
		{
			delete node;

		}
		//std::cout << "Node is Alone\n";
	}

}

Priority_Queue::Priority_Queue()
{
	root = nullptr;
}
Priority_Queue::~Priority_Queue()
{
}
void Priority_Queue::insert(Connection* element)
{

	Node* temp = new Node(element);
	temp->next = root;
	root = temp;

}
bool Priority_Queue::getEmpty() const
{
	bool toReturn = false;
	if (root == nullptr)
	{
		toReturn = true;
	}
	return toReturn;
}
Connection* Priority_Queue::getMin()
{
	Node* current = root;
	Node* lowest = root;
	Connection* toReturn = nullptr;
	if (!root)
	{
		throw "Queue is Empty";
	}
	bool end = false;
	while (current && !end)
	{
		//std::cout << "Current: " << *current->element << std::endl;
		//std::cout << "Lowest: " << *lowest->element << endl;
		//std::cout << "Comparing connections\n";
		if (*current->element < *lowest->element)
		{
			//cout << "Found Lower\n";
			lowest = current;
		}
		if (current->next != nullptr)
		{

			current = current->next;
		}
		else
		{
			end = true;
		}

	}
	std::cout << "Final Lowest: " << *lowest->element << endl;

	toReturn = lowest->element;
	//std::cout << "Attempting to remove " << *lowest->element << "\n";
	removeSpecificNode(lowest);
	//std::cout << "Node Removed, Returning " << *toReturn << "\n";
	return toReturn;
}

void Priority_Queue::emptyQueue()
{
	int counter = 0;
	while (root != nullptr)
	{
		std::cout << "Removal " << counter << endl;
		if (root)
		{

			removeSpecificNode(root);
		}
		counter++;
	}
}
