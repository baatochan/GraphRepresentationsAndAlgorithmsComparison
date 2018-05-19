//
// Created by barto on 19.05.18.
//

#include "DirectedGraph.h"

// public

DirectedGraph::DirectedGraph() : Graph("Graf skierowany", 1) {}

std::string DirectedGraph::getAvailableAlgorithms() {
	std::string output = "";

	output += "5. Algorytm Dijkstry (SP)\n";

	return output;
}

void DirectedGraph::loadDataFrom(std::string fileName) {

}

void DirectedGraph::generate(int numberOfVertices, int density) {

}

std::string DirectedGraph::printIncidenceMatrix() {
	return std::__cxx11::string();
}

std::string DirectedGraph::printAdjacencyList() {
	return std::__cxx11::string();
}

void DirectedGraph::runAlgorithm(int index) {

}

void DirectedGraph::test() {

}
