//
// Created by barto on 19.05.18.
//

#ifndef GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_GRAPH_H
#define GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_GRAPH_H


#include <vector>
#include <forward_list>

class Graph {
protected:
	std::vector<std::vector<int>> incidenceMatrix;

	std::vector<std::forward_list> adjacencyList;
};


#endif //GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_GRAPH_H
