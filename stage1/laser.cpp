#include "laser.h"
#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "sgg/graphics.h"
#include <iostream>

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

	float delta_time = dt / 1000.0f;
	if (is_active()) {
		m_pos_laser_y -= delta_time*m_velocity_laser*laser_direction;  // laser goes up
		if (m_pos_laser_y  < 0.0f || m_pos_laser_y>8.0) {  // out of canvas bounds(top left corner is 0(0,0))
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






void Laser::setLaserDirection(bool flag)
{
	laser_direction = (flag) ? -1 : 1;   //ternary op( if flag laser_direction=-1 and laser goes down) 

}



Laser::~Laser()
{
}
