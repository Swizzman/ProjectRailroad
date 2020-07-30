#pragma once
template <typename T>
class Priority_Queue
{
private:
	struct Node 
	{
		T element;
		Node* next = nullptr;
		Node(const T& element)
		{
			this->element = element;
		}
	};
	Node* root = nullptr;
	void removeNode(Node* node);
public:
	Priority_Queue();
	virtual  ~Priority_Queue();
	void insert(T element);
	T getMin();
};

template<typename T>
inline  void Priority_Queue<T>::removeNode(Node* node)
{
	if (node->next != nullptr)
	{
		node->element = node->next->element;
		removeNode(node->next);
	}
	else
	{
		delete node;
	}
}

template<typename T>
inline Priority_Queue<T>::Priority_Queue()
{
}

template<typename T>
inline Priority_Queue<T>::~Priority_Queue()
{
}

template<typename T>
inline void Priority_Queue<T>::insert(T element)
{
	Node* temp = new Node(element);
	temp->next = root;
	root = temp;
}

template<typename T>
inline T Priority_Queue<T>::getMin()
{
	Node* current = root;
	Node* lowest = current;
	T toReturn;
	if (!root)
	{
		throw "Queue is Empty";
	}
	while (current != nullptr)
	{
		if (current->element < lowest->element)
		{
			lowest = current;
		}
		current = current->next;
	}
	toReturn = lowest->element;
	removeNode(current);
	return toReturn;
}
