//
// Created by barto on 19.05.18.
//

#ifndef GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_GRAPH_H
#define GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_GRAPH_H


#include <vector>
#include <forward_list>
#include <string>

class Graph {
protected:
	Graph(std::string name, int numberOfAvailableAlgorithms);

	// implementing it here as it is needed for adjacencyList declaration
	struct EdgeListElement {
		int edgeEnd;
		int value;
	};

	const std::string name;

	const int numberOfAvailableAlgorithms;

protected:

	std::vector<std::vector<int>> incidenceMatrix;

	std::vector<std::forward_list<EdgeListElement>> adjacencyList;

public:
	std::string getName();

	int getNumberOfAvailableAlgorithms();

	virtual std::string getAvailableAlgorithms()= 0;

	std::string printIncidenceMatrix();

	std::string printAdjacencyList();

	virtual void loadDataFrom(std::string fileName)= 0;

	virtual void generate(int numberOfVertices, int density)= 0;

	virtual void runAlgorithm(int index, int arg1, int arg2)= 0;

	virtual void test()= 0;

};


#endif //GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_GRAPH_H
