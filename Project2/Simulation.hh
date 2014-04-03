#ifndef SIMULATION
#define SIMULATION

#include "GridDimension.hh"

#ifndef STRING
#define STRING
#include <string>
#endif

using namespace std;

class Simulation
{
    private:
        string name;
        int generation;
        int startGen;
        GridDimension terrain;
        GridDimension window;

    public:
        Simulation();
        void setName(string name);
        void setGen(int gen);
        void setStartGen(int sGen);
        void setTerrain(int xLow, int xHigh, int yLow, int yHigh);
        void setWindow(int xLow, int xHigh, int yLow, int yHigh);
        string getName();
        int getGen();
        int getStartGen();
};

#endif
