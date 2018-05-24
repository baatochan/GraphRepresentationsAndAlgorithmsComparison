//
// Created by barto on 19.05.18.
//

#include <cmath>
#include <random>
#include <climits>
#include <iostream>
#include <fstream>
#include <ctime>
#include "DirectedGraph.h"
#include "Counter.h"

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
	int numberOfElements[5] = {50, 100, 150, 200, 250};
	int density[4] = {25, 50, 75, 99};
	char representationType[2] = {'M', 'L'};
	int range = 1000;
	int numberOfTests = 100;
	string path;
	double sumOfResults;
	Counter counter;
	double result = 0;
	int beginVertex;
	int endVertex;
	
	cout.setf(ios::fixed);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 2; k++) {
				path = "..\\wyniki\\";
				path += to_string(time(0));
				path += "-gSkierowany-algorytmDijkstry-n" + to_string(numberOfElements[i]) + "-g" +
				        to_string(density[j]) + "-r" + representationType[k] + ".txt";

				cout << "Test - Graf: Skierowany - Algorytm: Dijkstry - Ilosc elem: " << numberOfElements[i] << " - Gestosc: " << density[j] << " - Reprezentacja: " << representationType[k] << endl;

				fstream file(path, fstream::out);

				file.setf(ios::fixed);

				sumOfResults = 0;

				if (!file.is_open()) {
					cerr << "Wyniki sie nie zapisza!!!" << endl;
				}

				for (int l = 0; l < numberOfTests; l++) {
					generate(numberOfElements[i], density[j], range);

					cout << "Test: " << l << " - ";

					std::random_device rd;
					std::mt19937 mt(rd());
					std::uniform_int_distribution<int> randomVertex(0, numberOfElements[i] - 1);
					beginVertex = randomVertex(mt);
					endVertex = randomVertex(mt);

					cout << "PW: " << beginVertex << ", KW: " << endVertex << " - ";

					if (representationType[k] == 'M') {
						try {
							counter.startCounter();
							dijkstrasAlgorithmOnMatrix(beginVertex, endVertex, false);
							result = counter.getCounter();
						} catch (const char* e) {
							l--;
							result = 0;
						}
					} else {
						try {
							counter.startCounter();
							dijkstrasAlgorithmOnList(beginVertex, endVertex, false);
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
			break;

		currentVertex = shortestPathVertex;

	}

	if (print) {
		string output;
		shortestPath = pathLength[endVertex];

		if (shortestPath == ULONG_MAX) {
			output += "Droga pomiedzy wybranymi wierzcholkami nie istnieje!\n\n"
		} else {
			output =
					"Najkrotsza droga z wierzch.: " + to_string(beginVertex) + " do wierzch.: " + to_string(endVertex) +
					" wynosi: " + to_string(shortestPath) + ".\n";
			output += "Prowadzi nastepujaca droga: ";

			currentVertex = endVertex;

			output += to_string(currentVertex);

			while (currentVertex != beginVertex) {
				currentVertex = previousVertex[currentVertex];
				output += " <- " + to_string(currentVertex);
			}

			output += "\n\n";
		}

		output += "Najkrotsza droga do innych wierzcholkow: \n";
		output += "W | Dlugosc\n";
		output += "------------------";
		for (int i = 0; i < numberOfVertices; i++) {
			shortestPath = pathLength[i];

			output += to_string(i) + " | ";

			if (shortestPath == ULONG_MAX) {
				output += "BRAK";
			} else {
				output += to_string(shortestPath);
			}

			output += "\n";
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
