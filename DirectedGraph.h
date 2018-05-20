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

	void generate(int numberOfVertices, int density, int range) override;

	std::string runAlgorithm(char index, char arg1, int arg2, int arg3) override;

	void test() override;

protected:
	void loadRawDataToMatrix(std::vector<int> rawData) override ;
	void loadRawDataToList(std::vector<int> rawData) override ;

private:
	std::string dijkstrasAlgorithmOnMatrix(int beginVertex, int endVertex);
	std::string dijkstrasAlgorithmOnList(int beginVertex, int endVertex);

};


#endif //GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_DIRECTEDGRAPH_H
