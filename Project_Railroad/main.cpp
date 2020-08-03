#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"Node.h"
#include "Priority_Queue.h"
#include<sstream>
#include <Windows.h>
#include <queue>
#include <functional>
using namespace std;
std::vector<string> openFile(string path);
void writeToFile(Node** arr, int nrOfNodes, std::vector<Connection*> usedCon);
int findNode(Node** arr, string nodeName, int nrOfNodes);
void primsMST(Node** arr, int nrOfNodes);
bool cmp(Connection* l, Connection* r);
int main(int argc, char** argv)
{
	if (argc > 1)
	{
		int nrOfNodes = 0;
		int nodeCap = 100;
		Node** nodes = new Node * [nodeCap] {nullptr};

		std::cout << "File path specified, opening file\n";
		vector<string> vec = openFile(argv[1]);
		std::cout << "File opened\n";

		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << vec.at(i) << endl;
		}
		std::cout << "Vector Size: " << vec.size() << endl;
		for (int i = 0; i < vec.size() && vec.at(i) != ""; i++)
		{
			nodes[nrOfNodes++] = new Node(vec.at(i));
		}

		for (int i = nrOfNodes + 1; i < vec.size(); i++)
		{
			string currentLine;
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
		std::cout << "Running Prims algorithm\n";
		primsMST(nodes, nrOfNodes);
		std::cout << "Prims algorithm run\n";
		std::vector<Connection*> vec2;
		for (int i = 0; i < nrOfNodes; i++)
		{
			std::vector<Connection*> tempVec = nodes[i]->getUsedConnectionsAsVector();
			for (int y = 0; y < tempVec.size(); y++)
			{

				vec2.push_back(tempVec.at(y));
			}
		}
		std::cout << "Vec2 Size: " << vec2.size() << std::endl;
		writeToFile(nodes, nrOfNodes, vec2);

		for (int i = 0; i < vec2.size(); i++)
		{
			std::cout << vec2.at(i)->getInfo() << std::endl;
		}
		for (int i = 0; i < nrOfNodes; i++)
		{
			delete nodes[i];
		}
		delete[] nodes;
	}
	else
	{
		int nrOfNodes = 0;
		int nodeCap = 100;
		Node** nodes = new Node * [nodeCap] {nullptr};

		std::cout << "File path specified, opening file\n";
		vector<string> vec = openFile("C:\\Users\\Swizzman\\Desktop\\Programmering\\BTH\\DV1538\\ProjectRailroad\\testdata\\Nodes4.txt");
		std::cout << "File opened\n";

		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << vec.at(i) << endl;
		}
		std::cout << "Vector Size: " << vec.size() << endl;
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
		for (int i = nrOfNodes + 1; i < vec.size(); i++)
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
		std::cout << "Running Prims algorithm\n";
		primsMST(nodes, nrOfNodes);
		std::cout << "Prims algorithm run\n";
		std::vector<Connection*> vec2;
		for (int i = 0; i < nrOfNodes; i++)
		{
			std::vector<Connection*> tempVec = nodes[i]->getUsedConnectionsAsVector();
			for (int y = 0; y < tempVec.size(); y++)
			{

				vec2.push_back(tempVec.at(y));
			}
		}
		std::cout << "Vec2 Size: " << vec2.size() << std::endl;
		for (int i = 0; i < vec2.size(); i++)
		{
			std::cout << vec2.at(i)->getInfo() << std::endl;
		}
		writeToFile(nodes, nrOfNodes, vec2);

		for (int i = 0; i < nrOfNodes; i++)
		{
			delete nodes[i];
		}
		delete[] nodes;
		//std::cout << "Please specify file path\n";
	}
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

void writeToFile(Node** arr, int nrOfNodes, std::vector<Connection*> usedCon)
{
	ofstream fileOutput("Answers.txt");
	for (int i = 0; i < nrOfNodes; i++)
	{
		fileOutput << arr[i]->getName() << '\n';
	}
	fileOutput << '\n';
	for (int i = 0; i < usedCon.size(); i++)
	{
		fileOutput <<usedCon.at(i)->getInfo() << '\n';
	}
	fileOutput.close();
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
	std::priority_queue<Connection*, std::vector<Connection*>, decltype(&cmp)> queue(cmp);

	while (nrOfVisited < nrOfNodes)
	{
		for (int i = 0; i < nrOfVisited; i++)
		{
			std::vector<Connection*> vec = visitedNodes[i]->getUnusedConnectionsAsVector();
			for (int y = 0; y < vec.size(); y++)
			{
				queue.emplace(vec.at(y));
			}

		}
		if (!queue.empty())
		{

			Connection* con = nullptr;

			while (con == nullptr || con->getUsed() == true)
			{
				con = queue.top();
				queue.pop();

			}
			if (con)
			{
				Node* unknown = con->getUnkownNode();

				if (!unknown->getKnown())
				{
					con->setUsed();
					visitedNodes[nrOfVisited++] = unknown;
				}
			}
			queue = std::priority_queue<Connection*, std::vector<Connection*>, decltype(&cmp)>(cmp);
		}
	}

}

bool cmp(Connection* l, Connection* r)
{
	return l->getCost() > r->getCost();
}
