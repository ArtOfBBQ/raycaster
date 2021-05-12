#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../modules/game.h"


TEST_CASE("We can keep an angle between 0 and 6.28 radians") {
    
    std::string map_filename = "../data/mymap.rcm"; 
    game::GameState gs(map_filename);
    
    float angle = 0.24f;
    REQUIRE(game::wrap_radians_angle(angle) == angle);
    
    angle = -0.20f;
    bool check = game::wrap_radians_angle(angle) >= 6.07f
        && game::wrap_radians_angle(angle) <= 6.09f;
    REQUIRE(check);

    angle = -1.20f;
    check = game::wrap_radians_angle(angle) >= 5.06
        && game::wrap_radians_angle(angle) <= 5.09f;
    REQUIRE(check);

    angle = 8.28f;
    check = game::wrap_radians_angle(angle) >= 1.59f
        && game::wrap_radians_angle(angle) <= 2.01f;
    REQUIRE(check);

    angle = 108.48;
    check = game::wrap_radians_angle(angle) >= 1.71f
        && game::wrap_radians_angle(angle) <= 1.73f;
    REQUIRE(check);
}

TEST_CASE("thrust forward changes velocity") {
    
    std::string map_filename = "../data/mymap.rcm"; 
    game::GameState gs(map_filename);
    
    REQUIRE(gs.player.velocity_x == 0);
    REQUIRE(gs.player.velocity_y == 0);
    REQUIRE(gs.player.angle == 2.5f);
    
    gs.player.thrust(0.01f);
   
    bool vel_x_check = gs.player.velocity_x > 2.39f
        && gs.player.velocity_x < 2.40f;
    REQUIRE(vel_x_check);
    
    bool vel_y_check = gs.player.velocity_y > 3.20f
        && gs.player.velocity_y < 3.21f;
    REQUIRE(vel_y_check);
}

TEST_CASE("update column heights") {
   
    std::string map_filename = "../data/mymap.rcm"; 
    game::GameState gs(map_filename);
  
    REQUIRE(gs.column_heights[0] == 20.0f);
    REQUIRE(gs.column_heights[40] == 60.0f);
    
    gs.update_column_heights();
    
    REQUIRE(gs.column_heights[0] == 399.99997f);
    REQUIRE(gs.column_heights[40] == 520.00006f);
}

TEST_CASE("update column heights 2") {
    
    std::string map_filename = "../data/mymap.rcm"; 
    game::GameState gs(map_filename);
    
    REQUIRE(gs.column_heights[0] == 20.0f);
    REQUIRE(gs.column_heights[40] == 60.0f);
    REQUIRE(gs.map.width_tiles == 16);
    REQUIRE(gs.map.height_tiles == 13);
    REQUIRE(gs.map.width == 640);
    REQUIRE(gs.map.height == 520);
    
    gs.player.angle = 6.1; 
    gs.update_column_heights();
    
    REQUIRE(gs.column_heights[0] == 80.00001f);
    REQUIRE(gs.column_heights[40] == 80.0f);
}

TEST_CASE("On one angle, the rightmost column is bigger") {
    
    std::string map_filename = "../data/mymap.rcm"; 
    game::GameState gs(map_filename);
    
    REQUIRE(gs.column_heights[0] == 20.0f);
    REQUIRE(gs.column_heights[40] == 60.0f);
    
    gs.player.angle = 1.57f; 
    gs.update_column_heights();
    
    REQUIRE(gs.column_heights[0] == 159.99998f);
    REQUIRE(gs.column_heights[40] == 240.0f);
}

