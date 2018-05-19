//
// Created by barto on 19.05.18.
//

#include "UndirectedGraph.h"

// public

UndirectedGraph::UndirectedGraph() : Graph("Graf nieskierowany", 1) {}

std::string UndirectedGraph::getAvailableAlgorithms() {
	std::string output = "";

	output += "5. Algorytm Prima (MST)\n";

	return output;
}

void UndirectedGraph::loadDataFrom(std::string fileName) {

}

void UndirectedGraph::generate(int numberOfVertices, int density) {

}

std::string UndirectedGraph::printIncidenceMatrix() {
	return std::__cxx11::string();
}

std::string UndirectedGraph::printAdjacencyList() {
	return std::__cxx11::string();
}

void UndirectedGraph::runAlgorithm(int index) {

}

void UndirectedGraph::test() {

}
