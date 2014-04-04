#ifndef CMDVIS
#define CMDVIS

#include "View.hh"

/**View that outputs to command line (extension of View object)
 * @author Adam Sunderman
 * @modified 04/04/2014 **/
class CmdView:public View
{
    private:
        char alive; //char to represent alive cells
        char dead; //char to represent dead cells
        unsigned char alive_rVal; //rgb values for alive cells
        unsigned char alive_gVal;
        unsigned char alive_bVal;
        unsigned char dead_rVal; //rgb values for dead cells
        unsigned char dead_gVal;
        unsigned char dead_bVal;
    public:
        CmdView(); //default constructor
        CmdView(char givenAlive, char givenDead, unsigned char given_alive_rVal, unsigned char given_alive_gVal, 
            unsigned char given_alive_bVal, unsigned char given_dead_rVal, unsigned char given_dead_gVal, 
            unsigned char given_dead_bVal); //initialization constructor
        void setAliveChar(char givenAlive); //set the character used to represent alive cell
        void setDeadChar(char givenDead); //set the character used to represent a dead cell
        void setAliveColor(unsigned char rVal, unsigned char gVal, unsigned char bVal); //set color for alive cells
        void setDeadColor(unsigned char rVal, unsigned char gVal, unsigned char bVal); //set color for dead cells
        void draw(); //output cell grid to stdout
};

#endif
