#include "explosionPiece.h"
#include <string>
void explosionPiece::move_explosion_piece(float dt)
{
	float delta_time = dt / 1000.0f;
	if (m_part=="left")
		m_pos_x -= delta_time * velocity_x;
	else if(m_part=="right")
		m_pos_x += delta_time * velocity_x;

	velocity_y += m_gravity * delta_time;
	m_pos_y += m_gravity * delta_time;

}

void explosionPiece::update(float dt) {
	if ( m_pos_y>8.0) {  // out of canvas bounds(top left corner is 0(0,0))
		m_active = false;  // laser gets deactivated
	}
}
