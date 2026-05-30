#pragma once
#include <vector>
#include <blocks.h>

struct GameMap {

	int w = 0;
	int h = 0;

	std::vector<Block> mapData;

	void create(int x, int y);
	Block& getBlock(int x, int y);
};