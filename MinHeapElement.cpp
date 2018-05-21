//
// Created by barto on 20.05.18.
//

#include "MinHeapElement.h"

// MinHeapElement
// public

MinHeapElement::MinHeapElement(int edgeBeginning, int edgeEnd, int edgeValue) {
	this->edgeBeginning = edgeBeginning;
	this->edgeEnd = edgeEnd;
	this->edgeValue = edgeValue;
}

int MinHeapElement::getEdgeBeginning() const {
	return edgeBeginning;
}

int MinHeapElement::getEdgeEnd() const {
	return edgeEnd;
}

int MinHeapElement::getEdgeValue() const {
	return edgeValue;
}

// MinHeapElementComparator
// public

int MinHeapElementComparator::operator()(const MinHeapElement &element1, const MinHeapElement &element2) {
	return element1.getEdgeValue() > element2.getEdgeValue();
}
