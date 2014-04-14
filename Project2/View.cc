#include "View.hh"

/**default constructor with alive as '@' and dead as '~' and all black text
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
View::View()
{
    alive = '@';
    dead = '~';
    alive_rVal = alive_gVal = alive_bVal = dead_rVal = dead_gVal = dead_bVal = 0;
}

/**constructor with parameters
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
View::View(char givenAlive, char givenDead, unsigned char given_alive_rVal, unsigned char given_alive_gVal,
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
void View::setAliveChar(char givenAlive)
{
    alive = givenAlive;
}

/**method that sets which character represents an dead cell
 * @param char givenDead: character to represent dead cell
 * @ret void
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
void View::setDeadChar(char givenDead)
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
void View::setAliveColor(unsigned char rVal, unsigned char gVal, unsigned char bVal)
{
    alive_rVal = rVal;
    alive_gVal = gVal;
    alive_bVal = bVal;
}

/**method that sets the color of an dead cell
 * @param unsigned char rVal: red value for dead cell
 * @param unsigned char gVal: green value for dead cell
 * @param unsigned char bVal: blue value for dead cell
 * @ret void
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
void View::setDeadColor(unsigned char rVal, unsigned char gVal, unsigned char bVal)
{
    dead_rVal = rVal;
    dead_gVal = gVal;
    dead_bVal = bVal;
}

/**method that gets the color of alive cell
 * @param none
 * @ret char: character used to rep alive cell
 * @author Adam Sunderman
 * @modified 04/12/2014 **/
 char View::getAliveChar()
 {
    return alive;
 }

 /**method that gets the color of dead cell
 * @param none
 * @ret char: character used to rep dead cell
 * @author Adam Sunderman
 * @modified 04/12/2014 **/
 char View::getDeadChar()
 {
    return dead;
 }

/**virtual draw method
 * @author Adam Sunderman
 * @modified 04/11/2014 **/
int View::draw(GameBoard game, string name, GridDimension terrain, GridDimension window)
{
    cout << "GENERIC DRAW: oops this programs inner-polymorphism seems to not be very polymorphic" << endl;
    return -1;
}
