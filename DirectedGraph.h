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

	void generate(int numberOfVertices, int density) override;

	void runAlgorithm(int index) override;

	void test() override;

protected:
	void loadRawDataToMatrix(std::vector<int> rawData) override ;
	void loadRawDataToList(std::vector<int> rawData) override ;

};


#endif //GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_DIRECTEDGRAPH_H
