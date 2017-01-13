LIBS= -lsfml-graphics -lsfml-system -lsfml-window
FLAGS= -std=c++11 -Wall -Werror -pedantic
OBJECTS= main.cpp simulation.cpp drawing.cpp vehicle.cpp assets.cpp customer.cpp simtime.cpp package.cpp
all:
	mkdir ./bin -p
	g++ $(OBJECTS) -o ./bin/simulation.out -O3  $(FLAGS) $(LIBS)
debug:
	mkdir ./bin -p
	g++ $(OBJECTS) -o ./bin/simulation.out -O0 -g $(FLAGS) $(LIBS)
