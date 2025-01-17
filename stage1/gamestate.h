#pragma once

#include "sgg/graphics.h"
#include <string>

#define SETCOLOR(c,r,g,b){c[0] =r,c[1]=g,c[2]= b;}

using namespace std;

class GameState {
private:
	float m_canvas_width = 6.0f;
	float m_canvas_height = 6.0f;
	graphics::Brush m_menu;
	graphics::Brush menu_brush_option;

	std::string m_asset_path = "assets/";

	static GameState* m_unique_instance;
	GameState();
	
	

	class Player* m_player = 0;
	class Level* m_current_level = 0;
	class Laser* m_laser = 0;
	int selectedOption = 0; // Tracks the currently selected menu option
	vector<string> menuOptions = { "PLAY", "CONTROLS", "QUIT" };
public:
	
	string current_state;
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
	class Level* getLevel() { return m_current_level; }
	class Laser* getLaser() { return m_laser; }

	int getSelectedOption() {
		return selectedOption;
	}

	// Setter for selectedOption
	void setSelectedOption(int option) {
		selectedOption = option;
	}

	// Getter for menuOptions
	vector<string> getMenuOptions() {
		return menuOptions;
	}

	// Setter for menuOptions (if needed)
	void setMenuOptions(const vector<string>& options) {
		menuOptions = options;
	}

};