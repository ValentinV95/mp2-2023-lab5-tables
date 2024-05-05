// îáúÿâëåíèå ôóíêöèé è êëàññîâ äëÿ âû÷èñëåíèÿ àðèôìåòè÷åñêèõ âûðàæåíèé
#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <fstream>
#include <time.h>
#include "polynomials.h"
#include "Unordered_table.h"
#include "Hash_table.h"
#include "RBT.h"

using namespace std;


class TPostfix
{
private:
	class Lexeme
	{
	public:
		int type_of_lex; //1 - operation sign, 2 - '(', 3 - ')',
		//4 - polynomial name (index), 5 - unary minus, 7 - number, 8 - polynomial itself
		void* lex;
		size_t pos=0; //èíäåêñ îïåðàíäà (ïî óìîë÷àíèþ = 0)
		Lexeme() noexcept {
			lex = nullptr;
			type_of_lex = 0;
			pos = 0;
		}
		Lexeme(const Lexeme&& rv) noexcept : type_of_lex(rv.type_of_lex), pos(rv.pos) {
			lex = rv.lex;
		}

		Lexeme(const Lexeme& rv)  : type_of_lex(rv.type_of_lex), pos(rv.pos) {
			if (rv.type_of_lex == 1 || rv.type_of_lex == 2 || rv.type_of_lex == 3 || rv.type_of_lex == 5)
			{
				char* tmp = new char((*(char*)rv.lex));
				lex = tmp;
			}
			else if (rv.type_of_lex == 4)
			{
				size_t* tmp = new size_t((*(size_t*)rv.lex));
				lex = tmp;
			}
			else if (rv.type_of_lex == 6)
			{
				int* tmp = new int((*(int*)rv.lex));
				lex = tmp;
			}
			else if (rv.type_of_lex == 7)
			{
				double* tmp = new double((*(double*)rv.lex));
				lex = tmp;
			}
			else if (rv.type_of_lex == 8)
			{
				Polynomial* tmp = new Polynomial((*(Polynomial*)rv.lex));
				lex = tmp;
			}
		}

		template <typename T>
		Lexeme(int t_of_l, T op, size_t position=0) noexcept : type_of_lex(t_of_l), pos(position)
		{
			lex = new T(op);
		}

		Lexeme(int t_of_l, Polynomial& op, size_t position = 0) : type_of_lex(t_of_l), pos(position)
		{
			lex = new Polynomial(op);
		}

		Lexeme& operator=(const Lexeme & rv)
		{
			if (this == &rv)
				return *this;
			pos = rv.pos;
			type_of_lex = rv.type_of_lex;
			if (rv.type_of_lex == 1 || rv.type_of_lex == 2 || rv.type_of_lex == 3 || rv.type_of_lex == 5)
			{
				char* tmp = new char((*(char*)rv.lex));
				lex = tmp;
			}
			else if (rv.type_of_lex == 4)
			{
				size_t* tmp = new size_t((*(size_t*)rv.lex));
				lex = tmp;
			}
			else if (rv.type_of_lex == 6)
			{
				int* tmp = new int((*(int*)rv.lex));
				lex = tmp;
			}
			else if (rv.type_of_lex == 7)
			{
				double* tmp = new double((*(double*)rv.lex));
				lex = tmp;
			}
			else if (rv.type_of_lex == 8)
			{
				Polynomial* tmp = new Polynomial((*(Polynomial*)rv.lex));
				lex = tmp;
			}
			return *this;
		}
	};

	Lexeme* Rev_Pol_Notation;  //ÎÏÇ
	string* arr_name_variable; //ìàññèâ ñ íîìåðàìè ïåðåìåííûõ
	size_t i = 0, ind_RPN = 0, cap_RPN, ind_variable = 0, cap_variable, polynomials_inserted;
	TStack <Lexeme> ops;	   //stack ëåêñåì
	LR_UnordTable<string, Polynomial> UnordTable;
	Hash<string, Polynomial> Hsh_Table;
	UV_RBT<string, Polynomial> RBT_tree;

public:
	TPostfix(size_t variable = 3, size_t RPN = 10);
	void Polish_Notation(const string& inp, bool need_to_check = true);
	void insert_result(const Lexeme& lex);				
	void insert_variable(string&& name);				
	void asker();										
	void insert_polynomial(const string& name, const Polynomial& p, bool need_to_insert_name=false);
	bool avail(const string& name);							//Searches for a polynomial by name and returns true if there is
	Polynomial search(const string& name);						//Returns a polynomial by name
	Polynomial count();									
};
