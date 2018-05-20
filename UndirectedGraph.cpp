//
// Created by barto on 19.05.18.
//

#include <random>
#include <queue>
#include <algorithm>
#include "UndirectedGraph.h"
#include "MinHeapElement.h"

using namespace std;

// public

UndirectedGraph::UndirectedGraph() : Graph("Graf nieskierowany", 1) {}

std::string UndirectedGraph::getAvailableAlgorithms() {
	std::string output = "";

	output += "6. Algorytm Prima (MST) [arg1 <- rodzaj reprezentacji (m - macierz, l - lista); arg2 <- 0; arg3 <- 0]\n";

	return output;
}

void UndirectedGraph::generate(int numberOfVertices, int density) {
	double dens = (double)density / 100;
	dens *= numberOfVertices * (numberOfVertices - 1);
	dens /= 2;
	int numberOfEdges = round(dens);

	// prepare matrix and list
	incidenceMatrix.clear();
	adjacencyList.clear();

	incidenceMatrix.resize(numberOfEdges);
	adjacencyList.resize(numberOfVertices);

	for (auto& row : incidenceMatrix) {
		row.assign(numberOfVertices, 0);
	}

	// declare rands
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> randomVertex(0, numberOfVertices - 1);
	// std::uniform_int_distribution<int> randomEdge(0, numberOfEdges - 1);
	// std::uniform_int_distribution<int> randomValue(1, 15);
	std::uniform_int_distribution<int> randomValue(1, INT32_MAX);

	int beginningVertex = 0;
	int endVertex = 0;
	int value;
	bool edgeBeginningNotAvailable = true;
	bool edgeEndNotAvailable = true;

	// generate rand edges
	for (int i = 0; i < numberOfEdges; i++) {
		// random beggining
		edgeBeginningNotAvailable = true;
		while (edgeBeginningNotAvailable) {
			beginningVertex = randomVertex(mt);
			edgeBeginningNotAvailable = !edgeBeginningAvailable(beginningVertex);
		};
		// random end
		edgeEndNotAvailable = true;
		while (edgeEndNotAvailable) {
			endVertex = randomVertex(mt);
			edgeEndNotAvailable = !edgeEndAvailable(beginningVertex, endVertex);
		};

		value = randomValue(mt);

		adjacencyList[beginningVertex].push_front({endVertex, value});
		adjacencyList[endVertex].push_front({beginningVertex, value});
		incidenceMatrix[i][beginningVertex] = value;
		incidenceMatrix[i][endVertex] = value;
	}
}

string UndirectedGraph::runAlgorithm(char index, char arg1, int arg2, int arg3) {
	string output;

	if (index == 1) {
		if (arg1 == 0) {
			output = primsAlgorithmOnMatrix();
		} else if (arg1 == 1) {
			output = primsAlgorithmOnList();
		} else {
			throw "Nieznany blad!"; // should never be thrown
		}
	} else {
		throw "Algorytm nie istnieje!";
	}

	return  output;
}

void UndirectedGraph::test() {

}

// protected

void UndirectedGraph::loadRawDataToMatrix(vector<int> rawData) {
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

		incidenceMatrix[j][edgeEnd] = edgeValue;
		incidenceMatrix[j][edgeBeginning] = edgeValue;
	}
}

void UndirectedGraph::loadRawDataToList(std::vector<int> rawData) {
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
		adjacencyList[edgeEnd].push_front({edgeBeginning, edgeValue});
	}
}

// private

string UndirectedGraph::primsAlgorithmOnMatrix() {
	// prepare vector for output
	vector<vector<int>> minimumSpanningTree;
	int numberOfVertices = incidenceMatrix[0].size();
	vector<int> foundVertices;
	priority_queue<MinHeapElement, vector<MinHeapElement>, MinHeapElementComparator> queue;

	// take first vertex
	int vertexID = 0;
	int edgeEnd;
	int edgeValue;
	int i;
	int j;

	foundVertices.push_back(vertexID);

	do {
		// look for edges from first vertices
		for (auto &row : incidenceMatrix) {
			if (row[vertexID] > 0) {
				edgeValue = row[vertexID];
				i = 0;
				edgeEnd = -1;
				for (auto &v : row) {
					if (i == vertexID) {
						i++;
						continue;
					}
					if (v > 0) {
						edgeEnd = i;
					}
					i++;
				}

				if (edgeEnd == -1)
					throw "Nieznany blad!"; // should never be thrown

				queue.push(MinHeapElement(vertexID, edgeEnd, edgeValue));

			}
		}

		do {
			MinHeapElement element = queue.top();
			edgeEnd = element.getEdgeEnd();
			edgeValue = element.getEdgeValue();
		} while (find(foundVertices.begin(), foundVertices.end(), edgeEnd) != foundVertices.end());

		foundVertices.push_back(edgeEnd);

		minimumSpanningTree.emplace_back();
		minimumSpanningTree[j].resize(numberOfVertices);

		minimumSpanningTree[j][vertexID] = edgeValue;
		minimumSpanningTree[j][edgeEnd] = edgeValue;

		vertexID = edgeEnd;
		j++;

	} while (foundVertices.size() < numberOfVertices && queue.size() > 0);

	if (foundVertices.size() < numberOfVertices)
		throw "Graf niespojny!";

	string output = "Minimalne drzewo rozpinajace\n";

	output += printMatrix(minimumSpanningTree);

	return output;
}

string UndirectedGraph::primsAlgorithmOnList() {
	throw "Algorytm jeszcze nie zaimplementowany!";
}
