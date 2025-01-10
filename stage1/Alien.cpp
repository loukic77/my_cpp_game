#include "Alien.h"
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include "player.h"
#include "timer.h"

void Alien::draw()
{
}

void Alien::update(float dt)
{
	
	
	/*if (m_alien_x + velocity_x > 5.7f || m_alien_x + velocity_x < 0.3f) {
		reverseDirection = true;
			
	}
	
	if (reverseDirection) {
		velocity_x = -velocity_x;
		for (auto& block : m_blocks) {
			block.m_pos_y += velocity_y;
		}
	}
	for (auto& block : m_blocks) {
		block.m_pos_x += velocity_x;
	}*/
}

void Alien::init()
{
}

Alien::Alien()
{
}

Alien::~Alien()
{
}
