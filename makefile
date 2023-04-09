all: conway.cpp grid.cpp grid.hpp
	g++ conway.cpp grid.cpp -o conway -lncurses -g

run:
	./conway
