#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include "player.h"
#include "timer.h"

class Obstacle :public GameObject, public Box {
	float pos_x, pos_y;
	graphics::Brush m_brush_obstacle;

public:
	void draw();
	void update(float dt);
	void init();
	std::vector<Box> blocks;
	static std::vector<std::vector<int>> grid;
	Obstacle(float posx, float posy) :pos_x(posx), pos_y(posy) {
		m_brush_obstacle.fill_opacity = 1.0f;
		m_brush_obstacle.outline_opacity = 1.0f;
	};
	~Obstacle();
};