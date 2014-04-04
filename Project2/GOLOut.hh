#ifndef GOLOUT
#define GOLOUT

#include "View.hh"

/**View that outputs to GOL file (extension of View object)
 * @author Adam Sunderman
 * @modified 04/04/2014 **/
class GOLOut:public View
{
    public:
        void draw(); //outputs simulation data to GOL file
};

#endif
