// îáúÿâëåíèå ôóíêöèé è êëàññîâ äëÿ âû÷èñëåíèÿ àðèôìåòè÷åñêèõ âûðàæåíèé

#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "stack.h"

using namespace std;

class TPostfix
{
private:
	class Lexeme
	{
	public:
		int type_of_lex; //1 - áèíàðíàÿ îïåðàöèÿ, 2 - '(', 3 - ')',
		//4 - ïåðåìåííàÿ, 5 - óíàðíûé ìèíóñ, 6 - ôóíêöèÿ: 6, 1 - sin,
		//6, 2 - cos; 6, 3 - tan; 6, 4 - exp; 6, 5 - ln; 7 - ÷èñëî
		void* lex;
		size_t pos=0; //èíäåêñ îïåðàíäà (ïî óìîë÷àíèþ = 0)
		Lexeme() noexcept {
			lex = nullptr;
			type_of_lex = 0;
			pos = 0;
		}

		Lexeme(const Lexeme&& rv) : type_of_lex(rv.type_of_lex), pos(rv.pos) {
			lex = rv.lex;
		}

		Lexeme(const Lexeme& rv) : type_of_lex(rv.type_of_lex), pos(rv.pos) {
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
		}

		template <typename T>
		Lexeme(int t_of_l, T op, size_t position=0) : type_of_lex(t_of_l), pos(position)
		{
			lex = new T(op);
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
			return *this;
		}
	};

	Lexeme* Rev_Pol_Notation;  //ÎÏÇ
	int* arr_num_variable; //ìàññèâ ñ íîìåðàìè ïåðåìåííûõ
	double* arr_value_variable;//ìàññèâ ñî çíà÷åíèÿìè ïåðåìåííûõ
	size_t i = 0, ind_RPN = 0, cap_RPN, ind_variable = 0, cap_variable;
	TStack <Lexeme> ops;	   //stack ëåêñåì

public:

	TPostfix(string& inp, bool need_to_check = true);	//Âûçâàòü, êîãäà õî÷åòñÿ ïðåîáðàçîâàòü èíôèêñíîå âûðàæåíèå â ïîñòôèêñíîå, íî íå çíàåøü, êàê
	void insert_result(const Lexeme& lex);				//Âûçâàòü, êîãäà õî÷åòñÿ âíåñòè î÷åðåäíóþ ëåêñåìó â ÎÏÇ, íî íå çíàåøü, êàê
	void insert_variable(int xi);						//Âûçâàòü, êîãäà õî÷åòñÿ âíåñòè î÷åðåäíóþ ïåðåìåííóþ â ìàññèâ îíûõ, íî íå çíàåøü, êàê
	void asker();										//Âûçâàòü, êîãäà õî÷åòñÿ óçíàòü çíà÷åíèÿ ïåðåìåííûõ, íî íå çíàåøü, êàê
	void input_variables(double* arr, size_t ind);		//Âûçâàòü, êîãäà õî÷åòñÿ â òåñòå âíåñòè ïåðåìåííûå èç ìàññèâà
	size_t Get_ind_variable();							//Âûçâàòü, êîãäà õî÷åòñÿ óçíàòü êîëè÷åñòâî ïåðåìåííûõ, íî íå çíàåøü, êàê
	double count();										//Âûçâàòü, êîãäà õî÷åòñÿ ïîäñ÷èòàòü ðåçóëüòàò, íî íå çíàåøü, êàê
};
