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
    setTerrain(0, DEFAULT_TERRAIN_WIDTH, 0, DEFAULT_TERRAIN_HEIGHT);
    setWindow(0, DEFAULT_WINDOW_WIDTH, 0, DEFAULT_WINDOW_HEIGHT);
}

void Simulation::setName(string givenName)
{
    name = givenName;
}

void Simulation::setStartGen(int sGen)
{
    startGen = sGen;
}

void Simulation::setTerrain(int xLow, int xHigh, int yLow, int yHigh)
{
    terrain.setXLow(xLow);
    terrain.setXHigh(xHigh);
    terrain.setYLow(yLow);
    terrain.setYHigh(yHigh);
}

void Simulation::setWindow(int xLow, int xHigh, int yLow, int yHigh)
{
    window.setXLow(xLow);
    window.setXHigh(xHigh);
    window.setYLow(yLow);
    window.setYHigh(yHigh);
}

string Simulation::getName()
{
    return name;
}

int Simulation::getGen()
{
    return generation;
}

void Simulation::advanceGen()
{
    /*TODO*/
}

void Simulation::draw()
{
    /*TODO*/
}
