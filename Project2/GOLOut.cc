#include "GOLOut.hh"

/**default constructor with alive as '@' and dead as '~' and all black text
 * @author Adam Sunderman
 * @modified 04/07/2014 **/
GOLOut::GOLOut()
{
    alive = '@';
    dead = '~';
    alive_rVal = alive_gVal = alive_bVal = dead_rVal = dead_gVal = dead_bVal = 0;
}

/**override method from View class to output to GOL file
 * @param GameBoard game: current game to draw to cmd line
 * @param string name: name of simulation
 * @param GridDimension terrain: terrain dimensions for output
 * @param GridDimension window: window dimensions for output
 * @ret int: 0 = operation success; -1 = failure
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
int GOLOut::draw(GameBoard game, string name, GridDimension terrain, GridDimension window)
{
    //holds alive cells
    vector<pair<int, int> > alive_coordinates = game.getAliveCells();

    // header
    cout << "#GOL output for simulation: " << name << endl << endl;
    cout << "Life =" << endl << "{" << endl;

    // name
    cout << "\t" << "Name = \"" << name << "\";" << endl << endl;

    // terrain
    cout << "\t" << "Terrain = { Xrange = " << terrain.getXLow() << ".." << terrain.getXHigh() << "; Yrange = " <<
        terrain.getYLow() << ".." << terrain.getYHigh() << ";};" << endl << endl;

    // window
    cout << "\t" << "Window = { Xrange = " << window.getXLow() << ".." << window.getXHigh() << "; Yrange = " <<
        window.getYLow() << ".." << window.getYHigh() << ";};" << endl << endl;

    // Chars
    cout << "\t" << "Chars = {" << endl << "\t\t Alive = " << (int) alive << ";\t# ASCII code for " << alive << endl
        << "\t\t Dead = " << (int) dead << ";" << "\t# ASCII code for " << dead << endl << "\t};" << endl;

    // Colors
    cout << "\t" << "Colors = {" << endl << "\t\t Alive = (" << (int) alive_rVal << ", " << (int) alive_gVal << ", "
        << (int) alive_bVal << ");" << endl << "\t\t Dead = (" << (int) dead_rVal << ", " << (int) dead_gVal << ", " <<
        (int) dead_bVal << ");" << endl << "\t};" << endl;

    if(alive_coordinates.size() == 0)
    {
        //finish
        cout << "};" << endl;

        return 0;
    }

    // Initial
    cout << "\t" << "Initial = {" << endl << "\t\t# Set coordinates of the alive cells" << endl <<
        "\t\t# Everything else is dead" << endl << "\t\tAlive = ";

    // loop through alive coordinates
    for(int i = 0; i < alive_coordinates.size(); i++)
    {
        cout << "(" << alive_coordinates.at(i).first << ", " << alive_coordinates.at(i).second << ")";
        if(i == (alive_coordinates.size() - 1))
        {
            cout << ";" << endl << "\t};" << endl;
        }
        else
        {
            cout << ", ";
            if(i % 5 == 4)
            {
                cout << endl << "\t\t";
            }
        }
    }

    //finish
    cout << "};" << endl;

    return 0;
}
