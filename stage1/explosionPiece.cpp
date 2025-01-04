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
