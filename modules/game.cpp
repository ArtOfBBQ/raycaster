#include "game.h"

#include <iostream>
#include <cmath> 


namespace game {
    
    void Player::hard_stop() {
        velocity_x = 0.0f;
        velocity_y = 0.0f;
    }
    
    int Player::get_x_tile() const {
        return x / TILE_SIZE;
    }
    
    int Player::get_y_tile() const {
        return y / TILE_SIZE;
    }
    
    void Player::thrust(const float time_elapsed) {
        assert(angle >= 0.0f);
        assert(angle <= 6.29f);
        velocity_x += sinf(angle) * 400.0f * time_elapsed;
        velocity_y += -cosf(angle) * 400.0f * time_elapsed;
    }
    
    void Player::thrust_back(const float time_elapsed) {
        assert(angle >= 0.0f);
        assert(angle <= 6.29f);
        velocity_x -= sinf(angle) * 400.0f * time_elapsed;
        velocity_y -= -cosf(angle) * 400.0f * time_elapsed;
    }
    
    void GameState::update_player_position(
        const float time_elapsed)
    {
        const float new_x =
            player.x + (player.velocity_x * time_elapsed);
        const float new_y =
            player.y + (player.velocity_y * time_elapsed);
        
        if (!map.tile_at(new_x, new_y).wall) {
            player.x = new_x;
            player.y = new_y;
        } else {
            player.hard_stop();
        }
    }
    
    float wrap_radians_angle(float input) {
        if (input < 0.0f) {
            return 6.28f + fmod(input, 6.28f);
        }
        
        if (input > 6.28f) {
            return fmod(input, 6.28f);
        }

        return input;
    }
    
    void Player::rotate_left(const float time_elapsed) {
        angle -= (3.14f * time_elapsed);
        angle = wrap_radians_angle(angle);
    }
    
    void Player::rotate_right(const float time_elapsed) {
        angle += (3.14f * time_elapsed);
        angle = wrap_radians_angle(angle);
    }
    
    void GameState::register_key_held(
        const Key key,
        const float time_elapsed)
    {
        if (key == Key::UP) {
            player.thrust(time_elapsed);
        } else if (key == Key::DOWN) {
            player.thrust_back(time_elapsed);
        } 
        
        if (key == Key::RIGHT) {
            player.rotate_right(time_elapsed);
        }
        
        if (key == Key::LEFT) {
            player.rotate_left(time_elapsed);
        }
    }

    void GameState::update_column_heights() {
        float fov = 3.14f / 4.0f;
        
        float starting_angle = wrap_radians_angle(
            player.angle - (fov / 2.0f));
        float step = fov / RAY_COUNT;
        float final_angle = wrap_radians_angle(
            player.angle + (fov / 2.0f));
        
        for (
            int col_i = 0;
            col_i < column_heights.size();
            col_i++)
        {
            rays_x[col_i].clear();
            rays_y[col_i].clear();
            
            float cur_angle = wrap_radians_angle(
                starting_angle
                    + (step * col_i));
            ray_angles.at(col_i) = cur_angle;
            
            float step_x = sinf(cur_angle) * (TILE_SIZE / 5);
            float step_y = -cosf(cur_angle) * (TILE_SIZE / 5);
            
            float cur_x = player.x;
            float cur_y = player.y;
            
            while (
                cur_x >= 0.0f && cur_x <= map.width &&
                cur_y >= 0.0f && cur_y <= map.height)
            {
                rays_x[col_i].push_back(cur_x);
                rays_y[col_i].push_back(cur_y);
                
                if (map.tile_at(cur_x, cur_y).wall)
                {
                    column_heights.at(col_i) =
                        FP_SCREEN_HEIGHT - 
                            (std::sqrt(
                                std::pow(cur_x - player.x, 2) +
                                std::pow(cur_y - player.y, 2))
                            * 0.8);
                    
                    break;
                }
                
                cur_x += step_x;
                cur_y += step_y;
            }
        }
    }
}

