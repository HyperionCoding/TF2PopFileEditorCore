#include <iostream>
#include <parser.h>

using namespace std;

int main()
{
	Parser& parser = Parser::getInstance();

	parser.parse_file("example.pop");
	return 0;
}
