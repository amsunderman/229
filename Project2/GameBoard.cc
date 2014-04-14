#include "GameBoard.hh"

/**Method that initialized gameboard using initial coordinates provided in vector format
 * @param GridDimension terrain: dimensions of gameboard
 * @param vector<pair<int, int> > * coordinates: coordinates of cells to mark in initialization
 * @param bool alive: if true marked cells will be alive and rest will be dead and vice versa
 * @ret int: 0 = operation success; -1 = failure
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
int GameBoard::init(GridDimension terrain, vector<pair<int, int> > * coordinates, bool alive)
{
    // set offsets
    x_offset = -(terrain.getXLow());
    y_offset = -(terrain.getYLow());

    // set size of each dimension
    x_size = (terrain.getXHigh() - terrain.getXLow() + 1);
    y_size = (terrain.getYHigh() - terrain.getYLow() + 1);

    // make game grid (all cells initialized to the opposite of provided coordinates)
    for(int i = 0; i < y_size; i++)
    {
        vector<Cell> row;
        for(int j = 0; j < x_size; j++)
        {
            Cell cell(!alive);
            if(!alive)
                population++;
            row.push_back(cell);
        }
        grid.push_back(row);
    }

    // initiate cells given by coordinates
    for(int i = 0; i < coordinates->size(); i++)
    {
        if(alive)
        {
            grid[(coordinates->at(i).second + y_offset)][(coordinates->at(i).first + x_offset)].setAlive();
            population++;
        }
        else
        {
            grid[(coordinates->at(i).second + y_offset)][(coordinates->at(i).first + x_offset)].setDead();
            population--;
        }
    }

    // initialize cell neighbors
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            // set top left
            if((i-1) < 0 && (j-1) < 0)
            {
                grid[i][j].addNeighbor(&(grid[y_size-1][x_size-1]));
            }
            else if((i-1) < 0)
            {
                grid[i][j].addNeighbor(&(grid[y_size-1][j-1]));
            }
            else if((j-1) < 0)
            {
                grid[i][j].addNeighbor(&(grid[i-1][x_size-1]));
            }
            else
            {
                grid[i][j].addNeighbor(&(grid[i-1][j-1]));
            }

            // set top
            if((i-1) < 0)
            {
                grid[i][j].addNeighbor(&(grid[y_size-1][j]));
            }
            else
            {
                grid[i][j].addNeighbor(&(grid[i-1][j]));
            }

            // set top right
            if((i-1) < 0 && (j+1) == x_size)
            {
                grid[i][j].addNeighbor(&(grid[y_size-1][0]));
            }
            else if((i-1) < 0)
            {
                grid[i][j].addNeighbor(&(grid[y_size-1][j+1]));
            }
            else if((j+1) == x_size)
            {
                grid[i][j].addNeighbor(&(grid[i-1][0]));
            }
            else
            {
                grid[i][j].addNeighbor(&(grid[i-1][j+1]));
            }

            // set right
            if((j+1) == x_size)
            {
                grid[i][j].addNeighbor(&(grid[i][0]));
            }
            else
            {
                grid[i][j].addNeighbor(&(grid[i][j+1]));
            }

            // set bottom right
            if((i+1) == y_size && (j+1) == x_size)
            {
                grid[i][j].addNeighbor(&(grid[0][0]));
            }
            else if((i+1) == y_size)
            {
                grid[i][j].addNeighbor(&(grid[0][j+1]));
            }
            else if((j+1) == x_size)
            {
                grid[i][j].addNeighbor(&(grid[i+1][0]));
            }
            else
            {
                grid[i][j].addNeighbor(&(grid[i+1][j+1]));
            }

            // set bottom
            if((i+1) == y_size)
            {
                grid[i][j].addNeighbor(&(grid[0][j]));
            }
            else
            {
                grid[i][j].addNeighbor(&(grid[i+1][j]));
            }

            // set bottom left
            if((i+1) == y_size && (j-1) < 0)
            {
                grid[i][j].addNeighbor(&(grid[0][x_size-1]));
            }
            else if((i+1) == y_size)
            {
                grid[i][j].addNeighbor(&(grid[0][j-1]));
            }
            else if((j-1) < 0)
            {
                grid[i][j].addNeighbor(&(grid[i+1][x_size-1]));
            }
            else
            {
                grid[i][j].addNeighbor(&(grid[i+1][j-1]));
            }

            // set left
            if((j-1) < 0)
            {
                grid[i][j].addNeighbor(&(grid[i][x_size-1]));
            }
            else
            {
                grid[i][j].addNeighbor(&(grid[i][j-1]));
            }
        }
    }

    // return successfully
    return 0;
}

/**gets population of gameboard (number of alive cells)
 * @param none
 * @ret int: number of alive cells
 * @author Adam Sunderman
 * @modified 04/11/2014 **/
int GameBoard::getPopulation()
{
    return population;
}

/**advances to next generation and modifies cells accordingly
 * @param none
 * @ret int: 0 = operation success; -1 = failure
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
int GameBoard::advanceGen()
{
    // loop through all cells and evaluate generation
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            grid[i][j].aliveNextGen();
        }
    }

    // loop through all cells and mark with new status
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            if(grid[i][j].stayAlive() && !grid[i][j].isAlive())
            {
                grid[i][j].setAlive();
                population++;
            }
            else if(!grid[i][j].stayAlive() && grid[i][j].isAlive())
            {
                grid[i][j].setDead();
                population--;
            }
        }
    }

    return 0;
}

/**Method that gets cell at provided coordinates
 * @param int x: x coordinate of desired cell
 * @param int y: y coordinate of desired cell
 * @ret Cell: desired Cell
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
Cell GameBoard::getCell(int x, int y)
{
    return grid[y][x];
}

/**Method that returns alive cells contained in game grid
 * @param none
 * @ret vector<pair<int, int> >: vector containing alive cells
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
vector<pair<int, int> > GameBoard::getAliveCells()
{
    // vector to store alive cells and return
    vector<pair<int, int> > aliveCells;

    // loop through all cells and add alive cells to return vector
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            if(grid[i][j].isAlive())
            {
                pair<int, int> currentCell(j-x_offset, i-y_offset);
                aliveCells.push_back(currentCell);
            }
        }
    }

    // return vector
    return aliveCells;
}
