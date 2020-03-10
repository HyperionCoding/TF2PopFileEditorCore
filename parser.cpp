#include "parser.h"

std::vector<char> whitespace = {' ', '\t', '\n'};
std::vector<char> delimiters = {' ', '\t', '\n', '{', '}'};

std::string popfile_text;

Parser &Parser::getInstance()
{
	static Parser instance;
	return instance;
}

Block Parser::parse_file(std::string filepath)
{
	// Read file
	std::fstream readfile(filepath);
	std::stringstream buffer;
	buffer << readfile.rdbuf();

	Block mission;

	parse_text(&mission, buffer.str());

	return mission;
}

void Parser::parse_text(Block *block, std::string content)
{
	// Extract tokens
	std::vector<std::string> tokens = string_to_tokens(content);
	for(auto s : tokens){
		std::cout << "#" << s;
	}
}

bool Parser::is_whitespace(char c)
{
	if(std::find(whitespace.begin(), whitespace.end(), c) != whitespace.end()){
		return true;
	}
	return false;
}

bool Parser::is_delimiter(char c)
{
	if(std::find(delimiters.begin(), delimiters.end(), c) != delimiters.end()){
		return true;
	}
	return false;
}

std::vector<std::string> Parser::string_to_tokens(std::string str)
{
	// Collect tokens
	std::vector<std::string> tokens;
	std::string temp;

	for(std::string::iterator iter = str.begin(); iter != str.end(); iter++){
		if(*iter == '\n'){
			tokens.push_back(temp);
			temp.clear();
			tokens.push_back("\n");
			continue;
		}
		if(*iter != ' ' && *iter != '\t'){
			temp += *iter;
		}
		else{
			if(temp != ""){
				tokens.push_back(temp);
				temp.clear();
			}
		}
	}

	// Merge comments and quotes
	std::vector<std::string> tokens_merged;
	bool in_quotes = false; // ""
	bool in_comment = false; // //

	for(std::string token : tokens){
		// Comment detection
		if(token == "\'" || token == "\""){
			if(!in_quotes){
				tokens_merged.push_back(token);
			}
			in_quotes = !in_quotes;
		}

		if(!in_quotes){
			if(token == "//"){
				tokens_merged.push_back(token);
				in_comment = true;
			}
			if(token == "\n"){
				in_comment = false;
			}
		}

		if(in_quotes || in_comment){
			tokens_merged.back() += " " + token;
		} else {
			tokens_merged.push_back(token);
		}
	}

	return tokens_merged;
}

void Parser::string_tolower(std::string &str)
{
	std::transform(str.begin(), str.end(), str.begin(),
				   [](unsigned char c){ return std::tolower(c);});
}
