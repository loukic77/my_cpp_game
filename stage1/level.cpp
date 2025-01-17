#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "laser.h"
#include <list>
#include "timer.h"
#include "Spring.h"
#include "explosionPiece.h"
#include "Obstacle.h"
#include "gamestate.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

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
vector<Obstacle> Level::createObstacles()
{
	float obstacle_width = Obstacle::grid[0].size() * 0.03f;
	cout<< obstacle_width;
	float gap = (m_state->getCanvasWidth() - (4 * obstacle_width)) / 5;

	for (int i = 0; i < 4; i++) {
		float offset_x = (i+1  ) * gap + i * obstacle_width;
		float ob_y = m_state->getCanvasHeight()/2.0f+1.7f;
		std::cout << offset_x << " " << ob_y << std::endl;
		obstacles.emplace_back(offset_x, ob_y); // Construct in place
		obstacles.back().init();            // Initialize the newly created obstacle
	}
	return obstacles;
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
			
		}
		
	}*/
	
	

	for (auto* new_laser : m_laser_objects) {
		Box box1 = Box(new_laser->get_m_pos_laser_x(), new_laser->get_m_pos_laser_y(), m_block_size, m_block_size);
		for (int i = 0; i < m_blocks.size();) {
			if (box1.intersect(m_blocks[i]) && new_laser->get_laser_direction() == 1.0f) {

				score += 1;
				new_laser->setActive(false);
				explosions.push_back(explosion(m_blocks[i].m_pos_x, m_blocks[i].m_pos_y));
				explosionPiece piece1 = explosionPiece(m_blocks[i].m_pos_x - m_blocks[i].m_width / 2.0f, m_blocks[i].m_pos_y, m_blocks[i].m_height, m_blocks[i].m_width / 2.0f, "right");
				piece1.init();
				explosion_pieces.push_back(piece1);
				explosion_pieces_names.push_back(m_block_names[i] + "1");
				
				explosionPiece piece2 = explosionPiece(m_blocks[i].m_pos_x + m_blocks[i].m_width / 2.0f, m_blocks[i].m_pos_y, m_blocks[i].m_height, m_blocks[i].m_width / 2.0f, "left");
				explosion_pieces.push_back(piece2);
				explosion_pieces_names.push_back(m_block_names[i] + "2");

				graphics::playSound(m_state->getFullAssetPath("DeathExpl.mp3"),0.9f);
				m_blocks.erase(m_blocks.begin() + i);
				m_block_names.erase(m_block_names.begin() + i);
				break;
			}
			else { i++; }
		}
		if (new_laser->is_active()) {
			for (auto& obstacle : obstacles) {
				for (int i = 0; i < obstacle.blocks.size();) {
					if (box1.intersect(obstacle.blocks[i]) && abs(obstacle.blocks[i].m_pos_x - box1.m_pos_x) < 0.04f && abs(obstacle.blocks[i].m_pos_y - box1.m_pos_y)<0.03f) { //second condition is for the laser to not hit two blocks at the same time


						new_laser->setActive(false);
						obstacle.blocks.erase(obstacle.blocks.begin() + i);
						break;
					}
					else {
						i++;
					}
				}
			}
		}
		
		if (new_laser->get_laser_direction() == -1 && m_state->getPlayer()->intersect(box1) && new_laser->is_active() && abs(m_state->getPlayer()->m_pos_x - box1.m_pos_x) < 0.2f && abs(m_state->getPlayer()->m_pos_y - box1.m_pos_y) < 0.04f) {      //checking if a laser hits the target(it has to not hit another box earlier too)
			m_state->getPlayer()->set_lifes_remaining(m_state->getPlayer()->get_lifes_remaining() - 1);
			graphics::playSound(m_state->getFullAssetPath("HpLoss.mp3"),0.8f);
			std::cout <<"lifes left: "<< m_state->getPlayer()->get_lifes_remaining() << endl;
			new_laser->setActive(false);
		}
				//m_laser_objects.remove(laser);
			
		
	}
	float offset = 0.0f;
	for (auto& obstacle : obstacles) {
		for (int i = 0; i < obstacle.blocks.size(); i++) {
			//cout << "player x=" << m_state->getPlayer()->m_pos_x << endl;
			//cout << "box x=" << obstacle.blocks[i].m_pos_x << endl;
			if (! m_state->getPlayer()->intersect(obstacle.blocks[i]))
				continue;


			if (offset = m_state->getPlayer()->intersectSideways(obstacle.blocks[i])) {
				m_state->getPlayer()->m_pos_x += offset;
				m_state->getPlayer()->m_vx = 0.0f;
				break;


			}
			if (offset = m_state->getPlayer()->intersectDown(obstacle.blocks[i])) {
				m_state->getPlayer()->m_pos_y += offset;

				

				m_state->getPlayer()->m_vy = 0.0f;

				break;
			}
			if (offset = m_state->getPlayer()->intersectUp(obstacle.blocks[i])) {
				m_state->getPlayer()->m_pos_y -= offset;


				m_state->getPlayer()->m_vy = 0.0f;

				break;
			}
		}
	}
	for (int i = 0; i < m_blocks.size();i++) {
		if (abs(m_blocks[i].m_pos_x - m_state->getPlayer()->m_pos_x) < 0.2f && abs(m_blocks[i].m_pos_y - m_state->getPlayer()->m_pos_y)<0.2f || m_blocks[i].m_pos_y>7.5f) {  //check if aliens hit spaceship
			m_state->getPlayer()->set_lifes_remaining(m_state->getPlayer()->get_lifes_remaining() - 1);
			graphics::playSound(m_state->getFullAssetPath("HpLoss.mp3"), 0.8f);
			std::cout << "lifes left: " << m_state->getPlayer()->get_lifes_remaining() << endl;
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
			graphics::playSound(m_state->getFullAssetPath("Bullet.mp3"), 0.6f);
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

	explosions.erase(
		std::remove_if(explosions.begin(), explosions.end(),
			[](const explosion& e) { return !e.flag; }),
		explosions.end());

	


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
		//if (!(&piece)->is_active()) {     //is_active xrhsimpoieitai klhronomika apo GameObject
			 // Delete the laser
			//explosion_pieces.erase(&piece);  // Remove from list and update iterator
		//}
	}
	//auto name_it = explosion_pieces_names.begin();  // Iterator for names
	//for (auto piece = explosion_pieces.begin(); piece != explosion_pieces.end();) {
	//	if (!piece->is_active()) {
	//		piece = explosion_pieces.erase(piece);               // Erase piece
	//		name_it = explosion_pieces_names.erase(name_it);     // Erase corresponding name
	//	}
	//	else {
	//		piece->move_explosion_piece(dt);                     // Move the explosion piece
	//		++piece;
	//		++name_it;
	//	}
	//	
	//}
	for (explosion& exp : explosions) {
		exp.update(dt);
	}

		

	static int frame_count = 0;
	static float last_time = graphics::getGlobalTime() / 1000.0f;

	frame_count++;
	float current_time = graphics::getGlobalTime() / 1000.0f;
	if (current_time - last_time >= 1.0f) {
		std::cout << "FPS: " << frame_count << std::endl;
		frame_count = 0;
		last_time = current_time;
	}
	float current_time_alien = graphics::getGlobalTime() / 1000.0f;
	static float last_time_alien = 0.0f;

	if (current_time_alien - last_time_alien > alien_shoot_cooldown && !m_blocks.empty()) {
		int randomIndex = rand() % m_blocks.size();
		std::cout << "Alien " << randomIndex << " shooting at (" << m_blocks[randomIndex].m_pos_x << ", " << m_blocks[randomIndex].m_pos_y << ")\n";

		Laser* new_laser = new Laser(m_blocks[randomIndex].m_pos_x, m_blocks[randomIndex].m_pos_y);
		new_laser->init();
		new_laser->setLaserDirection(true);
		m_laser_objects.push_back(new_laser);

		last_time_alien = current_time_alien;
	}
	
	if (m_state->getPlayer()->get_lifes_remaining()<=0 || score==55) {
		//m_state->current_state = "menu";
		m_state->init();
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
				if (j == 0.5f) {
					m_block_names.push_back("B18");
				}
				else if (j == 1.0f) {
					m_block_names.push_back("C16");
				}
				else if (j == 1.5f) {
					m_block_names.push_back("F4");
				}
				else if (j == 2.0f) {
					m_block_names.push_back("E2");
				}
				else if (j == 2.5f) {
					m_block_names.push_back("G2");
					//m_block_names.push_back("alien");
				}
			}
		}
		/*Obstacle m_obstacle(3.0f, 4.0f);
		m_obstacle.init();
		obstacles.push_back(m_obstacle);*/
		obstacles = createObstacles();


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
	graphics::drawRect(offset_x, offset_y,w*1.3f,h*1.3f,m_brush_background);

	float j = 5.75;
	for (int i = 0; i <	m_state->getPlayer()->get_lifes_remaining(); i++) {
		graphics::drawRect(j, 0.3f,0.3f, 0.3f, m_brush_heart);
		
		
		j = j-0.29f;
	}
	string score_text = "Score = " + std::to_string(score);
	graphics::drawText(0.1f, 0.3f, 0.2f,score_text,m_highscore_text_brush);

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
	for (Obstacle ob : obstacles) {
		ob.draw();
	}
	for (explosion exp : explosions) {
		exp.draw();
	}

	

}

Level::Level(const std::string& name)
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background4.png");

	m_brush_heart.outline_opacity = 0.0f;
	m_brush_heart.texture = m_state->getFullAssetPath("heart.png");
	graphics::setFont("OpenSans-Bold.ttf");
}

Level::~Level()
{
	for (auto p_gob : m_static_objects)
		if (p_gob) delete p_gob;
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) delete p_gob;

}
