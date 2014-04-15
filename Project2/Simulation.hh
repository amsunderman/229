#ifndef SIMULATION
#define SIMULATION

#include "GridDimension.hh"
#include "View.hh"
#include "CmdView.hh"
#include "GOLOut.hh"
#include "GUIOut.hh"
#include "GameBoard.hh"

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef STRING
#define STRING
#include <string>
#include <string.h>
#endif

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

#ifndef SSTREAM
#define SSTREAM
#include <sstream>
#endif

#ifndef STACK
#define STACK
#include <stack>
#endif

using namespace std;

/**Simulation object to store GOL attributes and manage interactions with other GOL objects
 * @author Adam Sunderman
 * @modified 04/12/2014 **/
class Simulation
{
    private:
        string name; //name of simulation
        string GOL_in; //file to read gol data from
        int generation; //current generation
        int startGen; //generation to start simulation at
        GridDimension terrain; //terrain dimensions
        GridDimension window; //window dimensions
        bool override_tx; //marks if we should override values from gol file
        bool override_ty;
        bool override_wx;
        bool override_wy;
        vector<pair<int, int> > * coordinates; //stores coordinates of either alive cells or dead cells
        bool alive_coordinates; //controls whether coordinates are for alive or dead cells
        View * display; //View object that manages program output
        GameBoard game; //GameBoard object that manages Cell data as well as generation switching

    public:
        Simulation(); //default constructor
        Simulation(string GOL_in, View * out, bool override_tx, bool override_ty, bool override_wx, bool override_wy,
            int txLow, int txHigh, int tyLow, int tyHigh, int wxLow, int wxHigh, int wyLow, int wyHigh, int sGen);
        ~Simulation(); //deconstructor
        int readGOLFile(); //reads in GOL file and sets simulation values
        int run(); //runs simulation to startGen
        void setName(string name); //sets name of simulation
        void setStartGen(int sGen); //sets start generation of simulation
        void setTerrain(int xLow, int xHigh, int yLow, int yHigh); //set terrain dimensions
        void setWindow(int xLow, int xHigh, int yLow, int yHigh); //set window dimensions
        string getName(); //returns name
        int getGen(); //returns current generation
};

#endif
