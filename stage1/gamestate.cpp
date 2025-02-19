#include "gamestate.h"
#include "level.h"
#include "player.h"
#include <thread>
#include <chrono>
#include "laser.h"
#include <iostream>
#define SETCOLOR(c,r,g,b){c[0] =r,c[1]=g,c[2]= b;}

GameState::GameState()
{
}

void GameState::init() {
	

	if (m_current_level) {
		delete m_current_level;
		m_current_level = nullptr;
	}
	if (m_player) {
		delete m_player;
		m_player = nullptr;
	}

	current_state = "menu";
	m_current_level = new Level();
	m_current_level->init();
	
	m_player = new Player("Player");
	m_player->init();
	graphics::playMusic(getFullAssetPath("AuebInvaders.mp3"),0.29f,true);
	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(m_asset_path + "OpenSans-Bold.ttf");
	

	
}
	

void GameState::draw() {
	if (current_state == "menu") {
		// Draw background
		m_menu.texture = getFullAssetPath("menu4.png");
		SETCOLOR(m_menu.fill_color, 1.0f, 1.0f, 1.0f);
		graphics::drawRect(3, 3, 6, 6, m_menu);

		// Draw menu options with boxes
		float y_position = 3.0f;  // Starting position for menu options
		float box_width = 2.5f;   // Width of the box
		float box_height = 0.4f;  // Height of the box
		float text_size = 0.3f;   // Text size

		for (size_t i = 0; i < menuOptions.size(); ++i) {
			graphics::Brush box_brush;
			SETCOLOR(box_brush.fill_color, 0.2f, 0.2f, 0.2f);  // Default box color (dark gray)
			box_brush.fill_opacity = 0.5f;

			if (i == selectedOption) {
				// Highlight box for selected option
				SETCOLOR(box_brush.fill_color, 0.133f, 0.341f, 0.969f);  // Yellow highlight
				box_brush.fill_opacity = 0.8f;
			}

			// Draw the box
			graphics::drawRect(3.0f, y_position, box_width, box_height, box_brush);

			// Center the text
			float text_x = 3.0f - (menuOptions[i].length() * text_size * 0.30f);  // Adjust based on text length
			float text_y = y_position + (box_height * 0.25f);  // Center text vertically

			// Draw the text inside the box
			graphics::Brush text_brush;
			SETCOLOR(text_brush.fill_color, 1.0f, 1.0f, 1.0f);  // White text
			graphics::drawText(text_x, text_y, text_size, menuOptions[i], text_brush);

			y_position += 0.6f;  // Move down for the next option
		}
	}
	else if (current_state == "playing") {
		if (!m_current_level) return;
		m_current_level->draw();
	}
	
}

void GameState::update(float dt)
{
	if (dt > 500) return;

	float sleep_time = std::max(0.7f, 17.0f - dt);
	std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));

	if (current_state == "menu") {
		// Navigation
		if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {  // Down arrow
			selectedOption = (selectedOption + 1) % menuOptions.size();  // Moves to next option
			std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Delay to prevent rapid input
		}

		if (graphics::getKeyState(graphics::SCANCODE_UP)) {  // Up arrow
			selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();  // Move to previous option
			std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Delay to prevent rapid input
		}

		// Handle selection with ENTER key
		if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
			if (menuOptions[selectedOption] == "PLAY") {
				current_state = "playing";  // Transition to the game
			}
			else if (menuOptions[selectedOption] == "CONTROLS") {
				graphics::playSound(getFullAssetPath("controls22.mp3"),1.0f);


			}
			else if (menuOptions[selectedOption] == "QUIT") {
				graphics::stopMessageLoop();  // Exit game
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Prevent rapid input
		}
	}
	else if (current_state == "playing") {
		// Game logic
		if (!m_current_level) return;

		if (graphics::getKeyState(graphics::SCANCODE_P)) {  // Pause game
			current_state = "menu";
			return;
		}

		m_current_level->update(dt);
		m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
	}
	
	
}

GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr) {
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

GameState::~GameState()
{
	if (m_player)
		delete m_player;
	if (m_current_level)
		delete m_current_level;
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}

GameState* GameState::m_unique_instance = nullptr;