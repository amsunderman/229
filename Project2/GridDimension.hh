#ifndef GRIDDIMENSION
#define GRIDDIMENSION

using namespace std;

class GridDimension
{
    private:
        int xLow;
        int xHigh;
        int yLow;
        int yHigh;
    public:
        GridDimension();
        GridDimension(int givenXLow, int givenXHigh, int givenYLow, int givenYHigh);
        void setXLow(int givenXLow);
        void setXHigh(int givenXHigh);
        void setYLow(int givenYLow);
        void setYHigh(int givenYHigh);
        int getXLow();
        int getXHigh();
        int getYLow();
        int getYHigh();
};

#endif
