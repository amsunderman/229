#ifndef VIEW
#define VIEW

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

/**interface for View objects. All objects that extend View will implement a draw() method for correct GOL output
 * @author Adam Sunderman
 * @modified 04/04/2014 **/
class View
{
    public:
        virtual void draw(); //output GOL data (virtual)
};

#endif
