#ifndef CELL
#define CELL

#ifndef LIST
#define LIST
#include <list>
#endif

using namespace std;

class Cell
{
    private:
        bool alive;
        bool nextState;
        list<Cell> neighbors;
    public:
        void init();
        void setAlive();
        void setDead();
        bool isAlive();
        bool aliveNextGen();
};

#endif
