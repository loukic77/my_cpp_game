#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include "player.h"


class Laser :public GameObject, public Box {
	graphics::Brush m_brush_laser;
	float m_pos_laser_x;
	float m_pos_x = m_pos_laser_x;
	float m_pos_laser_y;
	float m_pos_y = m_pos_laser_y;
	float m_velocity_laser = 6.5f;
	int laser_direction = 1;
	class Timer* timer = 0;
public:
	void draw();
	void update(float dt);
	void init();
	//void setActive(bool m_active);
	float get_m_pos_laser_y() { return m_pos_laser_y; }
	float get_m_pos_laser_x() { return m_pos_laser_x; };
	void set_m_pos_laser_y(float new_m_pos_laser_y) { m_pos_laser_y = new_m_pos_laser_y; };
	void setLaserDirection(bool flag);
	int get_laser_direction() { return laser_direction; };
	Laser() {
		m_pos_laser_x = m_state->getPlayer()->m_pos_x;
		m_pos_laser_y = m_state->getPlayer()->m_pos_y;
	}

	Laser(float block_x, float block_y) :m_pos_laser_x(block_x), m_pos_laser_y(block_y) {};
	~Laser();
};