#ifndef TYPES_H
#define TYPES_H
#include <iostream>
#include <string>
#include <map>

enum BlockType { BlockNone, WaveSchedule, WaveSpawn, Wave, TFBot};
extern std::map<std::string, BlockType> BlockTypes;
enum Keys { StartingCurrency };

struct KeyValuePair{
	int id;
	std::string key;
	std::string value;
	std::string comment;
};

int generate_id();

#endif // TYPES_H
