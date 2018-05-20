//
// Created by barto on 20.05.18.
//

#ifndef GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_MINHEAPELEMENT_H
#define GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_MINHEAPELEMENT_H


class MinHeapElement {
public:
	MinHeapElement(int edgeBeginning, int edgeEnd, int edgeValue);

private:
	int edgeBeginning;
	int edgeEnd;
	int edgeValue;

public:
	int getEdgeBeginning() const;
	int getEdgeEnd() const;
	int getEdgeValue() const;

};

class MinHeapElementComparator {
public:
	int operator() (const MinHeapElement& element1, const MinHeapElement& element2);

};


#endif //GRAPHREPRESENTATIONSANDALGORITHMSCOMPARISON_MINHEAPELEMENT_H
