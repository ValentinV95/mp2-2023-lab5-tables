// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once
#include <vector>
#include <map>
#include "poly.h"

//using namespace std;

class ArithmeticExpr {
	std::string infix;
	std::string pubpostfix;
	std::vector<std::string> postfix;
	std::vector<std::string> lexems;
	std::map<std::string,polynoms> operands;
	std::string priorStr[12] = {"(","+","-","*","/","~","sin","cos","tg","ctg","ln","exp"}; 
	int priorVal[12]= { 0,1,1,2,2,3,4,4,4,4,4,4 };
public:
	ArithmeticExpr(std::string infx);
	void Parse();
	void ToPostfix();
	std::string GetInfix()const;
	std::string GetPostfix() const;
	std::vector <std::string> GetLexems() const;
	std::vector<std::string> GetOperands() const;
	polynoms Calculate(const std::map<std::string, polynoms>& value);
	std::string strNumberOrVar(std::string infx); // selects a substring from the zero character from the string, if it is a number or a variable
	double Translate(std::string snum);
	std::string strFunc(std::string infx); //selects a substring from a string with a null character if it is a function
	int Priority(std::string item);
	//std::map<std::string, double> Get_operands();
};
int StringIsAlmostCorrect(std::string s);  //eliminates most of the errors from the user needed to simplify the subsequent code


// реализаци€ функций и классов дл€ вычислени€ арифметических выражений




