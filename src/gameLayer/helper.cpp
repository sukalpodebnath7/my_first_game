#include "helper.h"
#include <raylib.h>

Rectangle getTextureAtlas(int x, int y, int px, int py) {
	return Rectangle{ (float)x * px, (float)y * py, (float)px, (float)py };
}