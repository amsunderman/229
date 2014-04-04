#ifndef SIMULATION
#define SIMULATION

#include "GridDimension.hh"
#include "View.hh"
#include "GameBoard.hh"

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

using namespace std;

/**Simulation object to store GOL attributes and manage interactions with other GOL objects
 * @author Adam Sunderman
 * @modified 04/04/2014 **/
class Simulation
{
    private:
        string name; //name of simulation
        int generation; //current generation
        int startGen; //generation to start simulation at
        GridDimension terrain; //terrain dimensions
        GridDimension window; //window dimensions
        View display; //View object that manages program output
        GameBoard game; //GameBoard object that manages Cell data as well as generation switching

    public:
        Simulation(); //default constructor
        void setName(string name); //sets name of simulation
        void setStartGen(int sGen); //sets start generation of simulation
        void setTerrain(int xLow, int xHigh, int yLow, int yHigh); //set terrain dimensions
        void setWindow(int xLow, int xHigh, int yLow, int yHigh); //set window dimensions
        string getName(); //returns name
        int getGen(); //returns current generation
        void advanceGen(); //uses game object to advance generation
        void draw(); //used View object to output gamestate
};

#endif
