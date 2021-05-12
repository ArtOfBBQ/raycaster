#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../modules/map.h"

TEST_CASE("can init a map from file") {

    map::Map my_map = map::map_from_file("../data/mymap.rcm");

    REQUIRE(my_map.width_tiles == 16);
    REQUIRE(my_map.height_tiles == 13);
}

TEST_CASE("can find tile 1 from coordinates 1/2") {

    map::Map my_map = map::map_from_file("../data/mymap.rcm");

    map::Tile & origin = my_map.tile_at(10.0f, 10.0f);

    REQUIRE(&my_map.tiles.at(0) == &origin);
    REQUIRE(&my_map.tiles.at(1) != &origin);
    REQUIRE(&my_map.tiles.at(2) != &origin);
    REQUIRE(&my_map.tiles.at(3) != &origin);
    REQUIRE(&my_map.tiles.at(4) != &origin);
    REQUIRE(&my_map.tiles.at(5) != &origin);
}

TEST_CASE("can find tile 1 from coordinates 2/2") {

    map::Map my_map = map::map_from_file("../data/mymap.rcm");

    map::Tile & origin = my_map.tile_at(0.3f, 0.7f);

    REQUIRE(&my_map.tiles.at(0) == &origin);
    REQUIRE(&my_map.tiles.at(1) != &origin);
    REQUIRE(&my_map.tiles.at(2) != &origin);
    REQUIRE(&my_map.tiles.at(3) != &origin);
    REQUIRE(&my_map.tiles.at(4) != &origin);
    REQUIRE(&my_map.tiles.at(5) != &origin);
}

TEST_CASE("can find tile 2 from coordinates") {

    map::Map my_map = map::map_from_file("../data/mymap.rcm");

    map::Tile & origin = my_map.tile_at(40, 0);

    REQUIRE(&my_map.tiles.at(0) != &origin);
    REQUIRE(&my_map.tiles.at(1) == &origin);
}

TEST_CASE("can find tile 16 from coordinates") {

    map::Map my_map = map::map_from_file("../data/mymap.rcm");

    map::Tile & origin = my_map.tile_at(1, 40);
    
    REQUIRE(&my_map.tiles.at(15) != &origin);
    REQUIRE(&my_map.tiles.at(16) == &origin);
    REQUIRE(&my_map.tiles.at(17) != &origin);
}

TEST_CASE("can find tile 17 from coordinates") {

    map::Map my_map = map::map_from_file("../data/mymap.rcm");

    map::Tile & origin = my_map.tile_at(41, 40);
    
    REQUIRE(&my_map.tiles.at(16) != &origin);
    REQUIRE(&my_map.tiles.at(17) == &origin);
    REQUIRE(&my_map.tiles.at(18) != &origin);
}

