#ifndef POSTFIX_H
#define POSTFIX_H

#include <string>
#include <stack>
#include "table.h"
#include "polynoms.h"
#include "unordered_table.h"
#include "ordered_table.h"
#include "hash_table.h"
#include "rbt.h"

class Postfix
{
public:
	Postfix() noexcept : p(this), t(this) {}

	Polynom evaluate(const std::string& s);
	void insert(const std::string& s, const Polynom& p, size_t idx);
	void remove(const std::string& s, size_t idx);

private:
	// ���� �������
	enum TokenType
	{
		UN_OP, // ������� ��������
		BIN_OP, // �������� ��������
		POL, // �������
		VAR, // ����������
		LEFT_PARS, // ����� ������� ������
		RIGHT_PARS, // ������ ������� ������
		UNRECG, // �������������� ��������� ��������
	};

	struct Token
	{
		std::string s;
		TokenType type;
		Polynom val;
	};

	class Parser
	{
	public:
		Parser(Postfix* _p) noexcept : p(_p) { }
		Token* convertToPostfix(Token* tokens, size_t& sz);

	private:
		inline int operatorPriority(const Token& t) noexcept;
		inline bool isLeftAssoc(const Token& t) noexcept;

		Postfix* p;
	};

	// ����� Tokenizer ������������ ��������� ��������� ��������� �� ������
	class Tokenizer
	{
	public:
		Tokenizer(Postfix* _p) noexcept : p(_p) { }
		Token* tokenize(const std::string& expr, size_t& sz);
		Token tokenizeOperation(const std::string& s, size_t& cur_pos, bool unary);
		Token tokenizeWord(const std::string& s, size_t& cur_pos);

	private:
		enum TokenizerState
		{
			TS_INIT,
			TS_WORD,
			TS_OP,
			TS_LEFT_PAR,
			TS_RIGHT_PAR
		};

		Postfix* p;
	};

	Table<Polynom, unordered_table> ut;
	Table<Polynom, ordered_table>	ot;
	Table<Polynom, rbtree>			rbt;
	Table<Polynom, hash_table>		ht;

	Polynom* findInTables(const std::string& key);

	Parser p;
	Tokenizer t;
};

#endif