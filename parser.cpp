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

	// Extract tokens
	std::vector<std::string> tokens = string_to_tokens(buffer.str());
	/*for(auto s : tokens){
		std::cout << s;
	}*/

	Block mission("Mission");
	parse_tokens(mission, tokens);

	return mission;
}

int Parser::parse_tokens(Block& block, std::vector<std::string> tokens, int begin)
{

	// Parse the rest fuck
	std::string temp = "";
	std::vector<std::string> keys_values;

	for(unsigned int i = begin; i<tokens.size(); i++){
		std::string token = tokens.at(i);

		// Dismiss comments for now
		if(token.find("//") == 0){
			continue;
		}
		if(token == "}"){
			while(keys_values.size() != 0){
				try {
					KeyValuePair kv = {generate_id(), keys_values.at(0), keys_values.at(1)};
					block.add_keyvalue(kv);
					keys_values.erase(keys_values.begin(), keys_values.begin()+2);
				} catch (...) {
					std::cout << "Error" << std::endl;
				}
			}
			return i;
		}

		if(token == "{"){
			keys_values.pop_back();
			Block children(temp);

			// Recurse and jump to after the children
			i = parse_tokens(children, tokens, i+1);

			block.add_children(children);
		}else {
			keys_values.push_back(token);
			temp = token;
		}
	}

	return tokens.size();
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
		// TODO: Simpify later
		if(*iter == '\n' || *iter == '\"'
				|| *iter == '{' || *iter == '}'){
			if(temp != ""){
				tokens.push_back(temp);
			}
			temp.clear();
			std::string s(1, *iter);
			tokens.push_back(s);
			continue;
		}

		if(*iter != ' ' && *iter != '\t'){
			temp += *iter;

			if(temp == "//"){
				tokens.push_back(temp);
				temp.clear();
			}
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
			if(!in_quotes && !in_comment){
				tokens_merged.push_back(token);
			} else{
				tokens_merged.back() += token;
			}
			in_quotes = !in_quotes;
			continue;
		}

		if(!in_quotes){
			if(token == "//"){
				tokens_merged.push_back(token);
				in_comment = true;
				continue;
			}
			if(token == "\n"){
				in_comment = false;
				continue;
			}
		}

		if(in_quotes || in_comment){
			if(tokens_merged.back() == "\""){
				tokens_merged.back() += token;
			} else{
				tokens_merged.back() += " " + token;
			}
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
