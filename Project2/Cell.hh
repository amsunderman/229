#ifndef CELL
#define CELL

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

using namespace std;

/**Cell object to store and modify the Cell's state as well as evaluate the Cell's next state
 * @author Adam Sunderman
 * @modified 04/04/2014 **/
class Cell
{
    private:
        bool alive; //boolean to store cell's state
        bool nextState; //boolean to stare cell's state next gen
        vector<Cell *> neighbors; //list of neighbors for cell
    public:
        Cell(); //default constructor
        Cell(bool alive); //initilazation constructor
        void addNeighbor(Cell * neighbor); //adds neighbor to vector
        void setAlive(); //mark cell as alive
        void setDead(); //mark cell as dead
        bool isAlive(); //return alive status
        bool stayAlive(); //return if cell is alive next gen
        bool aliveNextGen(); //evaluate if cell will be alive next gen
};

#endif
