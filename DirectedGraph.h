//
// Created by barto on 19.05.18.
//

#ifndef GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_DIRECTEDGRAPH_H
#define GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_DIRECTEDGRAPH_H


#include "Graph.h"

class DirectedGraph : public Graph {
public:
	DirectedGraph();

	std::string getAvailableAlgorithms() override;

	void loadDataFrom(std::string fileName) override;

	void generate(int numberOfVertices, int density) override;

	std::string printIncidenceMatrix() override;

	std::string printAdjacencyList() override;

	void runAlgorithm(int index) override;

	void test() override;

};


#endif //GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_DIRECTEDGRAPH_H
