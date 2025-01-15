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
	

	

	current_state = "menu";
	m_current_level = new Level();
	m_current_level->init();

	m_player = new Player("Player");
	m_player->init();
	graphics::playMusic(getFullAssetPath("AuebInvaders.mp3"),0.37f,true);
	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(m_asset_path + "OpenSans-Bold.ttf");
	

	
}
	

void GameState::draw() {
	if (current_state == "menu") {
		
		m_menu.texture = getFullAssetPath("menu3.png");
		SETCOLOR(m_menu.fill_color, 1.0f, 1.0f, 1.0f);
		graphics::drawRect(3, 3, 6, 6, m_menu);
		SETCOLOR(menu_brush_option.fill_color, 1.0f, 1.0f, 1.0f);
		menu_brush_option.fill_opacity = 1.0f;
		graphics::drawText(0.8f, 2.0f, 0.3f, "WELCOME TO SPACE INVADERS", menu_brush_option);
		graphics::drawText(1.6f, 3.0f, 0.3f, "Press ENTER to start", menu_brush_option);
		graphics::drawText(1.8f, 4.0f, 0.3f, "Press ESC to quit", menu_brush_option);
		graphics::drawText(1.8f, 5.0f, 0.3f, "Press P to pause", menu_brush_option);
	}
	else {

		if (!m_current_level) {
			return;
		}

		m_current_level->draw();
	}
	
}

void GameState::update(float dt)
{
	if (dt > 500) return;
	
	float sleep_time = std::max(0.7f,17.0f-dt);

	std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));

	if (current_state == "menu") {
		if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {  // ENTER key
			current_state = "playing";
			
		}
		
	}
	if (current_state == "playing") {

		if (!m_current_level) {
			return;
		}
		if (graphics::getKeyState(graphics::SCANCODE_P)) {  // PAUSE(P) key
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