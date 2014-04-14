#include "Cell.hh"

/**Default constructor
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
Cell::Cell()
{
    alive = false;
    nextState = false;
}

/**Initialization constructor
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
Cell::Cell(bool alive)
{
    alive = alive;
    nextState = false;
}

/**Method used to add neighbor to cells neighbors vector
 * @param Cell * neighbor: pointer to cell to add to vector
 * @ret void
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
void Cell::addNeighbor(Cell * neighbor)
{
    // loop through neighbors and check to see if it already exists
    for(int i = 0; i < neighbors.size(); i++)
    {
        if(neighbors[i] == neighbor)
        {
            return;
        }
    }

    // if neighbor is new add it to neighbors list
    neighbors.push_back(neighbor);
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

/**Method used to see if cell will stay alive next gen
 * @param void
 * @ret bool: true if alive next gen false otherwise
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
bool Cell::stayAlive()
{
    return nextState;
}

/**method that evaluates cell status for next gen
 * @param void
 * @ret bool: true if cell wil be alive next gen, false if dead
 * @author Adam Sunderman
 * @modified 04/07/2014**/
bool Cell::aliveNextGen()
{
    // keep track of alive neighbors
    int alive_neighbors = 0;

    // loop through neighbors and count them
    for(int i = 0; i < neighbors.size(); i++)
    {
        if(neighbors.at(i)->isAlive())
        {
            alive_neighbors++;
        }
    }

    // if dead follow dead rules
    if(!alive)
    {
        if(alive_neighbors == 3)
        {
            nextState = true;
            return true;
        }
        else
        {
            nextState = false;
            return false;
        }
    }
    // if alive follow alive rules
    else
    {
        if(alive_neighbors == 2 || alive_neighbors == 3)
        {
            nextState = true;
            return true;
        }
        else
        {
            nextState = false;
            return false;
        }
    }

    // can't get here
    return false;
}
