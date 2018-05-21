//
// Created by barto on 19.05.18.
//

#include <random>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctime>
#include "UndirectedGraph.h"
#include "MinHeapElement.h"
#include "Counter.h"

using namespace std;

// public

UndirectedGraph::UndirectedGraph() : Graph("Graf nieskierowany", 1) {}

std::string UndirectedGraph::getAvailableAlgorithms() {
	std::string output = "";

	output += "6. Algorytm Prima (MST) [arg1 <- rodzaj reprezentacji (m - macierz, l - lista); arg2 <- 0; arg3 <- 0]\n";

	return output;
}

void UndirectedGraph::generate(int numberOfVertices, int density, int range) {
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
			output = primsAlgorithmOnMatrix(true);
		} else if (arg1 == 1) {
			output = primsAlgorithmOnList(true);
		} else {
			throw "Nieznany blad!"; // should never be thrown
		}
	} else {
		throw "Algorytm nie istnieje!";
	}

	return  output;
}

void UndirectedGraph::test() {
	int numberOfElements[5] = {50, 100, 150, 200, 250};
	int density[4] = {25, 50, 75, 99};
	char representationType[2] = {'M', 'L'};
	int range = 1000;
	int numberOfTests = 100;
	string path;
	double sumOfResults;
	Counter counter;
	double result = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 2; k++) {
				path = "..\\wyniki\\";
				path += to_string(time(0));
				path += "-gNieskierowany-algorytmPrima-n" + to_string(numberOfElements[i]) + "-g" +
				        to_string(density[j]) + "-r" + representationType[k] + ".txt";

				cout << "Test - Graf: Nieskierowany - Algorytm: Prima - Ilosc elem: " << numberOfElements[i] << " - Gestosc: " << density[j] << " - Reprezentacja: " << representationType[k] << endl;

				fstream file(path, fstream::out);

				file.setf(ios::fixed);

				sumOfResults = 0;

				if (!file.is_open()) {
					cerr << "Wyniki sie nie zapisza!!!" << endl;
				}

				for (int l = 0; l < numberOfTests; l++) {
					generate(numberOfElements[i], density[j], range);

					cout << "Test: " << l << " - ";

					if (representationType[k] == 'M') {
						try {
							counter.startCounter();
							primsAlgorithmOnMatrix(false);
							result = counter.getCounter();
						} catch (const char* e) {
							l--;
							result = 0;
						}
					} else {
						try {
							counter.startCounter();
							primsAlgorithmOnList(false);
							result = counter.getCounter();
						} catch (const char* e) {
							l--;
							result = 0;
						}
					}

					cout << "Czas: " << result << endl;
					file << result << endl;

					sumOfResults += result;
				}

				sumOfResults /= numberOfTests;

				cout << "Srednia: " << sumOfResults << endl;
				file << "Srednia" << endl << sumOfResults << endl;

				file.close();
			}
		}
	}
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

std::string UndirectedGraph::primsAlgorithmOnMatrix(bool print) {
	// prepare vector for output
	vector<vector<int>> minimumSpanningTree;

	if (incidenceMatrix.size() == 0)
		throw "Graf pusty!";

	int numberOfVertices = incidenceMatrix[0].size();
	vector<int> foundVertices;
	priority_queue<MinHeapElement, vector<MinHeapElement>, MinHeapElementComparator> queue;

	// take first vertex
	int vertexID = 0;
	int edgeEnd;
	int edgeValue;
	int i;
	int j = 0;

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
			if (queue.empty()) // jesli kolejka pusta, wywal sie
				throw "Graf niespojny!";
			MinHeapElement element = queue.top();
			vertexID = element.getEdgeBeginning();
			edgeEnd = element.getEdgeEnd();
			edgeValue = element.getEdgeValue();
			queue.pop();
		} while (find(foundVertices.begin(), foundVertices.end(), edgeEnd) != foundVertices.end());

		foundVertices.push_back(edgeEnd);

		minimumSpanningTree.emplace_back();
		minimumSpanningTree[j].resize(numberOfVertices);

		minimumSpanningTree[j][vertexID] = edgeValue;
		minimumSpanningTree[j][edgeEnd] = edgeValue;

		vertexID = edgeEnd;
		j++;

	} while (foundVertices.size() < numberOfVertices);

	if (print) {
		string output = "Minimalne drzewo rozpinajace\n";

		output += printMatrix(minimumSpanningTree);

		return output;
	}

	return "";
}

std::string UndirectedGraph::primsAlgorithmOnList(bool print) {
	// prepare vector for output
	std::vector<std::forward_list<EdgeListElement>> minimumSpanningTree;

	if (adjacencyList.size() == 0)
		throw "Graf pusty!";

	int numberOfVertices = adjacencyList.size();
	minimumSpanningTree.resize(numberOfVertices);
	vector<int> foundVertices;
	priority_queue<MinHeapElement, vector<MinHeapElement>, MinHeapElementComparator> queue;

	// take first vertex
	int vertexID = 0;
	int edgeEnd;
	int edgeValue;
	int i;
	int j = 0;

	foundVertices.push_back(vertexID);

	do {
		// look for edges from first vertices
		for (auto& element : adjacencyList[vertexID]) {
			queue.push(MinHeapElement(vertexID, element.edgeEnd, element.value));
		}

		do {
			if (queue.empty()) // jesli kolejka pusta, wywal sie
				throw "Graf niespojny!";
			MinHeapElement element = queue.top();
			vertexID = element.getEdgeBeginning();
			edgeEnd = element.getEdgeEnd();
			edgeValue = element.getEdgeValue();
			queue.pop();
		} while (find(foundVertices.begin(), foundVertices.end(), edgeEnd) != foundVertices.end());

		foundVertices.push_back(edgeEnd);

		minimumSpanningTree[vertexID].push_front({edgeEnd, edgeValue});
		minimumSpanningTree[edgeEnd].push_front({vertexID, edgeValue});

		vertexID = edgeEnd;
		j++;

	} while (foundVertices.size() < numberOfVertices);

	if (print) {
		string output = "Minimalne drzewo rozpinajace\n";

		output += printList(minimumSpanningTree);

		return output;
	}

	return "";
}
