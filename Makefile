all:
	clang++ -g -std=c++11                             \
	    -I./                       	                  \
	    -I./lib/CoreCoord/include  	                  \
	    -I./lib/CoreGame/include   	                  \
	    -I./lib/CoreRandom/include 	                  \
	    -I./test_game/lib/termcolor_cpp/termcolor     \
	    ./lib/CoreCoord/src/*.cpp                     \
	    ./lib/CoreGame/src/*.cpp                      \
	    ./lib/CoreRandom/src/*.cpp                    \
	    ./test_game/lib/termcolor_cpp/termcolor/*.cpp \
	    ./src/*.cpp                                   \
	    ./test_game/*.cpp                             \
	    -o game

