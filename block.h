#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include <types.h>

class Block
{
public:
	Block();

	static int generate_id();
	void test_id();

	Block copy(const Block b);
	std::string print();

	int get_id();

	void set_type(std::string type);

	Block get_parent();
	void set_parent(Block* b);

	std::vector<Block> get_children(const BlockType key);
	void set_children(std::vector<Block> bs);
	bool add_children(Block b);
	bool remove_children(int id);

	std::vector<KeyValuePair> get_keyvalues(const Keys key);
	void set_keyvalues(std::vector<KeyValuePair> kvs);
	bool add_keyvalue(Keys key, std::string value);
	bool remove_keyvalue(KeyValuePair kv);

private:
	int id_ = -1;
	std::string type_ = "";
	Block* parent_ = nullptr;
	std::vector<KeyValuePair> keyvalues_;
	std::vector<Block> children_;
};

#endif // BLOCK_H
