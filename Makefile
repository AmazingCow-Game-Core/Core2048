all:
	clang++ -g -std=c++11          \
	    -I./                       \
	    -I./lib/CoreCoord/include  \
	    -I./lib/CoreGame/include   \
	    -I./lib/CoreRandom/include \
	    -I./lib/termcolor          \
	    ./lib/CoreCoord/src/*.cpp  \
	    ./lib/CoreGame/src/*.cpp   \
	    ./lib/CoreRandom/src/*.cpp \
	    ./lib/termcolor/*.cpp      \
	    ./src/*.cpp                \
	    ./test_game/*.cpp          \
	    -o game

