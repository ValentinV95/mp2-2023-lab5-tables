#include "error.h"

void throw_error(const std::string& s, const std::string& err_s, const size_t pos)
{
	std::stringstream ss;
	ss << err_s
		<< ", position "
		<< pos + 1 << ": "
		<< s.substr(0, pos)
		<< "["
		<< s[pos]
		<< "]"
		<< s.substr(pos + 1, s.size());
	throw std::runtime_error(ss.str());
}

void throw_error(const std::string& s, const std::string& err_s, const std::string& t, const size_t pos)
{
	std::stringstream ss;
	ss << err_s
		<< ", position "
		<< pos + 1 << "-" << pos + t.size() << ": "
		<< s.substr(0, pos)
		<< "["
		<< t
		<< "]"
		<< s.substr(pos + t.size(), s.size());
	throw std::runtime_error(ss.str());
}

bool isWhitespace(const char c) noexcept { return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f'); }

bool isInvalidVariableName(const std::string& s) noexcept
{
	if (isWhitespace(s[0]) || s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "(" || s == ")" || s == "=" || s == "help" || s == "quit"
		|| (s[0] >= '0' && s[0] <= '9'))
		return true;

	size_t count = 0;

	for (size_t i = 0; i < s.size(); i++)
	{
		if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9'))) return true;
		else if (s[i] != 'x' && s[i] != 'y' && s[i] != 'z')
			count++;
	}

	return count == 0;
}