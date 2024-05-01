// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once
#include "Polynom.h"
#include "UnorderedTable.h"
#include "OrderedTable.h"
#include "HashTable.h"
#include <vector>
#include <string>

class TPostfix {
	std::vector<std::string> RPN;
	
	std::string Error_string(const std::string& s, int i); //Method that selects element number "i" in a string. Uses only for selecting incorrect element when throws. 

	int get_prior(const std::string& s) noexcept; //Method that return the priority of an operation. If it is not an operation returns 0
	
	int get_prior(char c) noexcept; //similar method for characters

	double valid(const std::string& s); //Method that turns correct string into a number
	
	std::string number_check(const std::string& s, int& i); //Method takes the string being processed and the index from which the expected number begins and checks it for correctness
public:
	TPostfix(const std::string& s); //Turns string into a Reverse Polish Notation, if it possible.

	Polynom count(UnorderedTable<std::string, Polynom>& T1, 
				 OrderedTable<std::string, Polynom>& T2,
				 HashTable& T3); //Count a string stored in a class element. Variables is entered by programm.
};