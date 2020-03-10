#ifndef PARSER2_H
#define PARSER2_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "block.h"

extern std::vector<char> whitespace;
extern std::vector<char> delimiters;

extern std::string popfile_text;

class Parser
{
public:
	static Parser& getInstance();

	Block parse_file(std::string filepath);
	int parse_tokens(Block& block, std::vector<std::string> tokens, int begin=0);

	bool is_whitespace(char c);
	bool is_delimiter(char c);

	std::vector<std::string> string_to_tokens(std::string str);
	void string_tolower(std::string& str);
};

#endif // PARSER2_H
