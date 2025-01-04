#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "laser.h"
#include <list>
#include "timer.h"
#include "Spring.h"
#include "explosionPiece.h"
#include <iostream>
#include <chrono>
#include <thread>
using std::cout;
#define SETCOLOR(c,r,g,b){c[0] =r,c[1]=g,c[2]= b;}


void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	float x = box.m_pos_x ;
	float y = box.m_pos_y ;
	m_block_brush.texture = m_state->getFullAssetPath(m_block_names[i]+".png");
	m_block_brush.outline_opacity = 0.0f;
	
	graphics::drawRect(x ,y,0.3*m_block_size,0.3*m_block_size,m_block_brush);
	if (m_state->m_debugging) {
		graphics::drawRect(x, y, 0.4*m_block_size, 0.4*m_block_size, m_block_brush_debug);

	}
}
//void explodeAlien(int alienIndex, std::vector<Box>& m_blocks, float explosionRadius) {
//	Box& explodedAlien = m_blocks[alienIndex];
//
//	for (int i = 0; i < m_blocks.size(); ++i) {
//		if (i == alienIndex) continue; // Skip the alien being destroyed
//
//		Box& otherAlien = m_blocks[i];
//
//		// Calculate distance between exploded alien and this alien
//		float delta_x = otherAlien.m_pos_x - explodedAlien.m_pos_x;
//		float delta_y = otherAlien.m_pos_y - explodedAlien.m_pos_y;
//		float distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);
//
//		// If within explosion radius, apply a force
//		if (distance < explosionRadius && distance > 0.0f) {
//			float force = (explosionRadius - distance) * 10.0f; // Scale force with distance
//			float dir_x = delta_x / distance;
//			float dir_y = delta_y / distance;
//
//			otherAlien.m_pos_x +=
//		}
//	}
//}
void Level::checkCollisions(float dt)
{
	/*for (auto& box : m_blocks) {
		if (m_state->getPlayer()->intersect(box))
			printf("*");
	}*/
	float offset = 0.0f;
	/*for (auto& box : m_blocks) {
		if (offset = m_state->getPlayer()->intersectDown(box)) {
			m_state->getPlayer()->m_pos_y += offset;

			if (m_state->getPlayer()->m_vy > 1.0f)
				graphics::playSound(m_state->getFullAssetPath("metal2.wav"), 0.5f);

			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}
		for (auto& box : m_blocks) {
			if (offset = m_state->getPlayer()->intersectSideways(box)) {
				m_state->getPlayer()->m_pos_x += offset;
				m_state->getPlayer()->m_vx = 0.0f;

				break;
			}
		}

	
		for (auto& box : m_blocks) {
			if (offset = m_state->getPlayer()->intersectUp(box)) {
				m_state->getPlayer()->m_pos_y -= offset;

				m_state->getPlayer()->m_vy = 0.0f;

				break;
			}
		}
		
	}*/
	
	for (auto* new_laser : m_laser_objects) {
		Box box1 = Box(new_laser->get_m_pos_laser_x(), new_laser->get_m_pos_laser_y(), m_block_size, m_block_size);
		for (int i = 0; i < m_blocks.size();) {
			if (box1.intersect(m_blocks[i])) {

				new_laser->setActive(false);
				explosionPiece piece1 = explosionPiece(m_blocks[i].m_pos_x - m_blocks[i].m_width / 2.0f, m_blocks[i].m_pos_y , m_blocks[i].m_height, m_blocks[i].m_width/2.0f,"right");
				explosion_pieces.push_back(piece1);
				explosion_pieces_names.push_back(m_block_names[i] + "1");
				cout << m_block_names[i] + "1";
				explosionPiece piece2 = explosionPiece(m_blocks[i].m_pos_x + m_blocks[i].m_width / 2.0f, m_blocks[i].m_pos_y , m_blocks[i].m_height, m_blocks[i].m_width / 2.0f,"left");
				explosion_pieces.push_back(piece2);
				explosion_pieces_names.push_back(m_block_names[i]+"2");


				m_blocks.erase(m_blocks.begin() + i);
				m_block_names.erase(m_block_names.begin()+i);
			}
			else { i++; }

				
				//m_laser_objects.remove(laser);
			
		}
	}
	/*for (int i = 0; i < m_blocks.size();) {
		for (int j = 0; j < explosion_pieces.size(); j++) {
			if (m_blocks[i].intersect( (Box&) explosion_pieces[i])) {
				explosion_pieces[i].velocity_x -= 0.1f;
				explosion_pieces[i].velocity_y -= 0.1f;
			}
		}
	}*/
}

void Level::update(float dt)
{
	if (m_state->getPlayer()->is_active()) {
		m_state->getPlayer()->update(dt);
	}
	//m_pos_x = std::max(0.0f, std::min(m_pos_x, m_state->getCanvasWidth()));
	//m_pos_y = std::max(0.0f, std::min(m_pos_y, m_state->getCanvasHeight()));
	//checkCollisions();
	//if (m_state->getLaser()->is_active()) {
	//	m_state->getLaser()->update(dt);
	//}
	//std::cout << m_timer->isRunning();
	//std::cout << m_timer->m_val;
	//if (m_timer->isRunning()) {
	//	can_shoot = false;
	//}
	///*if (m_timer->m_val == 0.5f) {
	//	m_timer->stop();
	//}*/
	/*std::cout << m_timer;
	if (!m_timer) {
		std::cout << "Error: m_timer is null!" << std::endl;
	}*/
	
	

	
	

	if (graphics::getKeyState(graphics::SCANCODE_SPACE) ) {
		auto currentTime = std::chrono::steady_clock::now();             //o twrinos xronos
		float elapsed = std::chrono::duration<float>(currentTime - lastShotTime).count();           //o xronos apo thn prhgoumenh bolh(h apo thn arxh an einai h prwth bolh)
		if (elapsed >= cooldown) {                       
			
			lastShotTime = currentTime;  // reset the timer
			std::chrono::steady_clock::time_point lastShotTime = std::chrono::steady_clock::now();       //krataw sth mnhmh xrono gia epomenh bolh
			Laser* new_laser = new Laser();
			new_laser->init();
		//	new_laser->setActive(true);
			new_laser->draw();
			m_laser_objects.push_back(new_laser);
		}
		
	}
	for (auto it = m_laser_objects.begin(); it != m_laser_objects.end();) {
		(*it)->update(dt);  // Update the laser

		// If the laser goes off-screen, remove it from the list
		if (!(*it)->is_active()) {     //is_active xrhsimpoieitai klhronomika apo GameObject
			delete* it;  // Delete the laser
			it = m_laser_objects.erase(it);  // Remove from list and update iterator
		}
		else {
			++it;
		}
		
	}
	checkCollisions( dt);
	bool reverseDirection = false;
	for (const auto& block : m_blocks) {
		if (block.m_pos_x + velocity_x > 5.7f || block.m_pos_x + velocity_x < 0.3f) {
			reverseDirection = true;
			break;
		}
	}
	if (reverseDirection) {
		velocity_x = -velocity_x;
		for (auto& block : m_blocks) {
			block.m_pos_y += velocity_y;
		}
	}
	for (auto& block : m_blocks) {
		block.m_pos_x += velocity_x;
	}

	for (auto& piece : explosion_pieces) {
		piece.move_explosion_piece(dt);
	}
	GameObject::update(dt);
}



void Level::init()
{
	
	/*m_blocks.push_back(Box(5* m_block_size, 6* m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(4 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(3 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(2 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(6 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(7 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(7 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(3 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(4 * m_block_size, 3 * m_block_size, m_block_size, m_block_size));

	m_block_names.push_back("block8.png");
	m_block_names.push_back("block1.png");
	m_block_names.push_back("block7.png");
	m_block_names.push_back("block6.png");
	m_block_names.push_back("block10.png");
	m_block_names.push_back("block1.png");
	m_block_names.push_back("block2.png");
	m_block_names.push_back("block8.png");
	m_block_names.push_back("block3.png");

	m_block_brush.outline_opacity = 0.0f;
	m_block_brush_debug.fill_opacity = 0.1f;

	SETCOLOR(m_block_brush_debug.fill_color, 0.2f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);*/

		for (float i = 0.5; i <= 5.5; i=i+0.5) {
			for (float j = 0.5; j <= 2.5; j=j+0.5){
				m_blocks.push_back(Box(i * m_block_size, j * m_block_size, -0.7f,-0.7f));        //dinw arnhtiko height kai width.sto drawBlock ta megalwnw
				m_block_names.push_back("alien");
			}
		}
		Spring spring(0.5f, 3.0f, 0.1f);  //creation of spring



	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();


}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x =m_state->m_global_offset_x/4.0f +w / 2.0f;
	float offset_y = m_state->m_global_offset_y/4.0f + h / 2.0f;

	//draw background
	graphics::drawRect(3.0f, 3.0f,w,h*1.0f,m_brush_background);

	if (m_state->getPlayer()->is_active()) {
		m_state->getPlayer()->draw();
	}

	for (Laser* new_laser : m_laser_objects) {
		if (new_laser->is_active())
			new_laser->draw();
	}

	

	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();

	for (int i = 0; i < m_blocks.size(); i++)
	{
		drawBlock(i);
	}
	for (int i = 0; i < explosion_pieces.size(); i++)
	{
		m_block_brush.texture = m_state->getFullAssetPath(explosion_pieces_names[i]+".png");
		m_block_brush.outline_opacity = 0.0f;

		graphics::drawRect(explosion_pieces[i].m_pos_x, explosion_pieces[i].m_pos_y, 0.15 * m_block_size, 0.3 * m_block_size, m_block_brush);
	}
}

Level::Level(const std::string& name)
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("1349325.png");
}

Level::~Level()
{
	for (auto p_gob : m_static_objects)
		if (p_gob) delete p_gob;
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) delete p_gob;

}
