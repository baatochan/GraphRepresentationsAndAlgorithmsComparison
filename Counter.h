//
// Created by barto on 18.04.17.
//
// Code written by Ramonster.
// It was said in task description that we can use code from that link.
//

#ifndef DATASTRUCTURESSDIZO_COUNTER_H
#define DATASTRUCTURESSDIZO_COUNTER_H


#include <windows.h>
#include <iostream>

class Counter {
private:

	double PCFreq = 0.0;

	__int64 CounterStart = 0;

public:

	void startCounter();

	double getCounter();

};


#endif //DATASTRUCTURESSDIZO_COUNTER_H
