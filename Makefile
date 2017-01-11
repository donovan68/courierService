all:
	g++ main.cpp -o simulation.out -O3 -Wall -Werror -pedantic 
debug:
	g++ main.cpp -o simulation.out -O0 -g -Wall -Werror -pedantic 
