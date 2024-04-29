#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <stdexcept>
#include <sstream>

void throw_error(const std::string& s, const std::string& err_s, const size_t pos);
void throw_error(const std::string& s, const std::string& err_s, const std::string& t, const size_t pos);
bool isInvalidVariableName(const std::string& s) noexcept;
bool isWhitespace(const char c) noexcept;

#endif