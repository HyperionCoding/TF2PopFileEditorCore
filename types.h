#ifndef TYPES_H
#define TYPES_H
#include <string>
#include <map>

enum BlockType { BlockNone, WaveSchedule, WaveSpawn, Wave, TFBot};
extern std::map<std::string, BlockType> BlockTypes;
enum Keys { StartingCurrency };

struct KeyValuePair{
	int id;
	Keys key;
	std::string value;
};

#endif // TYPES_H
