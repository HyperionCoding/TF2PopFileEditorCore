#include "block.h"


Block::Block()
{
	id_ = generate_id();
	std::cout << "Generated block with ID: " << id_ << std::endl;
}

int Block::generate_id()
{
	static int id = 0;
	id++;
	return (id-1);
}

void Block::test_id()
{
	std::cout << generate_id() << std::endl;
}

std::string Block::print()
{
	std::stringstream ss;

	// Header
	ss << type_ << "\n{\n";

	// Keyvalues
	for(KeyValuePair kv : keyvalues_){
		ss << kv.key << " " << kv.value << "\n";
	}

	// Children
	for(Block ch : children_){
		ss << ch.print();
	}

	// Close
	ss << "}\n";

	return ss.str();
}

void Block::set_type(std::string type)
{
	type_ = type;
}

bool Block::add_children(Block b)
{
	children_.push_back(b);

	return true;
}
