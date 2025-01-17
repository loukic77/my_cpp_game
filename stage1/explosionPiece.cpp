#include "explosionPiece.h"
#include <string>
#include "level.h"
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include <iostream>
#define SETCOLOR(c,r,g,b){c[0] =r,c[1]=g,c[2]= b;}


void explosionPiece::move_explosion_piece(float dt)
{
	
	float delta_time = dt / 1000.0f;
	if (m_part=="left")
		m_pos_x -= delta_time * velocity_x;
	else if(m_part=="right")
		m_pos_x += delta_time * velocity_x;

	velocity_y += m_gravity * delta_time;
	m_pos_y += m_gravity * delta_time;

	update(dt);
	
	
}

void explosionPiece::update(float dt) {
	if ( m_pos_y>8.0) {  // out of canvas bounds(top left corner is 0(0,0))
		m_active = false;  // laser gets deactivated
	}
	
	
}
void explosionPiece::draw() {
	if (flag) {
		graphics::drawRect(start_x, start_y, 0.3f, 0.3f, m_brush_explosions);
	}
}
void explosionPiece::init()
{
	
	/*explosions = m_state->getLevel()->get_expl_sprites();
	for (const auto& sprite : explosions) {
		std::cout << "Loaded sprite path: " << sprite << std::endl;
	}*/
}
