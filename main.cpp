#include <iostream>
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello Cruel World!" << endl;
    Simulation sim(600, 600);
    sim.Init();
    while(sim.IsRunning())
    {
        sim.Step();
    }


    return 0;
}
