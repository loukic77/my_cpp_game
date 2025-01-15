#include "Obstacle.h"
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include "player.h"
#include "timer.h"
#include <iostream>
#define SETCOLOR(c,r,g,b){c[0] =r,c[1]=g,c[2]= b;}


void Obstacle::draw()
{
   // cout << blocks.size();
    for (Box ob : blocks) {
       /* std::cout << "hes";
        std::cout << ob.m_pos_x<<"\n";
        std::cout << ob.m_pos_y<<"\n";
        std::cout << ob.m_width << "\n";*/
        graphics::Brush debug_brush;
        debug_brush.fill_opacity = 0.0f;
        debug_brush.outline_opacity = 1.0f;
        SETCOLOR(debug_brush.outline_color, 1.0f, 0.0f, 0.0f); // Red outline for debugging
        graphics::drawRect(ob.m_pos_x, ob.m_pos_y, ob.m_width, ob.m_height, debug_brush);

        SETCOLOR(m_brush_obstacle.fill_color, 1.0f, 0.965f, 0.008f);
        SETCOLOR(m_brush_obstacle.outline_color, 0.0f, 0.0f, 0.000f);
       // m_brush_obstacle.outline_opacity = 0.0f;
        //graphics::drawRect(3.0f, 4.0f, 1, 1, m_brush_obstacle);
        graphics::drawRect(ob.m_pos_x, ob.m_pos_y, ob.m_width, ob.m_height, m_brush_obstacle);
    }
}

void Obstacle::update(float dt)
{
}

vector<vector<int>> Obstacle::grid =
{
    { 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

void Obstacle::init()
{
    
    for (unsigned int row = 0; row < grid.size(); row++) {
        for (unsigned int column = 0; column < grid[0].size(); column++) {
          //  std::cout << grid[row][column] << " "; // Print each value in the grid
            if (grid[row][column] == 1) {
                float position_x = pos_x + column * 0.06f;  // each block is 3 pixels wide
                float position_y = pos_y + row * 0.06f;     // each block is 3 pixels 

                Box block(position_x, position_y, 0.06f, 0.06f);
                blocks.push_back(block);
                
            }
        }
    }
}



Obstacle::~Obstacle()
{
}
