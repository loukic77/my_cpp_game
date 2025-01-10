#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include "player.h"
#include "timer.h"

class Alien :public GameObject, public Box {
	graphics::Brush m_brush_alien;
	float m_alien_x;
	float m_alien_y;
	float velocity_x = 0.002f;
	float velocity_y = 0.09f;
    static bool reverseDirection ;
public:
	void draw();
	void update(float dt);
	void init();
	//void setActive(bool m_active);
	Alien();
	~Alien();
};