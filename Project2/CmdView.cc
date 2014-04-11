#include "CmdView.hh"

/**default constructor with alive as '@' and dead as '~' and all black text
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
CmdView::CmdView()
{
    alive = '@';
    dead = '~';
    alive_rVal = alive_gVal = alive_bVal = dead_rVal = dead_gVal = dead_bVal = 0;
}

/**constructor with parameters
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
CmdView::CmdView(char givenAlive, char givenDead, unsigned char given_alive_rVal, unsigned char given_alive_gVal, 
    unsigned char given_alive_bVal, unsigned char given_dead_rVal, unsigned char given_dead_gVal,
    unsigned char given_dead_bVal)
{
    alive = givenAlive;
    dead = givenDead;
    alive_rVal = given_alive_rVal;
    alive_gVal = given_alive_gVal;
    alive_bVal = given_alive_bVal;
    dead_rVal = given_dead_rVal;
    dead_gVal = given_dead_gVal;
    dead_bVal = given_dead_bVal;
}

/**method that sets which character represents an alive cell
 * @param char givenAlive: character to represent alive cell
 * @ret void
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
void CmdView::setAliveChar(char givenAlive)
{
    alive = givenAlive;
}

/**method that sets which character represents an dead cell
 * @param char givenDead: character to represent dead cell
 * @ret void
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
void CmdView::setDeadChar(char givenDead)
{
    dead = givenDead;
}

/**method that sets the color of an alive cell
 * @param unsigned char rVal: red value for alive cell
 * @param unsigned char gVal: green value for alive cell
 * @param unsigned char bVal: blue value for alive cell
 * @ret void
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
void CmdView::setAliveColor(unsigned char rVal, unsigned char gVal, unsigned char bVal)
{
    alive_rVal = rVal;
    alive_gVal = gVal;
    alive_bVal = bVal;
}

/**method that sets the color of an alive cell
 * @param unsigned char rVal: red value for alive cell
 * @param unsigned char gVal: green value for alive cell
 * @param unsigned char bVal: blue value for alive cell
 * @ret void
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
void CmdView::setDeadColor(unsigned char rVal, unsigned char gVal, unsigned char bVal)
{
    dead_rVal = rVal;
    dead_gVal = gVal;
    dead_bVal = bVal;
}

/**method that draws gameboard to command line (override from View parent class)
 * @param GameBoard game: current game to draw to cmd line
 * @ret void
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
void CmdView::draw(GameBoard game)
{
    /*TODO*/
}
