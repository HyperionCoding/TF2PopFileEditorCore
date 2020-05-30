#include <iostream>
#include <parser.h>

using namespace std;

int main()
{
	std::string filepath;

	std::cout << "Input filepath: ";
	std::getline(std::cin, filepath);

	// Fix filepaths that use backslashes
	std::replace(filepath.begin(), filepath.end(), '\\', '/');
	filepath = std::string(
				*(filepath.begin()) == '\"' ? filepath.begin()+1 : filepath.begin(),
				*(filepath.end()-1) == '\"' ? filepath.end()-1 : filepath.end());

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
	writefile << block.print(0, true);

	std::cout << block.print(0, true) << std::endl;

	return 0;
}
