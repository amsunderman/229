#include "GridDimension.hh"

GridDimension::GridDimension()
{
    xLow = xHigh = yLow = yHigh = 0;
}

GridDimension::GridDimension(int givenXLow, int givenXHigh, int givenYLow, int givenYHigh)
{
    xLow = givenXLow;
    xHigh = givenXHigh;
    yLow = givenYLow;
    yHigh = givenYHigh;
}

void GridDimension::setXLow(int givenXLow)
{
    xLow = givenXLow;
}

void GridDimension::setXHigh(int givenXHigh)
{
    xHigh = givenXHigh;
}

void GridDimension::setYLow(int givenYLow)
{
    yLow = givenYLow;
}

void GridDimension::setYHigh(int givenYHigh)
{
    yHigh = givenYHigh;
}

int GridDimension::getXLow()
{
    return xLow;
}

int GridDimension::getXHigh()
{
    return xHigh;
}

int GridDimension::getYLow()
{
    return yLow;
}

int GridDimension::getYHigh()
{
    return yHigh;
}
