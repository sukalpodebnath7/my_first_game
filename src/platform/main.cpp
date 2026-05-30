#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>
#include <gameMain.h>

int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "my game");
	SetExitKey(KEY_NULL);
	SetTargetFPS(240);


	rlImGuiSetup(true);


	if (!initGame()) {
		return 0;
	}


	while (!WindowShouldClose()) {
		BeginDrawing();

		rlImGuiBegin();
		ClearBackground(BLACK);

		if (!updateGame()) {
			CloseWindow();
		}


		rlImGuiEnd();

		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	closeGame();
	return 0;
}