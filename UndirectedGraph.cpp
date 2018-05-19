//
// Created by barto on 19.05.18.
//

#include "UndirectedGraph.h"

// public

UndirectedGraph::UndirectedGraph() : Graph("Graf nieskierowany", 1) {}

std::string UndirectedGraph::getAvailableAlgorithms() {
	std::string output = "";

	output += "6. Algorytm Prima (MST) [arg1 <- 0; arg2 <- 0]\n";

	return output;
}

void UndirectedGraph::loadDataFrom(std::string fileName) {

}

void UndirectedGraph::generate(int numberOfVertices, int density) {

}

void UndirectedGraph::runAlgorithm(int index, int arg1, int arg2) {

}

void UndirectedGraph::test() {

}
