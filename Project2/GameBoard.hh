#ifndef GAMEBOARD
#define GAMEBOARD

#include "Cell.hh"

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

using namespace std;

class GameBoard
{
        private:
            vector<vector<Cell> > grid;
            int population;
        public:
            void advanceGen();
};  

#endif
