#define RAY_COUNT 120.0f

#include <vector>
#include <string>
#include <fstream>

#include "map.h"


namespace game {

    enum Key {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    
    float wrap_radians_angle(float input);
    
    class Player {
    public:
        Player()
            :
            x(100.0f),
            y(100.0f),
            angle(2.5f),
            velocity_x(0.0f),
            velocity_y(0.0f)
        {}
        
        int get_x_tile() const;
        int get_y_tile() const;
        
        void thrust(const float time_elapsed);
        void thrust_back(const float time_elapsed);
        void decelerate(const float time_elapsed);
        void rotate_left(const float time_elapsed);
        void rotate_right(const float time_elapsed);
        void hard_stop();
        
        void update_position(const float time_elapsed);
        
        float x;
        float y;
        float angle;
        float velocity_x;
        float velocity_y;
    };
    
    class GameState {
    public:
        GameState(std::string & map_filename)
            :
            map(map::map_from_file(map_filename))
        {
            for (int _ = 0; _ < RAY_COUNT; _++) {
                ray_angles.push_back(0.0f);
                column_heights.push_back(20.0f + _);
                rays_x.push_back({});
                rays_y.push_back({});
            }
            
            assert(column_heights[0] < column_heights[5]);
        }
        
        map::Map map;
        Player player;
        
        std::vector<float> ray_angles;
        std::vector<float> column_heights;
        std::vector<std::vector<float>> rays_x;
        std::vector<std::vector<float>> rays_y;
        
        void update_player_position(const float time_elapsed);
        void update_column_heights();
        
        void register_key_held(
            const Key key,
            const float time_elapsed);
    };
}

