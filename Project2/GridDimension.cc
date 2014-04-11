#include "GridDimension.hh"

/**default constructor, initializes all dimensions to 0
 * @author Adam Sunderman
 * @modified 04/11/2014 **/
GridDimension::GridDimension()
{
    xLow = xHigh = yLow = yHigh = 0;
}

/**initialization constructor, initializes dimensions via given dimensions
 * @param int givenXLow, int givenXHigh, int givenYLow, int genYHigh
 * @author Adam Sunderman
 * @modified 04/11/2014 **/
GridDimension::GridDimension(int givenXLow, int givenXHigh, int givenYLow, int givenYHigh)
{
    xLow = givenXLow;
    xHigh = givenXHigh;
    yLow = givenYLow;
    yHigh = givenYHigh;
}

/**set xLow
 * @param int givenXLow: new x Low value
 * @ret void
 * @author Adam Sunderman
 * @modified 04/11/2014 **/
void GridDimension::setXLow(int givenXLow)
{
    xLow = givenXLow;
}

/**set xHigh
 * @param int givenXHigh: new x High value
 * @ret void
 * @author Adam Sunderman
 * @modified 04/11/2014 **/
void GridDimension::setXHigh(int givenXHigh)
{
    xHigh = givenXHigh;
}

/**set yLow
 * @param int givenYLow: new y Low value
 * @ret void
 * @author Adam Sunderman
 * @modified 04/11/2014 **/
void GridDimension::setYLow(int givenYLow)
{
    yLow = givenYLow;
}

/**set yHigh
 * @param int givenYHigh: new y High value
 * @ret void
 * @author Adam Sunderman
 * @modified 04/11/2014 **/
void GridDimension::setYHigh(int givenYHigh)
{
    yHigh = givenYHigh;
}

/**returns current x low
 * @param none
 * @ret int: requested dimension
 * @author Adam Sunderman
 * @modified 04/11/2014 **/
int GridDimension::getXLow()
{
    return xLow;
}

/**returns current x high
 * @param none
 * @ret int: requested dimension
 * @author Adam Sunderman
 * @modified 04/11/2014 **/
int GridDimension::getXHigh()
{
    return xHigh;
}

/**returns current y low
 * @param none
 * @ret int: requested dimension
 * @author Adam Sunderman
 * @modified 04/11/2014 **/
int GridDimension::getYLow()
{
    return yLow;
}

/**returns current y high
 * @param none
 * @ret int: requested dimension
 * @author Adam Sunderman
 * @modified 04/11/2014 **/
int GridDimension::getYHigh()
{
    return yHigh;
}
