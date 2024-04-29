#include "postfix.h"
#include "error.h"

Polynom Postfix::evaluate(const std::string& s)
{
	try
	{
		size_t sz = 0;
		std::stack<Token> st;
		Token* tokens = t.tokenize(s, sz);
		Token* postfix = p.convertToPostfix(tokens, sz);

		for (size_t i = 0; i < sz; ++i)
		{
			switch (postfix[i].type)
			{
			case POL:
			{
				st.push(postfix[i]);
				break;
			}

			case VAR:
			{
				Polynom* p1 = ut.find(postfix[i].s);
				Polynom* p2 = ot.find(postfix[i].s);
				Polynom* p3 = rbt.find(postfix[i].s);
				Polynom* p4 = ht.find(postfix[i].s);

				if (p1 != nullptr)
					st.push({"", POL, *p1});
				else if (p2 != nullptr)
					st.push({ "", POL, *p2 });
				else if (p3 != nullptr)
					st.push({ "", POL, *p3 });
				else if (p4 != nullptr)
					st.push({ "", POL, *p4 });
				break;
			}

			case UN_OP:
			{
				if (postfix[i].s == "-")
					st.top().val = st.top().val * (- 1.0);
				break;
			}

			case BIN_OP:
			{
				Token lhs = st.top(); st.pop();
				Token rhs = st.top(); st.pop();
				switch (postfix[i].s[0])
				{
				case '+':
					st.push(Token{ "", POL, rhs.val + lhs.val });
					break;

				case '-':
					st.push(Token{ "", POL, rhs.val - lhs.val });
					break;

				case '*':
					st.push(Token{ "", POL, rhs.val * lhs.val });
					break;
				}

				break;
			}
			}
		}

		delete[] tokens;
		delete[] postfix;
		return st.top().val;
	}

	catch (const std::exception& e)
	{
		throw e;
	}

	return Polynom();
}

void Postfix::insert(const std::string& s, const Polynom& p, size_t idx)
{
	if (isInvalidVariableName(s))
		throw std::invalid_argument("Invalid variable name");

	switch (idx)
	{
	case 0:
		ut.insert({ s, p });
		break;
	case 1:
		ot.insert({ s, p });
		break;
	case 2:
		rbt.insert({ s, p });
		break;
	case 3:
		ht.insert({ s, p });
		break;
	default:
		throw std::invalid_argument("Invalid table index");
	}
}

void Postfix::remove(const std::string& s, size_t idx)
{
	if (isInvalidVariableName(s))
		throw std::invalid_argument("Invalid variable name");

	switch (idx)
	{
	case 0:
		ut.remove(s);
		break;
	case 1:
		ot.remove(s);
		break;
	case 2:
		rbt.remove(s);
		break;
	case 3:
		ht.remove(s);
		break;
	default:
		throw std::invalid_argument("Invalid table index");
	}
}

Postfix::Token* Postfix::Tokenizer::tokenize(const std::string& expr, size_t& sz)
{
	std::stack<Token> tmp;
	std::stack<size_t> parenthesis;
	TokenizerState ts = TS_INIT;
	bool unary = true;
	size_t tokens_count = 0;

	if (expr.size() == 0) throw std::runtime_error("An empty string was given");

	std::string tmp_string;

	for (size_t i = 0; i < expr.size();)
	{
		Token t;
		std::string token_string;

		switch (ts)
		{
		case TS_INIT:
			if (isWhitespace(expr[i])) i++;
			else if (expr[i] == '.' || (expr[i] >= '0' && expr[i] <= '9')) ts = TS_WORD;
			else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^') ts = TS_OP;
			else if (expr[i] == '(') ts = TS_LEFT_PAR;
			else if (expr[i] == ')') ts = TS_RIGHT_PAR;
			else if ((expr[i] >= 'a' && expr[i] <= 'z') || (expr[i] >= 'A' && expr[i] <= 'Z')) ts = TS_WORD;
			else throw_error(expr, "Unexpected character", i);
			continue;

		case TS_OP:
		{
			t = tokenizeOperation(expr, i, unary);

			if (!tmp.empty())
			{
				if (t.type == UN_OP)
					if (tmp.top().type != UN_OP && tmp.top().type != BIN_OP && tmp.top().type != LEFT_PARS)
						throw_error(expr, "Unexpected token", i - 1);

				else
					if (tmp.top().type != POL && tmp.top().type != VAR && tmp.top().type != RIGHT_PARS)
						throw_error(expr, "Unexpected token", i - 1);
			}

			tmp.push(t);
			ts = TS_INIT;
			tokens_count++;
			unary = true;
			continue;
		}

		case TS_WORD:
		{
			t = tokenizeWord(expr, i);
			auto ptr = p->findInTables(t.s);

			if (ptr != nullptr)
			{
				t.val = *ptr;
				t.type = VAR;
			}

			else
			{
				t.val.fill(t.s);
				t.type = POL;
			}

			if (!tmp.empty())
				if (tmp.top().type != UN_OP && tmp.top().type != BIN_OP && tmp.top().type != LEFT_PARS)
					throw_error(expr, "Unexpected token", t.s, i - t.s.size());

			tmp.push(t);
			ts = TS_INIT;
			tokens_count++;
			unary = false;
			continue;
		}

		case TS_LEFT_PAR:
		{
			if (!tmp.empty())
				if (tmp.top().type != LEFT_PARS && tmp.top().type != UN_OP && tmp.top().type != BIN_OP)
					throw_error(expr, "Unexpected token", i);

			parenthesis.push(i);
			t.s = expr[i++];
			t.type = LEFT_PARS;

			tmp.push(t);
			ts = TS_INIT;
			tokens_count++;
			unary = true;
			continue;
		}

		case TS_RIGHT_PAR:
		{
			if (parenthesis.empty()) throw_error(expr, "Misplaced parenthesis", i);
			parenthesis.pop();

			if (!tmp.empty())
				if (tmp.top().type != RIGHT_PARS && tmp.top().type != POL && tmp.top().type != VAR)
					throw_error(expr, "Unexpected token", i);

			t.s = expr[i++];
			t.type = RIGHT_PARS;

			tmp.push(t);
			ts = TS_INIT;
			tokens_count++;
			unary = false;
			continue;
		}
		}
	}

	if (tokens_count == 0) throw std::runtime_error("An empty string was given");
	if (tmp.top().type == UN_OP || tmp.top().type == BIN_OP) throw_error(expr, "Missing operand", tmp.top().s, tmp.size() - 1);
	if (!parenthesis.empty()) throw_error(expr, "Unclosed parenthesis", parenthesis.top());

	sz = tokens_count;
	size_t i = tokens_count - 1;
	size_t pos = expr.size() - 1;
	Token* tokens = new Token[tokens_count];

	while (!tmp.empty())
	{
		while (isWhitespace(expr[pos])) pos--;
		pos -= tmp.top().s.size();
		tokens[i--] = tmp.top();
		tmp.pop();
	}

	return tokens;
}

Polynom* Postfix::findInTables(const std::string& key)
{
	auto ptr1 = ut.find(key);
	auto ptr2 = ot.find(key);
	auto ptr3 = rbt.find(key);
	auto ptr4 = ht.find(key);

	if (ptr1 != nullptr)
		return ptr1;
	else if (ptr2 != nullptr)
		return ptr2;
	else if (ptr3 != nullptr)
		return ptr3;
	else if (ptr4 != nullptr)
		return ptr4;
	return nullptr;
}

Postfix::Token Postfix::Tokenizer::tokenizeOperation(const std::string& s, size_t& cur_pos, bool unary)
{
	Token op;
	op.val = Polynom();

	if (unary && s[cur_pos] == '-') op.type = UN_OP;
	else if (unary && s[cur_pos] != '-') throw_error(s, "Missing operand.", cur_pos);
	else op.type = BIN_OP;

	op.s = s[cur_pos++];
	return op;
}

Postfix::Token Postfix::Tokenizer::tokenizeWord(const std::string& s, size_t& cur_pos)
{
	Token word;
	word.val = Polynom();
	std::string t = "";
	size_t first_char = cur_pos;

	for (; cur_pos < s.size();)
	{
		if (isWhitespace(s[cur_pos])) break;
		else if (s[cur_pos] == '+' || s[cur_pos] == '-' || s[cur_pos] == '*')
		{
			if (cur_pos > 0 && s[cur_pos - 1] == 'e')
			{
				t += s[cur_pos++];
				continue;
			}

			else
				break;
		}
		else if (s[cur_pos] == '(' || s[cur_pos] == ')') break;
		t += s[cur_pos++];
	}

	word.s = t;
	return word;
}

Postfix::Token* Postfix::Parser::convertToPostfix(Token* tokens, size_t& sz)
{
	std::stack<Token> postfix;
	std::stack<Token> tmp;
	size_t inp_sz = sz;

	for (size_t i = 0; i < inp_sz; i++)
	{
		switch (tokens[i].type)
		{
		case POL: {}
		case VAR:
		{
			postfix.push(tokens[i]);
			break;
		}

		case LEFT_PARS:
		{
			tmp.push(tokens[i]);
			sz--;
			break;
		}

		case RIGHT_PARS:
		{
			while (tmp.top().type != LEFT_PARS)
			{
				postfix.push(tmp.top());
				tmp.pop();
			}

			tmp.pop();
			sz--;
			break;
		}

		case UN_OP: {}
		case BIN_OP:
		{
			while ((!tmp.empty()) && (operatorPriority(tmp.top()) > operatorPriority(tokens[i])
				|| (operatorPriority(tmp.top()) == operatorPriority(tokens[i]) && isLeftAssoc(tokens[i]))))
			{
				postfix.push(tmp.top());
				tmp.pop();
			}

			tmp.push(tokens[i]);
			break;
		}

		default:
			throw std::runtime_error("Unknown error");
			break;
		}
	}

	while (!tmp.empty())
	{
		postfix.push(tmp.top());
		tmp.pop();
	}

	Token* res = new Token[sz];
	size_t j = sz - 1;
	while (!postfix.empty())
	{
		res[j--] = postfix.top();
		postfix.pop();
	}

	return res;
}

inline int Postfix::Parser::operatorPriority(const Token& t) noexcept
{
	if (t.type == BIN_OP)
	{
		if (t.s == "+" || t.s == "-") return 2;
		else if (t.s == "*" || t.s == "/") return 3;
		else if (t.s == "^") return 4;
	}

	else if (t.type == UN_OP) return 4;
	return -1;
}

inline bool Postfix::Parser::isLeftAssoc(const Token& t) noexcept
{
	if (t.type == UN_OP) return false;
	return true;
}
