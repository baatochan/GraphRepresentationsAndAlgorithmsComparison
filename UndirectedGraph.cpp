//
// Created by barto on 19.05.18.
//

#include "UndirectedGraph.h"

using namespace std;

// public

UndirectedGraph::UndirectedGraph() : Graph("Graf nieskierowany", 1) {}

std::string UndirectedGraph::getAvailableAlgorithms() {
	std::string output = "";

	output += "5. Algorytm Prima (MST)\n";

	return output;
}

void UndirectedGraph::generate(int numberOfVertices, int density) {

}

void UndirectedGraph::runAlgorithm(int index) {

}

void UndirectedGraph::test() {

}

// private

void UndirectedGraph::loadRawDataToMatrix(vector<int> rawData) {

}

void UndirectedGraph::loadRawDataToList(std::vector<int> rawData) {

}
