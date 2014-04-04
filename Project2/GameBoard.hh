#ifndef GAMEBOARD
#define GAMEBOARD

#include "Cell.hh"

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
            int population; //keeps track of population (alive cells)
        public:
            int getPopulation(); //returns current population
            void advanceGen(); //advances generations
};  

#endif
