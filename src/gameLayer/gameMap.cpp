#include "gameMap.h"
#include <cassert>

void GameMap::create(int w, int h)
{
    this->w = w;
    this->h = h;

    mapData.clear();
    mapData.resize(w * h);
}

Block& GameMap::getBlock(int x, int y)
{
    static Block airBlock{};

    if (x < 0 || y < 0 || x >= w || y >= h)
        return airBlock;

    return mapData[x + y * w];
}