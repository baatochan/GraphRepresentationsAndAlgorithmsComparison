//
// Created by barto on 19.05.18.
//

#include <cmath>
#include <random>
#include <climits>
#include "DirectedGraph.h"

using namespace std;

// public

DirectedGraph::DirectedGraph() : Graph("Graf skierowany", 1) {}

std::string DirectedGraph::getAvailableAlgorithms() {
	std::string output = "";

	output += "6. Algorytm Dijkstry (SP) [arg1 <- rodzaj reprezentacji (m - macierz, l - lista); arg2 <- wierzch. pocz.; arg3 <- wierzch. konc.]\n";

	return output;
}

void DirectedGraph::generate(int numberOfVertices, int density, int range) {
	double dens = (double)density / 100;
	dens *= numberOfVertices * (numberOfVertices - 1);
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
	std::uniform_int_distribution<int> randomValue(1, range);

	int beginningVertex = 0;
	int endVertex = 0;
	int value;
	bool edgeBeginningNotAvailable = true;
	bool edgeEndNotAvailable = true;

	// generate rand edges
	for (int i = 0; i < numberOfEdges; i++) {
		// random beggining
		edgeBeginningNotAvailable = true;
		while (edgeBeginningNotAvailable){
			beginningVertex = randomVertex(mt);
			edgeBeginningNotAvailable = !edgeBeginningAvailable(beginningVertex);
		};
		// random end
		edgeEndNotAvailable = true;
		while (edgeEndNotAvailable){
			endVertex = randomVertex(mt);
			edgeEndNotAvailable = !edgeEndAvailable(beginningVertex, endVertex);
		};

		value = randomValue(mt);

		adjacencyList[beginningVertex].push_front({endVertex, value});
		incidenceMatrix[i][beginningVertex] = value;
		incidenceMatrix[i][endVertex] = -1 * value;
	}

}

string DirectedGraph::runAlgorithm(char index, char arg1, int arg2, int arg3) {
	string output;

	if (index == 1) {
		if (arg1 == 0) {
			output = dijkstrasAlgorithmOnMatrix(arg2, arg3, true);
		} else if (arg1 == 1) {
			output = dijkstrasAlgorithmOnList(arg2, arg3, true);
		} else {
			throw "Nieznany blad!"; // should never be thrown
		}
	} else {
		throw "Algorytm nie istnieje!";
	}

	return output;
}

void DirectedGraph::test() {

}

// protected

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

// private

std::string DirectedGraph::dijkstrasAlgorithmOnMatrix(int beginVertex, int endVertex, bool print) {
	if (incidenceMatrix.size() == 0)
		throw "Graf pusty!";

	int numberOfVertices = incidenceMatrix[0].size();


	if (beginVertex >= numberOfVertices || endVertex >= numberOfVertices)
		throw "Poczatkowy lub koncowy wierzcholek nie istnieje!";

	// create needed arrays and assign default values
	vector<bool> visitedVertices;
	vector<unsigned long> pathLength;
	vector<int> previousVertex;
	visitedVertices.assign(numberOfVertices, false);
	pathLength.assign(numberOfVertices, ULONG_MAX);
	previousVertex.assign(numberOfVertices, -1);

	// assaing starting value
	pathLength[beginVertex] = 0;
	int currentVertex = beginVertex;
	unsigned long shortestPath;
	int shortestPathVertex;

	// run main loop for numberOfVertices times (every vertex will be visisted)
	for (int i = 0; i < numberOfVertices; i++) {
		unsigned long currentLength = pathLength[currentVertex];

		for (auto& row : incidenceMatrix) {
			if (row[currentVertex] > 0) {
				for (int j = 0; j < numberOfVertices; j++) {
					if (row[j] < 0) {
						if (pathLength[j] > currentLength + row[currentVertex]) {
							pathLength[j] = currentLength + row[currentVertex];
							previousVertex[j] = currentVertex;
						}
					}
				}
			}
		}

		visitedVertices[currentVertex] = true;

		shortestPath = ULONG_MAX;
		shortestPathVertex = -1;

		for (int j = 0; j < numberOfVertices; j++) {
			if (!visitedVertices[j]) {
				if (pathLength[j] < shortestPath) {
					shortestPath = pathLength[j];
					shortestPathVertex = j;
				}
			}
		}

		if ((i != numberOfVertices - 1) && (shortestPathVertex == -1))
			throw "Graf niespojny!";

		currentVertex = shortestPathVertex;

	}

	if (print) {
		string output;
		output = "Najkrotsza droga z wierzch.: " + to_string(beginVertex) + " do wierzch.: " + to_string(endVertex) +
		         " wynosi: " + to_string(pathLength[endVertex]) + ".\n";
		output += "Prowadzi nastepujaca droga: ";

		currentVertex = endVertex;

		output += to_string(currentVertex);

		while (currentVertex != beginVertex) {
			currentVertex = previousVertex[currentVertex];
			output += " <- " + to_string(currentVertex);
		}

		return output;
	}

	return "";
}

std::string DirectedGraph::dijkstrasAlgorithmOnList(int beginVertex, int endVertex, bool print) {
	if (adjacencyList.size() == 0)
		throw "Graf pusty!";

	int numberOfVertices = adjacencyList.size();


	if (beginVertex >= numberOfVertices || endVertex >= numberOfVertices)
		throw "Poczatkowy lub koncowy wierzcholek nie istnieje!";

	// create needed arrays and assign default values
	vector<bool> visitedVertices;
	vector<unsigned long> pathLength;
	vector<int> previousVertex;
	visitedVertices.assign(numberOfVertices, false);
	pathLength.assign(numberOfVertices, ULONG_MAX);
	previousVertex.assign(numberOfVertices, -1);

	// assaing starting value
	pathLength[beginVertex] = 0;
	int currentVertex = beginVertex;
	unsigned long shortestPath;
	int shortestPathVertex;

	// run main loop for numberOfVertices times (every vertex will be visisted)
	for (int i = 0; i < numberOfVertices; i++) {
		unsigned long currentLength = pathLength[currentVertex];

		for (auto& edge : adjacencyList[currentVertex]) {
			if (pathLength[edge.edgeEnd] > currentLength + edge.value){
				pathLength[edge.edgeEnd] = currentLength + edge.value;
				previousVertex[edge.edgeEnd] = currentVertex;
			}
		}

		visitedVertices[currentVertex] = true;

		shortestPath = ULONG_MAX;
		shortestPathVertex = -1;

		for (int j = 0; j < numberOfVertices; j++) {
			if (!visitedVertices[j]) {
				if (pathLength[j] < shortestPath) {
					shortestPath = pathLength[j];
					shortestPathVertex = j;
				}
			}
		}

		if ((i != numberOfVertices - 1) && (shortestPathVertex == -1))
			throw "Graf niespojny!";

		currentVertex = shortestPathVertex;

	}

	if (print) {
		string output;
		output = "Najkrotsza droga z wierzch.: " + to_string(beginVertex) + " do wierzch.: " + to_string(endVertex) +
		         " wynosi: " + to_string(pathLength[endVertex]) + ".\n";
		output += "Prowadzi nastepujaca droga: ";

		currentVertex = endVertex;

		output += to_string(currentVertex);

		while (currentVertex != beginVertex) {
			currentVertex = previousVertex[currentVertex];
			output += " <- " + to_string(currentVertex);
		}

		return output;
	}

	return "";
}