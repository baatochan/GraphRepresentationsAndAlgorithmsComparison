//
// Created by barto on 19.05.18.
//

#include "Graph.h"

Graph::Graph(const std::string name, int numberOfAvailableAlgorithms) : name(name), numberOfAvailableAlgorithms(numberOfAvailableAlgorithms) {}

std::string Graph::getName() {
	return name;
}

int Graph::getNumberOfAvailableAlgorithms() {
	return numberOfAvailableAlgorithms;
}
