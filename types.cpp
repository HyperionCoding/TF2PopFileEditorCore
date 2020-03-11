#include <types.h>

std::map<std::string, BlockType> BlockTypes = {
	{"none", BlockNone},
	{"waveschedule", WaveSchedule},
	{"wavespawn", WaveSpawn},
	{"wave", Wave},
	{"tfbot", TFBot}
};

static int id = 0;
int generate_id()
{
	id++;
	return (id-1);
}
