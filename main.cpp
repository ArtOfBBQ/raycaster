#define OLC_PGE_APPLICATION

#include <iostream>

#include "modules/olcPixelGameEngine.h"
#include "modules/game.h"

class RayCaster : public olc::PixelGameEngine {
    public:
    RayCaster()
        :
        gs(nullptr)
    {
        std::string map_filename = "data/mymap.rcm";
        gs = new game::GameState(map_filename);
        
        sAppName = "RayCaster";
    }
   
    game::GameState * gs;
    
    bool OnUserCreate() override {
        // Called once at the start, so create things here
        return true;
    }
    
    bool OnUserUpdate(float fElapsedTime) override {

        if (GetKey(olc::Key::I).bHeld) {
            gs->register_key_held(
                game::Key::UP,
                fElapsedTime);
        } else if (GetKey(olc::Key::K).bHeld) {
            gs->register_key_held(
                game::Key::DOWN,
                fElapsedTime);
        } else {
            gs->player.hard_stop();
        }
        
        if (GetKey(olc::Key::L).bHeld) {
            gs->register_key_held(
                game::Key::RIGHT,
                fElapsedTime);
        }
        
        if (GetKey(olc::Key::J).bHeld) {
            gs->register_key_held(
                game::Key::LEFT,
                fElapsedTime);
        }
        
        gs->update_player_position(fElapsedTime);
        gs->update_column_heights();
        
        Clear(olc::BLACK);
        
        olc::Pixel purple = olc::Pixel(100,60,120);
        olc::Pixel dark_purple = olc::Pixel(40,0,40);
        olc::Pixel highlight = olc::Pixel(120,80,140);
        olc::Pixel * cur_color = nullptr;
        
        map::Tile & player_tile =
            gs->map.tile_at(
                gs->player.x,
                gs->player.y);
        
        // (left side of screen) draw 2d map
        for (int x = 0; x < gs->map.width; x += TILE_SIZE) {
            for (int y = 0; y < gs->map.height; y += TILE_SIZE)
            {
                map::Tile & cur_tile =
                    gs->map.tile_at(x, y);
                
                if (&cur_tile == &player_tile) {
                    cur_color = &highlight;
                } else if (cur_tile.wall) {
                    cur_color = &dark_purple;
                }
                else {
                    cur_color = &purple;
                }
                
                FillRect(
                    x,
                    y,
                    TILE_SIZE,
                    TILE_SIZE,
                    *cur_color);
            }
        }
        
        // Draw player on 2d map
        FillRect(
            gs->player.x,
            gs->player.y,
            5,
            5,
            olc::YELLOW);

        // Draw the leftmost ray on the 2d map
        for (
            int col_i = 0;
            col_i < gs->rays_x.size();
            col_i++)
        {
            for (
                int i=0;
                i < gs->rays_x.at(col_i).size();
                i++)
            {
                Draw(
                    gs->rays_x.at(col_i).at(i),
                    gs->rays_y.at(col_i).at(i),
                    olc::GREEN);
            }
        }
        
        // (left side of screen) draw 'rays' that make
        // up a pseudo 3d first person view

        float fp_screen_left = gs->map.width + 5;

        // draw ceiling regardless of rays
        for (int ceil_y = 0; ceil_y < FP_SCREEN_HEIGHT / 2; ceil_y++) {
            FillRect(
                fp_screen_left,
                ceil_y,
                FP_SCREEN_WIDTH, 
                1,
                olc::Pixel(
                    50 - (0.08 * ceil_y),
                    0,
                    50 - (0.08 * ceil_y)));
        }

        // draw floor regardless of rays
        for (
            int floor_y = FP_SCREEN_HEIGHT / 2;
            floor_y < FP_SCREEN_HEIGHT;
            floor_y++) {
            FillRect(
                fp_screen_left,
                floor_y,
                FP_SCREEN_WIDTH,
                1,
                olc::Pixel(
                    70 + (0.08 * (floor_y - (FP_SCREEN_HEIGHT / 2))),
                    0,
                    70 + (0.08 * (floor_y - (FP_SCREEN_HEIGHT / 2)))));
        }
        
        float ray_width = FP_SCREEN_WIDTH / RAY_COUNT;
        
        for
        (int i = 0; i < RAY_COUNT; i++) {
            float cur_wall_height = gs->column_heights.at(i);
            
            float ceil_height =
                (FP_SCREEN_HEIGHT - cur_wall_height) / 2.0f;
            /*
            float floor_height =
                FP_SCREEN_HEIGHT -
                    (ceil_height + cur_wall_height);
            */
            
            // draw wall
            if (cur_wall_height > 0.0f) {
                FillRect(
                    fp_screen_left + (i * ray_width),
                    ceil_height,
                    ray_width + 1,
                    cur_wall_height,
                    olc::Pixel(
                        100 + (0.1 * cur_wall_height),
                        60 + (0.06 * cur_wall_height),
                        120 + (0.12 * cur_wall_height)));
            }
        }
        
        return true;
    }
};


int main(int argc, char const *argv[]) {

	RayCaster ray_caster;
	if (ray_caster.Construct(1600, 700, 1, 1))
		ray_caster.Start();
        
	return 0;
}

