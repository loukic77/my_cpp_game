#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include "player.h"
#include "timer.h"

struct explosionPiece : public Box, public GameObject {
public:
	float m_pos_x = 0.0f;
	float m_pos_y = 0.0f;
	float m_width = 1.0f;
	float m_height = 1.0f;
	string m_part;
	float velocity_x=0.5f;
	float velocity_y=0.005f;
	const float m_gravity = 3.0f;
	const float m_accel_vertical = 6.0f;
	void move_explosion_piece(float dt);
	void update(float dt);
	explosionPiece(float x, float y, float w, float h,string part)
		: m_pos_x(x), m_pos_y(y), m_width(w), m_height(h),m_part(part) {}

	
};