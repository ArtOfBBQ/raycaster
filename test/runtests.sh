# g++ test-map.cpp catch.hpp ../modules/map.h ../modules/map.cpp -std=c++17
g++ test-game.cpp catch.hpp ../modules/map.h ../modules/map.cpp ../modules/game.h ../modules/game.cpp -std=c++17
./a.out
rm ./a.out

