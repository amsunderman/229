#ifndef GAMEBOARD
#define GAMEBOARD

#include "Cell.hh"
#include "GridDimension.hh"

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

using namespace std;

/**GameBoard object to store the grid of cells as well as manage cell population and advancing generations
 * @author Adam Sunderman
 * @modified 04/04/2014 **/
class GameBoard
{
        private:
            vector<vector<Cell> > grid; //2d vector to store grid of Cells
            int x_offset;
            int y_offset;
            int x_size;
            int y_size;
            int population; //keeps track of population (alive cells)

        public:
            // initialize gameboard
            int init(GridDimension terrain, vector<pair<int, int> > * coordinates, bool alive);
            int getPopulation(); //returns current population
            int advanceGen(); //advances generations
            Cell getCell(int x, int y); //get cell at coordinates x, y
            vector<pair<int, int> > getAliveCells(); //gets a vector list of all alive cell coordinates
};

#endif
