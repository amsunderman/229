#ifndef VIEW
#define VIEW

#include "GameBoard.hh"
#include "GridDimension.hh"

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef UTILITY
#define UTILITY
#include <utility>
#endif

/**interface for View objects. All objects that extend View will implement a draw() method for correct GOL output
 * @author Adam Sunderman
 * @modified 04/12/2014 **/
class View
{
    protected:
        char alive; //char to represent alive cells
        char dead; //char to represent dead cells
        unsigned char alive_rVal; //rgb values for alive cells
        unsigned char alive_gVal;
        unsigned char alive_bVal;
        unsigned char dead_rVal; //rgb values for dead cells
        unsigned char dead_gVal;
        unsigned char dead_bVal;

    public:
        View(); //default constructor
        View(char givenAlive, char givenDead, unsigned char given_alive_rVal, unsigned char given_alive_gVal,
            unsigned char given_alive_bVal, unsigned char given_dead_rVal, unsigned char given_dead_gVal,
            unsigned char given_dead_bVal); //initialization constructor
        virtual int draw(GameBoard game, string name, GridDimension terrain, GridDimension window); //output (virtual)
        void setAliveChar(char givenAlive); //set the character used to represent alive cell
        void setDeadChar(char givenDead); //set the character used to represent a dead cell
        void setAliveColor(unsigned char rVal, unsigned char gVal, unsigned char bVal); //set color for alive
        void setDeadColor(unsigned char rVal, unsigned char gVal, unsigned char bVal); //set color for dead
        char getAliveChar(); //get character used to represent alive cell
        char getDeadChar(); //get character used to represent dead cell
};

#endif
