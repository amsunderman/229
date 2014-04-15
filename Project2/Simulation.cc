#include "Simulation.hh"

#define DEFAULT_TERRAIN_WIDTH 10
#define DEFAULT_TERRAIN_HEIGHT 10
#define DEFAULT_WINDOW_WIDTH 10
#define DEFAULT_WINDOW_HEIGHT 10

using namespace std;

/**Default constructor
 * @author Adam Sunderman
 * @modified 04/13/2014**/
Simulation::Simulation()
{
    name = "game of life";
    generation = 0;
    startGen = 0;
    coordinates = new vector<pair<int, int> >();
    alive_coordinates = true;
    setTerrain(0, DEFAULT_TERRAIN_WIDTH, 0, DEFAULT_TERRAIN_HEIGHT);
    setWindow(0, DEFAULT_WINDOW_WIDTH, 0, DEFAULT_WINDOW_HEIGHT);
}

/**Initialization Constructor
 * @author Adam Sunderman
 * @modified 04/13/2014**/
Simulation::Simulation(string GOL_in, View * out, bool override_tx, bool override_ty, bool override_wx,
    bool override_wy, int txLow, int txHigh, int tyLow, int tyHigh, int wxLow, int wxHigh, int wyLow, int wyHigh,
    int sGen)
{
    name = "game of life";
    generation = 0;
    startGen = sGen;
    coordinates = new vector<pair<int, int> >();
    alive_coordinates = true;
    if(override_tx)
    {
        terrain.setXLow(txLow);
        terrain.setXHigh(txHigh);
    }
    if(override_ty)
    {
        terrain.setYLow(tyLow);
        terrain.setYHigh(tyHigh);
    }
    if(override_wx)
    {
        window.setXLow(wxLow);
        window.setXHigh(wxHigh);
    }
    if(override_wy)
    {
        window.setYLow(wxLow);
        window.setYHigh(wxHigh);
    }
    this->GOL_in = GOL_in;
    this->override_tx = override_tx;
    this->override_ty = override_ty;
    this->override_wx = override_wx;
    this->override_wy = override_wy;
    display = out;
}

Simulation::~Simulation()
{
    delete coordinates;
}

/**Method used to read in GOL file.
 * @param void
 * @ret int: 0 = operation success; -1 = failure
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
int Simulation::readGOLFile()
{
    // take in gol in
    ifstream * fin = new ifstream(GOL_in.c_str());

    // temp file to hold gol file with spaces stripped
    ofstream * fout = new ofstream("gol_spaces_stripped.gol");

    // holds current word in fin
    string s;

    // hods current line from fin
    string line;

    // marked true if line isn't empty
    bool line_has_content = false;

    // boolean that tracks if we are in quotation marks (where we will keep spaces)
    bool in_quotes = false;

    // if GOL_in is marked as std in then read from cin
    if(GOL_in == "stdin")
    {
        while(getline(cin, line))
        {
            istringstream * current_line = new istringstream(line);

            while( *current_line >> s ) {
                if((size_t) s.find("\"") != std::string::npos)
                    in_quotes = !in_quotes;
                line_has_content = true;
                *fout << s;
                if(in_quotes)
                    *fout << " "; // if we are in quotes then keep spaces
            }

            if(line_has_content)
                *fout << endl;

            delete current_line;
            line_has_content = false;
        }
    }

    // else read from provided argument
    else
    {
        // get first line from fin
        getline(*fin, line);

        // go through file and strip spaces
        while(!fin->eof())
        {
            istringstream * current_line = new istringstream(line);

            while( *current_line >> s ) {
                if((size_t) s.find("\"") != std::string::npos)
                    in_quotes = !in_quotes;
                line_has_content = true;
                *fout << s;
                if(in_quotes)
                    *fout << " "; // if we are in quotes then keep spaces
            }

            if(line_has_content)
                *fout << endl;

            delete current_line;
            line_has_content = false;
            getline(*fin, line);
        }
    }

    // clear fstream objects to start actual parsing
    delete fin;
    delete fout;

    // take in temp stripped spaces file
    fin = new ifstream("gol_spaces_stripped.gol");

    // stack to store which object we are working with
    stack <string> layer;

    // character index for line
    int c_index = 0;

    // boolean marks if life object has been acknowledged
    bool started = false;

    // marks ready to push something to stack
    bool layer_ready = false;

    // marks if we are dealing with alive cells
    bool alive = false;

    // marks if we are starting new coordinates
    bool new_coordinates = true;

    // have we read in window
    bool windowIn = false;

    // range variables
    int low = 0, high = 0;

    // color variables
    int rVal, gVal, bVal;

    // store current token
    string token;

    // what range are we identifying
    string range_identifier;

    // keep track of expected characters
    char expected = 'n';

    // get first line
    getline(*fin, line);

    // parse file
    while(!fin->eof())
    {
        // have we reached the end of the line
        if(c_index >= line.size())
        {
            getline(*fin, line);
            c_index = 0;
            continue;
        }

        // if we hit a # advance to next line (rest of line is a comment)
        if(line.at(c_index) == '#')
        {
            getline(*fin, line);
            c_index = 0;
            continue;
        }

        // if we haven't started and layer stack is empty then look for "Life"
        if(layer.empty() && !started )
        {
            if(line.size() < 4)
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }
            token = line.substr(c_index, 4);
            c_index = 4;
            if(token != "Life")
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }
            started = true;
            layer_ready = true;
            continue;
        }

        // have we started equality
        if(line.at(c_index) == '=' && layer_ready)
        {
            layer_ready = false;
            if(token == "Life" || token == "Terrain" || token == "Window" || token == "Chars" || token == "Colors" ||
                token == "Initial")
            {
                expected = '{';
            }
            else if(token == "Name")
            {
                expected = '"';
            }
            else if((token == "Alive" && layer.top() == "Chars") || (token == "Dead" && layer.top() == "Chars"))
            {
                expected = 'c'; //c for char
            }
            else if((token == "Alive" && layer.top() == "Initial") || (token == "Dead" && layer.top() == "Initial"))
            {
                expected = 'l'; //l for coordinates List
            }
            else if(token == "Alive" || token == "Dead")
            {
                expected = '(';
            }
            else if(token == "Xrange" || token == "Yrange")
            {
                expected = 'r'; //r for range
            }
            else
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }
            layer.push(token);
            c_index++;
            continue;
        }

        // detect ; to end layer
        if(line.at(c_index) == ';')
        {
            // if layer stack is empty this is invalid
            if(layer.empty() || expected != ';')
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }
            layer.pop();
            c_index++;

            // are we done?
            if(layer.empty() && started)
            {
                if(!windowIn)
                {
                    if(!override_wx)
                    {
                        window.setXLow(terrain.getXLow());
                        window.setXHigh(terrain.getXHigh());
                    }
                    if(!override_wy)
                    {
                        window.setYLow(terrain.getYLow());
                        window.setYHigh(terrain.getYHigh());
                    }
                }

                if((window.getXLow() < terrain.getXLow()) || (window.getXHigh() > terrain.getXHigh()) ||
                    (window.getYLow() < terrain.getYLow()) || (window.getYHigh() > terrain.getYHigh()))
                {
                    this->window = this->terrain;
                }

                delete fin;
                return 0;
            }

            expected = 'n'; //nothing expected next;
            continue;
        }

        // check for '{' character
        if(line.at(c_index) == '{')
        {
            // if we aren't expecting '{' then invalid format
            if(expected != '{')
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }
            expected = 'n';
            c_index++;
            continue;
        }

        // check for '"' character
        if(line.at(c_index) == '"')
        {
            // if we aren't expecting '"' then invalid format
            if(expected != '"')
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }
            expected = 's'; //s for string
            line = line.substr(c_index + 1, std::string::npos);
            c_index = 0;
            continue;
        }

        // check for '}' character
        if(line.at(c_index) == '}')
        {
            // must not be expecting anything
            if(expected != 'n')
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }
            expected = ';';
            c_index++;
            continue;
        }

        // read in string
        if(expected == 's')
        {
            size_t next_quote = line.find("\"");
            if(next_quote == std::string::npos)
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            // found name
            this->name = line.substr(c_index, next_quote);
            c_index += next_quote + 1;
            expected = ';';
            continue;
        }

        // read in range
        if(expected == 'r')
        {
            line = line.substr(c_index, std::string::npos);
            c_index = 0;
            istringstream line_range(line);

            if(!(line_range >> low))
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            if(low >= 0)
            {
                while(low >= 10)
                {
                    low = low / 10;
                    c_index++;
                }
                c_index++;
            }
            else
            {
                while(low <= -10)
                {
                    low = low / 10;
                    c_index++;
                }
                c_index += 2;
            }

            char check;

            line_range >> check;
            if(check != '.')
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }
            line_range >> check;
            if(check != '.')
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            c_index += 2;

            if(!(line_range >> high))
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            if(high >= 0)
            {
                while(high > 10)
                {
                    high = high / 10;
                    c_index++;
                }
                c_index++;
            }
            else
            {
                while(high > -10)
                {
                    high = high / 10;
                    c_index++;
                }
                c_index += 2;
            }

            if((high - low) <= 0)
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            if(range_identifier == "Terrain")
            {
                if(layer.top() == "Xrange" && !this->override_tx)
                {
                    // found xrange for terrain
                    this->terrain.setXLow(low);
                    this->terrain.setXHigh(high);
                }
                else if(layer.top() == "Yrange" && !this->override_ty)
                {
                    // found yrange for terrain
                    this->terrain.setYLow(low);
                    this->terrain.setYHigh(high);
                }
                expected = ';';
                continue;
            }
            else if(range_identifier == "Window")
            {
                if(layer.top() == "Xrange" && !this->override_wx)
                {
                    // found xrange for terrain
                    this->window.setXLow(low);
                    this->window.setXHigh(high);
                }
                else if(layer.top() == "Yrange" && !this->override_wy)
                {
                    // found yrange for terrain
                    this->window.setYLow(low);
                    this->window.setYHigh(high);
                }
                expected = ';';
                continue;
            }
            else
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }
        }

        //read in char
        if(expected == 'c')
        {
            line = line.substr(c_index, std::string::npos);
            c_index = 0;
            istringstream line_range(line);

            if(!(line_range >> low))
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            char out = (char) low;

            if(low >= 0)
            {
                while(low >= 10)
                {
                    low = low / 10;
                    c_index++;
                }
                c_index++;
            }
            else
            {
                while(low > -10)
                {
                    low = low / 10;
                    c_index++;
                }
                c_index += 2;
            }

            if(alive == true)
            {
                //found alive character
                this->display->setAliveChar(out);
            }
            else
            {
                //found dead character
                this->display->setDeadChar(out);
            }
            expected = ';';
            continue;
        }

        // read in color
        if(expected == '(')
        {
            line = line.substr(c_index, std::string::npos);
            istringstream line_color(line);
            c_index = 0;

            char check;

            // start parsing
            line_color >> check;

            c_index++;

            if(check != '(')
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            for(int j = 0; j < 3; j++)
            {
                if(!(line_color >> low))
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }

                if(low < 0 || low > 255)
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }

                //found color value
                switch (j)
                {
                    case 0:
                        rVal = low;
                        break;
                    case 1:
                        gVal = low;
                        break;
                    case 2:
                        bVal = low;
                        break;
                }

                if(!(line_color >> check))
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }

                if((check != ',') && (j != 2))
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }

                if((check != ')') && (j == 2))
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }

                while(low >= 10)
                {
                    low = low / 10;
                    c_index++;
                }
                c_index += 2;
            }

            // save colors
            if(layer.top() == "Alive")
            {
                this->display->setAliveColor(rVal, gVal, bVal);
            }
            else if(layer.top() == "Dead")
            {
                this->display->setDeadColor(rVal, gVal, bVal);
            }
            else
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            expected = ';';
            continue;
        }

        // read in initial coordinates
        if(expected == 'l')
        {
            if(new_coordinates)
            {
                //reset coordinates
                delete coordinates;
                coordinates = new vector<pair<int, int> >();
                new_coordinates = false;
            }

            line = line.substr(c_index, std::string::npos);
            istringstream line_coordinate(line);
            c_index = 0;

            char check;

            if(!(line_coordinate >> check))
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            if(check != '(')
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            c_index++;

            if(!(line_coordinate >> low))
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            if(!(line_coordinate >> check))
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            if(check != ',')
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            if(!(line_coordinate >> high))
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            if(!(line_coordinate >> check))
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            if(check != ')')
            {
                cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                return -1;
            }

            if(low >= 0)
            {
                while(low >= 10)
                {
                    low = low / 10;
                    c_index++;
                }
                c_index++;
            }
            else
            {
                while(low <= -10)
                {
                    low = low / 10;
                    c_index++;
                }
                c_index += 2;
            }
            c_index++;
            if(high >= 0)
            {
                while(high >= 10)
                {
                    high = high / 10;
                    c_index++;
                }
                c_index++;
            }
            else
            {
                while(high <= -10)
                {
                    high = high / 10;
                    c_index++;
                }
                c_index += 2;
            }
            c_index++;

            //add coordinates

            pair<int, int> coor(low, high);
            coordinates->push_back(coor);

            if(line.at(c_index) == ',')
            {
                c_index++;
                continue;
            }

            expected = ';';
            new_coordinates = true;
            continue;
        }

        // check for name
        if(c_index + 4 < line.size() && expected == 'n')
        {
            token = line.substr(c_index, 4);

            if(token == "Name")
            {
                if(layer.top() != "Life")
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }
                layer_ready = true;
                c_index += 4;
                continue;
            }
        }

        // check for Terrain
        if(c_index + 7 < line.size() && expected == 'n')
        {
            token = line.substr(c_index, 7);

            if(token == "Terrain")
            {
                if(layer.top() != "Life")
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }
                range_identifier = token;
                layer_ready = true;
                c_index += 7;
                continue;
            }
        }

        // check for Window
        if(c_index + 6 < line.size() && expected == 'n')
        {
            token = line.substr(c_index, 6);

            if(token == "Window")
            {
                if(layer.top() != "Life")
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }
                range_identifier = token;
                layer_ready = true;
                windowIn = true;
                c_index += 6;
                continue;
            }
        }

        // check for Chars
        if(c_index + 5 < line.size() && expected == 'n')
        {
            token = line.substr(c_index, 5);

            if(token == "Chars")
            {
                if(layer.top() != "Life")
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }
                layer_ready = true;
                c_index += 5;
                continue;
            }
        }

        // check for Colors
        if(c_index + 6 < line.size() && expected == 'n')
        {
            token = line.substr(c_index, 6);

            if(token == "Colors")
            {
                if(layer.top() != "Life")
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }
                layer_ready = true;
                c_index += 6;
                continue;
            }
        }

        // check for Initial
        if(c_index + 7 < line.size() && expected == 'n')
        {
            token = line.substr(c_index, 7);

            if(token == "Initial")
            {
                if(layer.top() != "Life")
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }
                layer_ready = true;
                c_index += 7;
                continue;
            }
        }

        // check for Xrange
        if(c_index + 6 < line.size() && expected == 'n')
        {
            token = line.substr(c_index, 6);

            if(token == "Xrange")
            {
                if(layer.top() != "Terrain" && layer.top() != "Window")
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }
                layer_ready = true;
                c_index += 6;
                continue;
            }
        }

        // check for Yrange
        if(c_index + 6 < line.size() && expected == 'n')
        {
            token = line.substr(c_index, 6);

            if(token == "Yrange")
            {
                if(layer.top() != "Terrain" && layer.top() != "Window")
                {
                    cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
                    return -1;
                }
                layer_ready = true;
                c_index += 6;
                continue;
            }
        }

        // check for Alive
        if(c_index + 5 < line.size() && expected == 'n')
        {
            token = line.substr(c_index, 5);

            if(token == "Alive")
            {
                if(layer.top() == "Chars" || layer.top() == "Colors" || layer.top() == "Initial")
                {
                    layer_ready = true;
                    c_index += 5;
                    alive = true;
                    continue;
                }
            }
        }

        // check for Dead
        if(c_index + 4 < line.size() && expected == 'n')
        {
            token = line.substr(c_index, 4);

            if(token == "Dead")
            {
                if(layer.top() == "Chars" || layer.top() == "Colors")
                {
                    layer_ready = true;
                    c_index += 4;
                    alive = false;
                    continue;
                }
            }
        }

        // if we get here: invalid format
        cerr << "err (Simulation::readGOLFile): invalid gol format" << endl;
        return -1;
    }
}

/**Method that runs simulation up to start generation
 * @param none
 * @ret int: 0 = operation success; -1 = failure
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
int Simulation::run()
{
    // initialize game
    if(game.init(terrain, coordinates, alive_coordinates))
    {
        cerr << "error (Simulation::run): error encountered in GameBoard::init" << endl;
        return -1;
    }

    //loop through generations
    for(generation = generation; generation < startGen; generation++)
    {
        if(game.advanceGen())
        {
            cerr << "error (Simulation::run): error encountered GameBoard::advanceGen" << endl;
            return -1;
        }
    }

    // output data
    if(display->draw(game, name, terrain, window))
    {
        cerr << "error (Simulation::run): error encountered in View::draw" << endl;
        return -1;
    }

    // return successfully
    return 0;
}

/**Method used to set name of simulation
 * @param string givenName: string to use as simulation name
 * @ret void
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
void Simulation::setName(string givenName)
{
    name = givenName;
}

/**Method that sets generation to run simulation to
 * @param int sGen: generation to run simulation to
 * @ret void
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
void Simulation::setStartGen(int sGen)
{
    startGen = sGen;
}

/**Method that sets terrain dimensions
 * @param xLow: lower x boundary for terrain
 * @param xHigh: high x boundary for terrain
 * @param yLow: lower y boundary for terrain
 * @param yHigh: high y boundary for terrain
 * @ret void
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
void Simulation::setTerrain(int xLow, int xHigh, int yLow, int yHigh)
{
    terrain.setXLow(xLow);
    terrain.setXHigh(xHigh);
    terrain.setYLow(yLow);
    terrain.setYHigh(yHigh);
}

/**Method that sets window dimensions
 * @param xLow: lower x boundary for window
 * @param xHigh: high x boundary for window
 * @param yLow: lower y boundary for window
 * @param yHigh: high y boundary for window
 * @ret void
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
void Simulation::setWindow(int xLow, int xHigh, int yLow, int yHigh)
{
    window.setXLow(xLow);
    window.setXHigh(xHigh);
    window.setYLow(yLow);
    window.setYHigh(yHigh);
}

/**Method used to get simulation's name
 * @param none
 * @ret string: name of simulation
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
string Simulation::getName()
{
    return name;
}

/**method used to get simulation's generation
 * @param none
 * @ret int: generation of sim
 * @author Adam Sunderman
 * @modified 04/13/2014 **/
int Simulation::getGen()
{
    return generation;
}
