#include "block.h"


Block::Block(std::string type)
{
	id_ = generate_id();
	type_ = type;
	std::cout << "Generated block with ID: " << id_ << std::endl;
}

std::string Block::print(int depth, bool debug)
{
	std::stringstream ss;

	// Header
	if(debug){
		ss << indent(depth) << type_ << "\t// ID:" << id_ << "\n" << indent(depth) << "{\n";
	}else{
		ss << indent(depth) << type_ << "\n" << indent(depth) << "{\n";
	}

	// Keyvalues
	for(KeyValuePair kv : keyvalues_){
		if(debug){
			ss << indent(depth+1) << kv.key << " " << kv.value << "\t// ID:" << kv.id << "\n";
		}else{
			ss << indent(depth+1) << kv.key << " " << kv.value << "\n";
		}
	}

	// Line between keys and children
	if(keyvalues_.size() != 0){
		ss << "\n";
	}

	// Children
	for(Block ch : children_){
		ss << ch.print(depth+1, debug);
	}

	// Close
	ss << indent(depth) << "}\n";

	return ss.str();
}

void Block::set_type(std::string type)
{
	type_ = type;
}

std::vector<Block> Block::get_children()
{
	return children_;
}

bool Block::add_children(Block b)
{
	children_.push_back(b);

	return true;
}

bool Block::add_keyvalue(KeyValuePair kv)
{
	keyvalues_.push_back(kv);
	return true;
}

std::string Block::indent(int count)
{
	std::string s;
	for(int i=0; i<count; i++){
		s += "\t";
	}

	return s;
}
