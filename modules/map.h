#include <vector>
#include <sstream>
#include <string>
#include <fstream>

#define FP_SCREEN_HEIGHT 690.0f
#define FP_SCREEN_WIDTH 950.0f
#define TILE_SIZE 40.0f

namespace map {
    class Tile {
    public:
        Tile() :
            wall(false)
        {}

        Tile(bool wall) :
            wall(wall)
        {}
        
        bool wall;
    };
    
    class Map {
    public:
        Map(std::stringstream & input) 
            : 
            width(0),
            height(0),
            width_tiles(0),
            height_tiles(0)
        {
            std::string map_data = input.str();
            for (char tile_char : map_data) {
                
                if (tile_char == '\n') {
                    height_tiles += 1;
                } else {
                    tiles.push_back(Tile(tile_char == '#'));
                    if (height_tiles == 0) {
                        width_tiles += 1;
                    }
                }
            }
            
            width = width_tiles * TILE_SIZE;
            height = height_tiles * TILE_SIZE;
        }
        
        int width;
        int height;
        int width_tiles;
        int height_tiles;
        
        Tile & tile_at(float x, float y);
        std::vector<Tile> tiles; 
    };
    
    Map map_from_file(std::string filename);
}

