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
