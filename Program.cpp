//
// Created by barto on 19.05.18.
//

#include <iostream>
#include <limits>
#include "Program.h"

using namespace std;

// public

void Program::start() {
	char option;
	char option2;
	bool breakMainMenu;

	string file;
	int numberOfVerticles;
	int density;
	string matrix;
	string list;
	char index;

	do {
		printGraphTypeSelect();
		cin >> option;
		cout << endl;

		breakMainMenu = false;

		switch (option) {
			case '1':
				graph = new UndirectedGraph();
				break;

			case '2':
				graph = new DirectedGraph();
				break;

			case '0':
				breakMainMenu = true;
				break;

			default:
				cout << "Nie ma takiej opcji, wybierz jeszcze raz." << endl;
				breakMainMenu = true;
				break;
		}

		if (breakMainMenu)
			continue;

		do {
			printGraphMenu();
			cin >> option2;
			cout << endl;

			switch (option2) {
				case '1': // wczytaj z pliku
					cout << "Podaj nazwe pliku: ";
					cin >> file;

					graph->loadDataFrom(file);
					break;

				case '2': // generuj losowo
					cout << "Podaj ilosc wierzcholkow: ";
					while (!(cin >> numberOfVerticles)) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Bledna wartosc! Podaj ilosc wierzcholkow: ";
					}
					cout << "Podaj gestosc grafu: ";
					while (!(cin >> density)) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Bledna wartosc! Podaj gestosc grafu: ";
					}

					graph->generate(numberOfVerticles, density);
					break;

				case '3': // wyswietl macierz
					matrix = graph->printIncidenceMatrix();

					cout << endl;
					cout << matrix;
					cout << endl;
					break;

				case '4': // wyswietl liste
					list = graph->printAdjacencyList();

					cout << endl;
					cout << list;
					cout << endl;
					break;

				case '5':
					graph->test();
					break;

				case '6':
				case '7':
				case '8':
				case '9':
					index = option2 - 53;
					runAlgorithm(index);

				case '0':
					break;

				default:
					cout << "Nie ma takiej opcji, wybierz jeszcze raz." << endl;
					break;
			}


		} while (option2 != '0');

	} while (option != '0');
}

// private

void Program::printGraphTypeSelect() {
	cout << endl;
	cout << "==== MENU GLOWNE ===" << endl;
	cout << "1. Graf nieskierowany" << endl;
	cout << "2. Graf skierowany" << endl;
	cout << "0. Wyjscie" << endl;
	cout << "Podaj opcje:";
}

void Program::printGraphMenu() {
	cout << endl;

	string name = graph->getName();
	for (auto &c: name) c = toupper(c); //convert to uppercase

	cout << "==== " << name << " ===" << endl;
	cout << "1. Wczytaj z pliku" << endl;
	cout << "2. Generuj losowo" << endl;
	cout << "3. Wyswietl graf jako macierz" << endl;
	cout << "4. Wyswietl graf jako lista" << endl;
	cout << "5. Wykonaj testy" << endl;

	string availableAlgorithms = graph->getAvailableAlgorithms();
	cout << availableAlgorithms;

	cout << "0. Wyjscie" << endl;
	cout << "Podaj opcje:";
}

void Program::runAlgorithm(char index) {
	int arg1;
	int arg2;
	if (graph->getNumberOfAvailableAlgorithms() > index - 1) {
		cout<<"Podaj argument 1: ";
		while (!(cin >> arg1)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Bledna wartosc! Podaj argument 1: ";
		}
		cout<<"Podaj argument 2: ";
		while (!(cin >> arg2)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Bledna wartosc! Podaj argument 2: ";
		}
		graph->runAlgorithm(index, arg1, arg2);
	} else {
		cout << "Nie ma takiej opcji, wybierz jeszcze raz." << endl;
	}
}
