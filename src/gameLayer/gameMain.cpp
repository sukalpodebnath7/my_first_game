#include <raylib.h>
#include "gameMain.h"
#include <assetManager.h> 
#include <gameMap.h>
#include <helper.h>
#include <iostream>
#include <raymath.h>
#include <cmath>
#include <worldGenerate.h>
#include <imgui.h>



struct GameData {
	GameMap gameMap;
	Camera2D camera;

}gameData;

AssetManager assetManager;



bool initGame() {
    assetManager.loadAll();
	generateWorld(gameData.gameMap);

	gameData.camera.target = { 300,177 };
	gameData.camera.rotation = 0.0f;
	gameData.camera.zoom = 50.0f;

	return true;
}

bool updateGame() {

	float deltaTime = GetFrameTime();
	if (deltaTime > 1.f / 5) deltaTime = 1 / 5.f;

	gameData.camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

	

	ClearBackground({ 75,75,150,255 });


	static float CAMERA_SPEED = 10;
	if (IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= CAMERA_SPEED * GetFrameTime();
	if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += CAMERA_SPEED * GetFrameTime();
	if (IsKeyDown(KEY_UP)) gameData.camera.target.y -= CAMERA_SPEED * GetFrameTime();
	if (IsKeyDown(KEY_DOWN)) gameData.camera.target.y += CAMERA_SPEED * GetFrameTime();

	gameData.camera.target.x = Clamp(gameData.camera.target.x, 0.0f, gameData.gameMap.w - 1);
	gameData.camera.target.y = Clamp(gameData.camera.target.y, 0.0f, gameData.gameMap.h - 1);

	Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
	int blockX = (int)floor(worldPos.x);
	int blockY = (int)floor(worldPos.y);
	std::cout << blockX << " " << blockY << "\n";


	BeginMode2D(gameData.camera);

	Vector2 topLeftView = GetScreenToWorld2D({ 0,0 }, gameData.camera);
	Vector2 bottomRightView = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, gameData.camera);

	int startXView = floorf(topLeftView.x - 1);
	int endXView = ceilf(bottomRightView.x - 1);
	int startYView = floorf(topLeftView.y - 1);
	int endYView = ceilf(bottomRightView.y - 1);


	startXView = Clamp(startXView, 0, gameData.gameMap.w);
	endXView = Clamp(endXView, 0, gameData.gameMap.w);
	startYView = Clamp(startYView, 0, gameData.gameMap.h);
	endYView = Clamp(endYView, 0, gameData.gameMap.h);


	for (int y = startYView; y <= endYView; y++) {
		for (int x = startXView; x <= endXView; x++) {

			auto& b = gameData.gameMap.getBlock(x, y);
			if (b.type == Block::air) {	
				continue;
			}

			
			DrawTexturePro(
				assetManager.textures,
				getTextureAtlas(b.type, 0, 32, 32),
				{ (float)x, (float)y, 1, 1 },
				{ 0,0 },
				0.0f,
				WHITE
			);
		}
	}

	DrawTexturePro(
		assetManager.frame,
		{0,0,(float)assetManager.frame.width, (float)assetManager.frame.height},
		{ (float)blockX, (float)blockY, 1,1 },
		{ 0,0 },
		0.f,
		WHITE
	);



	EndMode2D();

	ImGui::Begin("Game controll");

	ImGui::SliderFloat("Camera zoom:", &gameData.camera.zoom, 1, 150);
	ImGui::SliderFloat("Camera speed:", &CAMERA_SPEED, 5, 100);

	ImGui::End();

	DrawFPS(10, 10);
	return true;
}


void closeGame() {
    
}