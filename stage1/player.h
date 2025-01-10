#pragma once
#include "gameobject.h"
#include "box.h" 

class Player :public GameObject,public Box {
	graphics::Brush m_brush_player;

	std::vector<std::string> m_sprites;

	const float m_gravity = 10.0f;
	const float m_accel_vertical = 6.0f;
	const float m_accel_horizontal = 20.0f;
	const float m_max_velocity = 6.0f;
	int lifes_remaining = 3;

	void movePlayer(float dt);
	
public:
	float m_vx = 0.0f;
	float m_vy = 0.0f;
	Player(std::string name): GameObject(name) {}
	void  update(float dt) override;
	void  draw() override;
	void  init() override;
	void debugDraw();
	int get_lifes_remaining() { return lifes_remaining; };
	void set_lifes_remaining(int lifes) { lifes_remaining = lifes; };
};