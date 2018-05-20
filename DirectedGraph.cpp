//
// Created by barto on 19.05.18.
//

#include "DirectedGraph.h"

using namespace std;

// public

DirectedGraph::DirectedGraph() : Graph("Graf skierowany", 1) {}

std::string DirectedGraph::getAvailableAlgorithms() {
	std::string output = "";

	output += "6. Algorytm Dijkstry (SP) [arg1 <- wierzch. pocz.; arg2 <- wierzch. konc.]\n";

	return output;
}

void DirectedGraph::generate(int numberOfVertices, int density) {

}

void DirectedGraph::runAlgorithm(int index, int arg1, int arg2) {

}

void DirectedGraph::test() {

}

// private

void DirectedGraph::loadRawDataToMatrix(std::vector<int> rawData) {
	incidenceMatrix.clear();
	int i = 0;
	incidenceMatrix.resize(rawData[i++]); // clear vector and resize to first item of raw data

	for (auto& row : incidenceMatrix) {
		row.assign(rawData[i], 0);
	}
	i++;

	for (int j = 0; j < incidenceMatrix.size(); j++) {
		int edgeBeginning = rawData[i++];
		int edgeEnd = rawData[i++];
		int edgeValue = rawData[i++];

		if (edgeBeginning == edgeEnd) {
			incidenceMatrix.clear();
			throw "Petle sa nieakceptowane!";
		}

		incidenceMatrix[j][edgeEnd] = edgeValue * -1;
		incidenceMatrix[j][edgeBeginning] = edgeValue;
	}
}

void DirectedGraph::loadRawDataToList(std::vector<int> rawData) {
	adjacencyList.clear();
	int i = 0;

	int numberOfEdges = rawData[i++];

	adjacencyList.resize(rawData[i++]);

	for (int j = 0; j < numberOfEdges; j++) {
		int edgeBeginning = rawData[i++];
		int edgeEnd = rawData[i++];
		int edgeValue = rawData[i++];

		if (edgeBeginning == edgeEnd) {
			incidenceMatrix.clear();
			throw "Petle sa nieakceptowane!";
		}

		adjacencyList[edgeBeginning].push_front({edgeEnd, edgeValue});
	}
}
