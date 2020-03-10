#include <iostream>
#include <parser.h>

using namespace std;

int main()
{
	Parser& parser = Parser::getInstance();

	Block block = parser.parse_file("example.pop");
	std::cout << block.print() << std::endl;

	return 0;
}
