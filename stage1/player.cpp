#include "sgg/graphics.h"
#include "player.h"
#include "gamestate.h"
#include "level.h"

#define SETCOLOR(c,r,g,b){c[0] =r,c[1]=g,c[2]= b;}


void Player::movePlayer(float dt)
{
	float delta_time = dt / 1000.0f;
	float move = 0.0f;
	if (graphics::getKeyState(graphics::SCANCODE_A))
		move -= 1.0f;
	if (graphics::getKeyState(graphics::SCANCODE_D))
		move += 1.0f;
	
	// X
	m_vx = std::min(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
	m_vx = std::max(-m_max_velocity, m_vx);
	//m_vx  -= 0.2f* m_vx/(0.1f + fabs(m_vx));
	m_vx *= 0.90f;
	if (fabs(m_vx) < 0.01)
		m_vx = 0;
	m_pos_x += delta_time * m_vx;
	

	m_pos_x = std::max(0.3f, std::min(m_pos_x, m_state->getCanvasWidth()-0.26f)); //check if it out of image bounds in x axis

	// Y
	float move2 = 0.0f;

	if (graphics::getKeyState(graphics::SCANCODE_W)) {
		/*m_vy -= graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f;*/
		move2 -= 1.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_S)) {
		/*m_vy -= graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f;*/
		move2 += 1.0f;
	}
	m_vy = std::min(m_max_velocity, m_vy + delta_time * move2 * m_accel_horizontal);
	m_vy = std::max(-m_max_velocity, m_vy);
	//m_vy -= 0.2f * m_vy / (0.1f + fabs(m_vy));
	m_vy *= 0.90f;
	if (fabs(m_vy) < 0.01)
		m_vy = 0.0f;
	//m_vy += delta_time * m_gravity;
	
	m_pos_y += m_vy * delta_time;
	m_pos_y = std::max(4.5f, std::min(m_pos_y, m_state->getCanvasHeight()-0.26f));   //check if it out of image bounds in y axis

}

void Player::update(float dt)
{
	float delta_time = dt / 1000.0f;
	
	const float velocity = 5.0f;
	
	//if (graphics::getKeyState(graphics::SCANCODE_A)) {
	//	m_pos_x -= velocity * delta_time;
	//}
	//if (graphics::getKeyState(graphics::SCANCODE_D)) {
	//	m_pos_x += velocity * delta_time;
	//}
	//if (graphics::getKeyState(graphics::SCANCODE_S)) {
	//	m_pos_y += velocity * delta_time;
	//}
	//if (graphics::getKeyState(graphics::SCANCODE_W)) {
	//	m_pos_y -= velocity * delta_time;
	//}
	//

	movePlayer(dt);
	m_state -> m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;



	GameObject::update(dt);
}
void Player::init()
{
	m_pos_x = m_state->getCanvasWidth() / 2.0f;
	m_pos_y = 7.0f;
	//m_width = m_width / 2.0f;
	m_width = m_width / 2.2f;

	m_height = m_height / 1.5f;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getFullAssetPath("Space-Invaders-ship.png");

	



}
void Player::debugDraw() {
	graphics::Brush player_debug_brush;
	player_debug_brush.fill_opacity = 0.1f;

	SETCOLOR(player_debug_brush.fill_color, 0.9f, 0.78f, 0.2f);
	SETCOLOR(player_debug_brush.outline_color, 0.7f, 0.6f, 0.5f);
	graphics::drawRect(m_pos_x + m_state->m_global_offset_x,
		m_pos_y + m_state->m_global_offset_y,
		m_width, m_height, player_debug_brush);
}
void Player::draw()
{
	
	graphics::drawRect(m_pos_x, m_pos_y, 1.0f, 1.0f, m_brush_player);

	if (m_state->m_debugging)
		debugDraw();

}



