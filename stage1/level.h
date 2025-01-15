#pragma once
#include "gameobject.h"
#include "sgg/graphics.h"
#include <list>
#include <vector>
#include "player.h"
#include "laser.h"
#include "timer.h"
#include "explosionPiece.h"
#include "Obstacle.h"
#include <vector>
#include <chrono>
#include <thread>

class Level :public GameObject,public Box {
	graphics::Brush m_brush_background;
	graphics::Brush m_brush_heart;
	graphics::Brush m_highscore_text_brush;
	float m_center_x = 5.0f;	
	float m_center_y = 5.0f;

	
	const float m_block_size = 1.0f;
	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;
    graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;


	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;
	const float cooldown = 0.2f;
	std::chrono::steady_clock::time_point lastShotTime = std::chrono::steady_clock::now();   //arxikopoiw xrono gia thn prwth bolh
	std::list<Laser*> m_laser_objects;
	float velocity_x = 0.003f;
	float velocity_y = 0.09f;
	std::vector<float> force;
	std::vector<explosionPiece> explosion_pieces;
	std::vector<std::string> explosion_pieces_names;
	void drawBlock(int i);
	std::vector<Obstacle> obstacles;
	const float alien_shoot_cooldown = 0.8f;
	int score;
	vector<string> m_expl_sprites;

	vector<Obstacle> createObstacles();
	void checkCollisions(float dt);
public:
	vector<string> get_expl_sprites() { return m_expl_sprites; };
	void  update(float dt) override;
	void  draw() override;
	void  init() override;
	Level(const std::string & name = "Level0");
	~Level();
};