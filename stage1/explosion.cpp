#pragma once
#include "explosion.h"
#include "gameobject.h"
#include "sgg/graphics.h"
#include <list>
#include <vector>
#include "player.h"
#include "laser.h"
#include "explosionPiece.h"
#include "Obstacle.h"
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
void explosion::draw()
{
	if (flag) {
		//std::cout << "Explosion Frame: " << i << ", Position: (" << m_pos_x << ", " << m_pos_y << "), Flag: " << flag << std::endl;
		
		m_brush_explosions.texture = frames[count];
		
;		graphics::drawRect(m_pos_x, m_pos_y, 0.3f, 0.3f, m_brush_explosions);
	}
}

void explosion::update(float dt)
{	
	if (!flag) return;
	m_brush_explosions.outline_opacity = 0.0f;

	float current_time = graphics::getGlobalTime() / 1000.0f;  // Get current time in seconds
	if (count < frames.size()-1) {
		if (current_time - last_time >= 0.1f) {
			count++;
			m_brush_explosions.texture = frames[count];
			
			last_time = current_time;
		}
	
	}
	else {
		//cout << "finally";
		flag = false;
	}
}
