#include "Simulation.hh"

#define DEFAULT_TERRAIN_WIDTH 10
#define DEFAULT_TERRAIN_HEIGHT 10
#define DEFAULT_WINDOW_WIDTH 10
#define DEFAULT_WINDOW_HEIGHT 10

using namespace std;

Simulation::Simulation()
{
    name = "game of life";
    generation = 0;
    startGen = 0;
}

void Simulation::setName(string givenName)
{
    name = givenName;
}

void Simulation::setGen(int gen)
{
    generation = gen;
}

void Simulation::setStartGen(int sGen)
{
    startGen = sGen;
}

string Simulation::getName()
{
    return name;
}

int Simulation::getGen()
{
    return generation;
}

int Simulation::getStartGen()
{
    return startGen;
}
