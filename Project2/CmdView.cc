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

/**method that draws gameboard to command line (override from View parent class)
 * @param GameBoard game: current game to draw to cmd line
 * @param string name: name of simulation
 * @param GridDimension terrain: terrain dimensions for output
 * @param GridDimension window: window dimensions for output
 * @ret int: 0 = operation success; -1 = failure
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
int CmdView::draw(GameBoard game, string name, GridDimension terrain, GridDimension window)
{
    int x_size = (window.getXHigh() - window.getXLow() + 1);
    int y_size = (window.getYHigh() - window.getYLow() + 1);

    for(int i = y_size - 1; i > -1; i--)
    {
        for(int j = 0; j < x_size; j++)
        {
            if(game.getCell(j, i).isAlive())
                cout << alive;
            else
                cout << dead;
        }
        cout << endl;
    }

    return 0;
}
