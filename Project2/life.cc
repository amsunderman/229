#include "Simulation.hh"

using namespace std;

// function declaration to read terrain and window dimensions from command line switches
int read_dimension(string argument, int * low, int * high);

/**Executable program that takes in a GOL file from either a cmd line argument or stdin and then runs a GOL simulation
 * to specified generation and outputs data according to provided command line switches. compile with "-D GUI" to have
 * executable integrate with QT.
 * @param inputGOLFile: file to read game of life data from.
 * @ret int: 0 = execution success -1 = failure (with data printed to stderr)
 * @author Adam Sunderman
 * @modified 04/13/14**/
int main(int argc, char ** argv)
{
    // stores name of GOL file
    string gol_file_name = "";

    // stores current command line argument
    string current_argument = "";

    // integer that stores generation that will simulation will end at (default 0)
    int generation = 0;

    // boolean that marks if we received a GOL file. If not we will read from stdin
    bool gol_provided = false;

    // boolean that marks if we are outputting a command line visual (outputs GOL file if false)
    bool cmd_visual = false;

    // booleans that store which grid dimensions to override gol file contents
    bool override_tx = false, override_ty = false, override_wx = false, override_wy = false;

    // integers that store terrain and window dimensions
    int terrain_xl = 0, terrain_xh = 0, terrain_yl = 0, terrain_yh = 0, window_xl = 0, window_xh = 0, window_yl = 0,
        window_yh = 0;

    // stores pixel size for gui output
    int pixelSize = 10;

    // simulation object to manage gol
    Simulation * sim;

    // view object to manage output
    View * view;

    // parse command line switches and arguments
    for(int i = 1; i < argc; i++)
    {
        // are we on a command line switch?
        if(argv[i][0] == '-')
        {
            // parse command line switches
            current_argument = argv[i];

            // file command line switch (only for life)
            #ifndef GUI
            if(current_argument == "-f")
            {
                cmd_visual = false;
                continue;
            }

            // visual command line switch (only for life)
            if(current_argument == "-v")
            {
                cmd_visual = true;
                continue;
            }
            #endif

            // pixel size switch (only for lifegui)
            #ifdef GUI
            if(current_argument == "-s")
            {
                // used to check type of next argument. should be an integer
                istringstream * argument_type_check = new istringstream(argv[++i]);

                // check to see if next argument is a valid integer (new generation value)
                if(!(*argument_type_check >> pixelSize))
                {
                    cerr << "error: usage of command line switch -s: \"-s n\" where n is an integer" << endl;
                    cerr << "exiting program" << endl;
                    return -1;
                }

                if(pixelSize < 4)
                {
                    pixelSize = 10;
                }

                delete argument_type_check;
                continue;
            }
            #endif

            // generation command line switch
            if(current_argument == "-g")
            {
                // used to check type of next argument. should be an integer
                istringstream * argument_type_check = new istringstream(argv[++i]);

                // check to see if next argument is a valid integer (new generation value)
                if(!(*argument_type_check >> generation))
                {
                    cerr << "error: usage of command line switch -g: \"-g n\" where n is an integer" << endl;
                    cerr << "exiting program" << endl;
                    return -1;
                }

                delete argument_type_check;
                continue;
            }

            // help command line switch
            if(current_argument == "-h")
            {
                cout << endl << "life program: simulates the game of life with the following rules:" << endl;
                cout << "1: if cell is alive in generation i, then: " << endl;
                cout << "\t(a) loneliness rule: if there are fewer then two alive neighbors, cell will be " <<
                    "dead in generation i + 1" << endl;
                cout << "\t(b) if there are two or three alive neighbors, cell will be alive in generation i + 1"
                    << endl;
                cout << "\t(c) Over-Population Rule: If there are more than three alive neighbors, cell will " <<
                    "be dead in generation i + 1" << endl;
                cout << "2: if cell is dead in generation i, then:" << endl;
                cout << "\t(a) Reproduction Rule: if there are exactly three alive neighbors, cell will be alive " <<
                    "generation i + 1" << endl;
                cout << "\t(b) If any other number of alive neighbors exist, cell will remain dead in generation " <<
                    "i + 1" << endl << endl;
                return 0;
            }

            // terrain overrides
            if(current_argument == "-tx")
            {
                override_tx = true;
                if(read_dimension(argv[++i], &terrain_xl, &terrain_xh))
                    return -1;
                continue;
            }

            if(current_argument == "-ty")
            {
                override_ty = true;
                if(read_dimension(argv[++i], &terrain_yl, &terrain_yh))
                    return -1;
                continue;
            }

            if(current_argument == "-wx")
            {
                override_wx = true;
                if(read_dimension(argv[++i], &window_xl, &window_xh))
                    return -1;
                continue;
            }

            if(current_argument == "-wy")
            {
                override_wy = true;
                if(read_dimension(argv[++i], &window_yl, &window_yh))
                    return -1;
                continue;
            }

            // invalid command line switch
            else
            {
                cerr << "argument "<< i << " \"" << current_argument << "\"" << " is an invalid command line switch"
                    << endl << endl;
                cerr << "valid command line switches:" << endl;
                cerr << "-f: Output will be in the form of a gol file" << endl;
                cerr << "-g n: n specifies the desired output generation number" << endl;
                cerr << "-h: displays program help screen" << endl;
                cerr << "-tx L..H: override terrain x range L is low and H is high" << endl;
                cerr << "-ty L..H: override terrain y range L is low and H is high" << endl;
                cerr << "-v: output will be an ascii display on the command line" << endl;
                cerr << "-wx L..H: override window x range L is low and H is high" << endl;
                cerr << "-wy L..H: override window y range L is low and H is high" << endl << endl;
                cerr << "exiting program" << endl;
                return -1;
            }
        }

        //if not a command line switch it must be a gol file
        else
        {
            gol_provided = true;
            gol_file_name = argv[i];
        }
    }

    // determine view type based of of executable and command line switches
    #ifndef GUI
    if(cmd_visual)
        view = new CmdView();
    else
        view = new GOLOut();
    #else
    view = new GUIOut(pixelSize);
    #endif

    // if gol was provided we use it else simulation will read from stdin
    if(gol_provided)
    {
        sim = new Simulation(gol_file_name, view, override_tx, override_ty, override_wx, override_wy, terrain_xl,
            terrain_xh, terrain_yl, terrain_yh, window_xl, window_xh, window_yl, window_yh, generation);
    }
    else
    {
        sim = new Simulation("stdin", view, override_tx, override_ty, override_wx, override_wy, terrain_xl, terrain_xh,
            terrain_yl, terrain_yh, window_xl, window_xh, window_yl, window_yh, generation);
    }

    // use Simulation to read in GOL file
    if(sim->readGOLFile())
    {
        cerr << "error encountered in Simulation::readGOLFile" << endl;
        cerr << "exiting program" << endl;
        return -1;
    }

    // run simulation
    if(sim->run())
    {
        cerr << "error encountered in Simulation::run()" << endl;
        cerr << "exiting program" << endl;
    }

    delete sim;
    delete view;

    /*return successfully*/
    return 0;
}

/**function declaration to read terrain and window dimensions from command line switches
 * @param string argument: L..H
 * @param int * low: low dimension to read in
 * @param int * high: high dimension to read in
 * @ret int: 0 = operation success -1 = failure
 * @author Adam Sunderman
 * @modified 04/12/14 **/
int read_dimension(string argument, int * low, int * high)
{
    // used to parse argument
    istringstream argument_type_check(argument);

    // character checker
    char check;

    // if we can't get x low exit program
    if(!(argument_type_check >> *low))
    {
        cerr << "error: bad dimension command line argument format" << endl;
        cerr << "exiting program" << endl;
        return -1;
    }

    // filter dots
    for(int j = 0; j < 2; j++)
    {
        argument_type_check >> check;

        if(check != '.')
        {
            cerr << "error: usage of command line switch -tx: \"-tx L..H\" where L is terrain x low " <<
            cerr << "exiting program" << endl;
            return -1;
        }
    }

    // if we can't get x high exit program
    if(!(argument_type_check >> *high))
    {
        cerr << "error: bad dimension command line argument format" << endl;
        cerr << "exiting program" << endl;
        return -1;
    }

    // if the string has more data it doesn't follow valid format
    if(argument_type_check.peek() >= 0)
    {
        cerr << "error: bad dimension command line argument format" << endl;
        cerr << "exiting program" << endl;
        return -1;
    }

    //check that dimension is > 0 (from high to low)
    if((*high - *low) < 1)
    {
        cerr << "error: bad dimension command line argument format" << endl;
        cerr << "exiting program" << endl;
        return -1;
    }

    // return successfully
    return 0;
}
