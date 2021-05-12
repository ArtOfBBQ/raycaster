#include "map.h"
#include <iostream>

namespace map {
    
    Map map_from_file(std::string filename) {
        
        std::ifstream myfile(filename);
        std::stringstream buffer;
        buffer << myfile.rdbuf();
        
        return Map(buffer);
    }
    
    Tile & Map::tile_at(float x, float y) {
        
        int tile_found = (int)(x / TILE_SIZE)
                + ((int)(y / TILE_SIZE) * width_tiles);
        
        if (tile_found < 0 || tile_found >= tiles.size()) {
            std::cout
                << "error! tile_found: " << tile_found
                << " for [" << x << "," << y << "] "
                << " map width: " << width
                << ", map height: " << height
                << std::endl;
            assert(1 == 2);
        }
        
        return tiles.at(tile_found);
    }
}

