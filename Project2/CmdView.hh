#ifndef CMDVIS
#define CMDVIS

#include "View.hh"

/**View that outputs to command line (extension of View object)
 * @author Adam Sunderman
 * @modified 04/04/2014 **/
class CmdView:public View
{
    public:
        CmdView(); //default constructor
        CmdView(char givenAlive, char givenDead, unsigned char given_alive_rVal, unsigned char given_alive_gVal,
            unsigned char given_alive_bVal, unsigned char given_dead_rVal, unsigned char given_dead_gVal,
            unsigned char given_dead_bVal); //initialization constructor
        int draw(GameBoard game, string name, GridDimension terrain, GridDimension window); //output cell grid
};

#endif
