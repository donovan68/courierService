#include <iostream>
#include <random>
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    Simulation sim(600, 600);
    sim.Init();
    while(sim.IsRunning())
    {
        sim.Step();
    }


    return 0;
}
