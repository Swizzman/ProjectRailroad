#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"Node.h"
#include<sstream>
#include <Windows.h>
#include <queue>
#include <functional>
#include <chrono>
using namespace std;
std::vector<string> openFile(string path);
void writeToFile(std::vector<Node*> arr, std::vector<Connection*> usedCon);
std::vector<int> findNode(std::vector<Node*> arr, string nodeName1, string nodeName2);
void primsMST(std::vector<Node*> arr);
bool cmp(Connection* l, Connection* r);
int main(int argc, char** argv)
{
	if (argc > 1)
	{
	int startI = 0;
	int nodeCap = 100;
	std::vector<Node*> nodes;

	std::cout << "File path specified, opening file\n";
	vector<string> vec = openFile(argv[1]);
	std::cout << "File opened\n";
	for (int i = 0; i < vec.size() && vec.at(i) != ""; i++)
	{

		nodes.push_back(new Node(vec.at(i)));
		startI++;
	}
	auto start = std::chrono::steady_clock::now();

	for (int i = startI + 1; i < vec.size(); i++)
	{
		string currentLine;
		currentLine = vec.at(i);
		stringstream ss(currentLine);
		string temp1;
		string temp2;
		int cost;
		ss >> temp1;
		ss >> temp2;
		ss >> cost;
		std::vector<int> tempIS = findNode(nodes, temp1, temp2);
		Connection* tempCon = new Connection(cost, nodes.at(tempIS.at(0)), nodes.at(tempIS.at(1)));
		nodes.at(tempIS.at(0))->addConnection(tempCon);
		nodes.at(tempIS.at(1))->addConnection(tempCon);
	}
	primsMST(nodes);
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Constructing MST took: " << elapsed_seconds.count() << " seconds" << std::endl;
	std::vector<Connection*> vec2;
	for (int i = 0; i < nodes.size(); i++)
	{
		std::vector<Connection*> tempVec = nodes.at(i)->getUsedConnectionsAsVector();
		for (int y = 0; y < tempVec.size(); y++)
		{
			vec2.push_back(tempVec.at(y));
		}
	}
	std::cout << "Vec2 Size: " << vec2.size() << std::endl;
	writeToFile(nodes, vec2);

}
else
{
	std::cout << "Please specify file path\n";
}
	return 0;
}

std::vector<string> openFile(string path)
{
	std::cout << path << endl;
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

void writeToFile(std::vector<Node*> arr, std::vector<Connection*> usedCon)
{
	ofstream fileOutput("Answers.txt");
	for (int i = 0; i < arr.size(); i++)
	{
		fileOutput << arr[i]->getName() << '\n';
	}
	fileOutput << '\n';
	for (int i = 0; i < usedCon.size(); i++)
	{
		fileOutput << usedCon.at(i)->getInfo() << '\n';
	}
	fileOutput.close();
}

std::vector<int> findNode(std::vector<Node*> arr, string nodeName1, string nodeName2)
{
	std::vector<int> temp;
	temp.push_back(-1);
	temp.push_back(-1);
	bool found1 = false;
	bool found2 = false;
	for (int i = 0; i < arr.size() && (!found1 || !found2); i++)
	{
		if (arr.at(i)->getName() == nodeName1)
		{
			found1 = true;
			temp.at(0) = i;
		}
		if (arr.at(i)->getName() == nodeName2)
		{
			found2 = true;
			temp.at(1) = i;
		}
	}
	return temp;
}

void primsMST(std::vector<Node*> arr)
{

	std::vector<Node*> visitedNodes;
	visitedNodes.push_back(arr.at(0));
	visitedNodes.at(0)->setKnown();
	std::priority_queue<Connection*, std::vector<Connection*>, decltype(&cmp)> queue(cmp);
	while (visitedNodes.size() < arr.size())
	{
		for (int i = 0; i < visitedNodes.size(); i++)
		{
			std::vector<Connection*> vec = visitedNodes.at(i)->getUnusedConnectionsAsVector();
			for (int y = 0; y < vec.size(); y++)
			{
				queue.emplace(vec.at(y));
			}
		}
		if (!queue.empty())
		{
			Connection* con = nullptr;
			con = queue.top();
			queue.pop();

			if (con)
			{
				Node* unknown = con->getUnkownNode();

				if (!unknown->getKnown())
				{
					con->setUsed();
					visitedNodes.push_back(unknown);
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

