#include <iostream>

#include "sgg/graphics.h"
#include <string>
#include <cmath>
#include "gamestate.h"

#define SETCOLOR(c,r,g,b){c[0] =r,c[1]=g,c[2]= b;}
using namespace std;
graphics::Brush m_menu;




void init() {
	GameState::getInstance()->init();
}


void draw() {
	
	GameState::getInstance()->draw();
	

}

void update(float dt) {
	GameState::getInstance()->update(dt);
}



int main() {

	graphics::createWindow(800,800,"Space Invaders");
	init();

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(GameState::getInstance()-> getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);


	graphics::startMessageLoop();

}