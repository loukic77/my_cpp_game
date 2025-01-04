#include "laser.h"
#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "sgg/graphics.h"
#include <iostream>
#include "timer.h"

#define SETCOLOR(c,r,g,b){c[0] =r,c[1]=g,c[2]= b;}

using namespace std;

void Laser::draw()
{	
	if (is_active()) {
		graphics::drawRect(m_pos_laser_x, m_pos_laser_y , 0.04f, 0.15f, m_brush_laser);

	}
}

void Laser::update(float dt)
{


	if (is_active()) {
		m_pos_laser_y -= 0.07f;  // laser goes up
		if (m_pos_laser_y  < 0.0f) {  // out of canvas bounds(top left corner is 0(0,0))
			m_active = false;  // laser gets deactivated
		}
	}
	
	//GameObject::update(dt);

}

void Laser::init()
{
	SETCOLOR(m_brush_laser.fill_color, 1.0f, 0.965f, 0.008f);
	SETCOLOR(m_brush_laser.outline_color,0.0f, 0.0f, 0.000f);

	m_active = true;
	
} 

//void Laser::setActive(bool m_active) {
//	float m_collision_time = graphics::getGlobalTime() / 1000.0f;
//	if (m_collision_time >= 0.0f) {
//		float elapsed = (graphics::getGlobalTime() / 1000.0f) - m_collision_time;
//		if (elapsed > 0.1f) { // Show laser for 0.1 seconds after collision
//			m_active = false;
//		}
//	}
//}




Laser::Laser()
{
}

Laser::~Laser()
{
}
