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

	void loadDataFrom(std::string fileName);

	virtual void generate(int numberOfVertices, int density)= 0;

	virtual std::string runAlgorithm(char index, char arg1, int arg2, int arg3)= 0;

	virtual void test()= 0;

protected:

	std::vector<int> loadRawDataFrom(std::string path);

	virtual void loadRawDataToMatrix(std::vector<int> rawData)= 0;
	virtual void loadRawDataToList(std::vector<int> rawData)= 0;

	bool edgeBeginningAvailable(int vertex);
	bool edgeEndAvailable(int beginning, int end);

	std::string printMatrix(std::vector<std::vector<int>> v);

};


#endif //GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_GRAPH_H
