//
// Created by barto on 19.05.18.
//

#ifndef GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_UNDIRECTEDGRAPH_H
#define GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_UNDIRECTEDGRAPH_H


#include "Graph.h"

class UndirectedGraph : public Graph {
public:
	UndirectedGraph();

	std::string getAvailableAlgorithms() override;

	void generate(int numberOfVertices, int density) override;

	void runAlgorithm(int index, int arg1, int arg2) override;

	void test() override;

protected:
	void loadRawDataToMatrix(std::vector<int> rawData) override ;
	void loadRawDataToList(std::vector<int> rawData) override ;

};


#endif //GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_UNDIRECTEDGRAPH_H
