//
// Created by barto on 19.05.18.
//

#include <fstream>
#include "Graph.h"

using namespace std;

// protected

Graph::Graph(const string name, int numberOfAvailableAlgorithms)
		: name(name), numberOfAvailableAlgorithms(numberOfAvailableAlgorithms) {}

// public

string Graph::getName() {
	return name;
}

int Graph::getNumberOfAvailableAlgorithms() {
	return numberOfAvailableAlgorithms;
}

string Graph::printIncidenceMatrix() {
	string output = getName();
	string temp = "";

	if (incidenceMatrix.size() == 0) {
		output = "Graf pusty!";
		return output;
	}

	output += "\n  K\\W  ||"; //lewy gorny rog ma ' K\W  ||', podwojny | dla wyroznienia komorki

	// wypisz pierwsza linijke
	for (int i = 0; i < incidenceMatrix[0].size(); i++) {
		temp = to_string(i);

		output += " ";
		for (int j = 0; j < 5 - temp.size(); j++) { //miejsce na 6 znakow dla kazdej komorki
			if (temp.size() > 5) break;
			output += " ";
		}
		output += temp + " |";
	}
	output += "\n";

	// pozioma linia dla odzielenia wierszy
	int firstLineSize = output.size() - getName().size() - 2; //-2 bo dwa razy \n
	for (int i = 0; i < firstLineSize; i++) {
		output += "-";
	}
	output += "\n";

	//wypisz kolejne linijki
	for (int i = 0; i < incidenceMatrix.size(); i++) {
		// pierwsza pozycja kolejnej linijki
		temp = to_string(i);

		output += " ";
		for (int j = 0; j < 5 - temp.size(); j++) {
			if (temp.size() > 5) break;
			output += " ";
		}
		output += temp + " ||";

		// kolejne pozycje kolejnych linijek
		for (int j = 0; j < incidenceMatrix[0].size(); j++) {
			temp = to_string(incidenceMatrix[i][j]);

			output += " ";
			for (int k = 0; k < 5 - temp.size(); k++) {
				if (temp.size() > 5) break;
				output += " ";
			}
			output += temp + " |";
		}

		output += "\n";
	}

	return output;
}

string Graph::printAdjacencyList() {
	string output = getName();
	string temp = "";

	if (adjacencyList.size() == 0) {
		output = "Graf pusty!";
		return output;
	}

	output += "\n   W   || wierzcholek konca krawedzi, waga | kolejna... | ...\n"; // pierwsza linijka

	// druga linijka rozdzielajaca
	for (int i = 0; i < 80; i++) {
		output += "-";
	}
	output += "\n";

	for (int i = 0; i < adjacencyList.size(); i++) {
		// pierwsza pozycja kolejnej linijki
		temp = to_string(i);

		output += " ";
		for (int j = 0; j < 5 - temp.size(); j++) {
			if (temp.size() > 5) break;
			output += " ";
		}
		output += temp + " ||";

		// kolejne pozycje
		for (auto& element : adjacencyList[i]) {
			output += " " + to_string(element.edgeEnd) + ", " + to_string(element.value) + " |";
		}

		output += "\n";
	}

	return output;
}

void Graph::loadDataFrom(std::string fileName) {
	vector<int> rawData = loadRawDataFrom(fileName);
	loadRawDataToMatrix(rawData);
	loadRawDataToList(rawData);
}

// protected

vector<int> Graph::loadRawDataFrom(string path) {
	vector<int> returnIntVector = vector<int>();
	vector<string> values = vector<string>();

	fstream file(path, ios::in);

	if (!file.is_open())
		return returnIntVector; // should throw an error

	string temp = "";
	while (file >> temp) {
		try {
			returnIntVector.push_back(stoi(temp));
		} catch (const exception& e) {
			returnIntVector.clear();
			throw "Bledna zawartosc pliku! Upewnij sie ze podales odpowiedni format!";
		}
	}

	return returnIntVector;
}
