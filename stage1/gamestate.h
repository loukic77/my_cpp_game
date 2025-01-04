#pragma once

#include "sgg/graphics.h"
#include <string>
using namespace std;

class GameState {
private:
	float m_canvas_width = 6.0f;
	float m_canvas_height = 6.0f;

	
	std::string m_asset_path = "assets/";

	static GameState* m_unique_instance;
	GameState();

	class Player* m_player = 0;
	class Level* m_current_level = 0;
	class Laser* m_laser = 0;

public:
	float m_global_offset_x = 0.0;
	float m_global_offset_y = 0.0;
	bool m_debugging = false;

	void init();
	void draw();
	void update(float dt);

	static GameState* getInstance();
	~GameState();

	float getCanvasWidth() {
		return m_canvas_width;
	}
	float getCanvasHeight() {
		return m_canvas_height;
	}
	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);
	class Player* getPlayer() { return m_player; }
	class Laser* getLaser() { return m_laser; }

};