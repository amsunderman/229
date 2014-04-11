#include "Cell.hh"

/**method used to initialize individual cell (will assign neighbors and state)
 * @param bool alive: is cell alive
 * @ret void
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
void Cell::init(bool alive)
{
    //set alive
    this->alive = alive;

    //set neighbors
    /*TODO*/
}

/**method used to set cell to alive status
 * @param void
 * @ret void
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
void Cell::setAlive()
{
    alive = true;
}

/**method used to set cell to dead status
 * @param void
 * @ret void
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
void Cell::setDead()
{
    alive = false;
}

/**method used to find out if cell is alive
 * @param void
 * @ret bool: true if alive, false if dead
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
bool Cell::isAlive()
{
    return alive;
}

/**method that evaluates cell status for next gen
 * @param void
 * @ret bool: true if cell wil be alive next gen, false if dead
 * @author Adam Sunderman
 * @modified 04/07/2014**/
bool Cell::aliveNextGen()
{
    /*TODO*/
    return false;
}
