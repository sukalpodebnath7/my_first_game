#include <buildStructs.h>
#include <gameMap.h>
#include <blocks.h>

void buildTree(GameMap& gameMap, int x, int y) {
	for (int i = 0; i < 5; i++) {
		gameMap.getBlock(x, y - i).type = Block::woodLog;
	}

	for (int i = -3; i <= 3; i++) {
		if (i) {
			gameMap.getBlock(x - i, y - 4).type = Block::leaves;
		}
	}

	for (int i = -2; i <= 2; i++) {
		gameMap.getBlock(x - i, y - 5).type = Block::leaves;
	}

	for (int i = -1; i <= 1; i++) {
		gameMap.getBlock(x - i, y - 6).type = Block::leaves;
	}
	for (int i = -1; i <= 1; i++) {
		gameMap.getBlock(x - i, y - 7).type = Block::leaves;
	}
	gameMap.getBlock(x, y - 8).type = Block::leaves;
}