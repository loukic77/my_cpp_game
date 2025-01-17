#pragma once
#include "gameobject.h"
#include "sgg/graphics.h"
#include <list>
#include <vector>
#include "player.h"
#include "laser.h"
#include "timer.h"
#include "explosionPiece.h"
#include "Obstacle.h"
#include <vector>
#include <chrono>
#include <thread>

class explosion :public GameObject, public Box {
	float m_pos_x, m_pos_y;
	int count = 0;
	graphics::Brush m_brush_explosions;
	float last_time = graphics::getGlobalTime() / 1000.0f;

	
	vector<string> frames = {
				m_state->getFullAssetPath("explosion0.png"),
				m_state->getFullAssetPath("explosion1.png"),
				m_state->getFullAssetPath("explosion2.png"),
				m_state->getFullAssetPath("explosion3.png"),
				m_state->getFullAssetPath("explosion4.png"),
				m_state->getFullAssetPath("explosion5.png")
	};;
public:
	bool flag = true;
	void draw();
	void update(float dt);
	explosion(float x, float y) :m_pos_x(x), m_pos_y(y) {};
};