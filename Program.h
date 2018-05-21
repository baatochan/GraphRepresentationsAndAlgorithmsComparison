//
// Created by barto on 19.05.18.
//

#ifndef GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_PROGRAM_H
#define GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_PROGRAM_H


#include "DirectedGraph.h"
#include "UndirectedGraph.h"

class Program {
private:
	Graph* graph;

public:
	void start();

private:
	void printGraphTypeSelect();

	void printGraphMenu();

	std::string runAlgorithm(char index);
};


#endif //GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_PROGRAM_H
