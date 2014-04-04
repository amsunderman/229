#ifndef GRIDDIMENSION
#define GRIDDIMENSION

using namespace std;

/**Grid Dimension object used to store dimensions
 * @author Adam Sunderman
 * @modified 04/04/2014 **/
class GridDimension
{
    private:
        int xLow; //horizontal low coordinate
        int xHigh; //horizontal high coordinate
        int yLow; //vertical low coordinate
        int yHigh; //vertical high coordinate
    public:
        GridDimension(); //default constructor
        GridDimension(int givenXLow, int givenXHigh, int givenYLow, int givenYHigh); //initialation constructor
        void setXLow(int givenXLow); //set horizontal low coordinate
        void setXHigh(int givenXHigh); //set horizontal high coordinate
        void setYLow(int givenYLow); //set vertical low coordinate
        void setYHigh(int givenYHigh); //set vertical high coordinate
        int getXLow(); //return horizontal low coordinate
        int getXHigh(); //return horizontal high coordinate
        int getYLow(); //return vertical low coordinate
        int getYHigh(); //return vertical high coordinate
};

#endif
