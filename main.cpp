#include <iostream>
#include <parser.h>

using namespace std;

int main()
{
	std::string filepath;

	std::cout << "Input filepath: ";
	std::cin >> filepath;

	std::string out_path = filepath;
	for(auto iter=out_path.end(); iter != out_path.begin(); iter--){
		if(*iter == '.'){
			out_path.insert(iter, '_');
			break;
		}
	}

	Parser& parser = Parser::getInstance();
	Block block = parser.parse_file(filepath);

	std::ofstream writefile(out_path);
	writefile << block.get_children().at(0).print();

	std::cout << block.get_children().at(0).print(0, true) << std::endl;

	return 0;
}
