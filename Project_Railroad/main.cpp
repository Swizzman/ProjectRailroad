#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"Node.h"
#include "Priority_Queue.h"
#include<sstream>
using namespace std;
std::vector<string> openFile(string path);
int findNode(Node** arr, string nodeName, int nrOfNodes);
void primsMST(Node** arr, int nrOfNodes);
int main(int argc, char** argv)
{
	if (argc > 1)
	{
		int nrOfNodes = 0;
		int nodeCap = 100;
		Node** nodes = new Node * [nodeCap] {nullptr};
		int nrOfConnections = 0;
		int connectionCap = 100;
		Connection** connections = new Connection * [connectionCap] {nullptr};
		std::cout << "File path specified, opening file\n";
		vector<string> vec = openFile(argv[1]);
		cout << "File opened\n";

		for (int i = 0; i < vec.size(); i++)
		{
			cout << vec.at(i) << endl;
		}
		cout << "Vector Size: " << vec.size() << endl;
		for (int i = 0; i < vec.size() && vec.at(i) != ""; i++)
		{
			nodes[nrOfNodes++] = new Node(vec.at(i));
			//vec.erase(vec.begin());
		}
		//cout << vec.at(nrOfNodes) << endl;
		//for (int i = 0; i < nrOfNodes; i++)
		//{
		//	cout << nodes[i]->getName() << endl;
		//}
		for (int i = nrOfNodes+1; i < vec.size(); i++)
		{
			string currentLine;
			//cout << vec.at(i) << endl;
			currentLine = vec.at(i);
			stringstream ss(currentLine);
			string temp;
			ss >> temp;
			int tempI = findNode(nodes, temp, nrOfNodes);
			ss >> temp;
			int cost;
			ss >> cost;
			nodes[tempI]->addConnection(nodes[findNode(nodes, temp, nrOfNodes)], cost);
		}
		for (int i = 0; i < nrOfNodes; i++)
		{
			delete nodes[i];
		}
		delete[] nodes;
	}
	else
	{
		std::cout << "Please specify file path\n";
	}
	//(void)getchar();
	return 0;
}

std::vector<string> openFile(string path)
{
	vector<string> vec;
	ifstream fileInput(path);
	string currentLine;
	while (std::getline(fileInput, currentLine))
	{
		vec.push_back(currentLine);
	}
	fileInput.close();

	return vec;
}

int findNode(Node** arr, string nodeName, int nrOfNodes)
{
	bool found = false;
	int index = -1;
	for (int i = 0; i < nrOfNodes && !found; i++)
	{
		if (arr[i]->getName() == nodeName)
		{
			found = true;
			index = i;
		}
	}
	return index;
}

void primsMST(Node** arr, int nrOfNodes)
{
	int visitCap = 100;
	int nrOfVisited = 0;
	Node** visitedNodes = new Node * [visitCap] {nullptr};
	visitedNodes[0] = arr[0];
	visitedNodes[0]->setKnown();
	nrOfVisited++;
	Priority_Queue<Connection*> queue;
	while (nrOfVisited < nrOfNodes)
	{
		for (int i = 0; i < nrOfVisited; i++)
		{ 
			std::vector<Connection*> vec = visitedNodes[i]->getConnectionsAsVector();
		}
	}
	 
}
