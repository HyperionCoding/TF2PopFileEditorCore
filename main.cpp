#include <iostream>
#include <parser.h>

using namespace std;

int main()
{
	Parser& parser = Parser::getInstance();

	Block block = parser.parse_file("example.pop");
	block.print();

	return 0;
}
