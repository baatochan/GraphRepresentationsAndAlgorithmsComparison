//
// Created by barto on 19.05.18.
//

#include "Graph.h"

// protected

Graph::Graph(const std::string name, int numberOfAvailableAlgorithms)
		: name(name), numberOfAvailableAlgorithms(numberOfAvailableAlgorithms) {}

// public

std::string Graph::getName() {
	return name;
}

int Graph::getNumberOfAvailableAlgorithms() {
	return numberOfAvailableAlgorithms;
}

std::string Graph::printIncidenceMatrix() {
	std::string output = getName();
	std::string temp = "";

	output += "\n  K\\W  ||"; //lewy gorny rog ma ' K\W  ||', podwojny | dla wyroznienia komorki

	// wypisz pierwsza linijke
	for (int i = 0; i < incidenceMatrix[0].size(); i++) {
		temp = std::to_string(i);

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
		temp = std::to_string(i);

		output += " ";
		for (int j = 0; j < 5 - temp.size(); j++) {
			if (temp.size() > 5) break;
			output += " ";
		}
		output += temp + " ||";

		// kolejne pozycje kolejnych linijek
		for (int j = 0; j < incidenceMatrix[0].size(); j++) {
			temp = std::to_string(incidenceMatrix[i][j]);

			output += " ";
			for (int j = 0; j < 5 - temp.size(); j++) {
				if (temp.size() > 5) break;
				output += " ";
			}
			output += temp + " |";
		}

		output += "\n";
	}

	return output;
}

std::string Graph::printAdjacencyList() {

}
