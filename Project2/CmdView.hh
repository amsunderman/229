#ifndef CMDVIS
#define CMDVIS

#include "View.hh"

class CmdView:public View
{
    private:
        char alive;
        char dead;
        unsigned char alive_rVal;
        unsigned char alive_gVal;
        unsigned char alive_bVal;
        unsigned char dead_rVal;
        unsigned char dead_gVal;
        unsigned char dead_bVal;
    public:
        CmdView();
        CmdView(char givenAlive, char givenDead, unsigned char given_alive_rVal, unsigned char given_alive_gVal, 
            unsigned char given_alive_bVal, unsigned char given_dead_rVal, unsigned char given_dead_gVal, 
            unsigned char given_dead_bVal);
        void setAliveChar(char givenAlive);
        void setDeadChar(char givenDead);
        void setAliveColor(unsigned char rVal, unsigned char gVal, unsigned char bVal);
        void setDeadColor(unsigned char rVal, unsigned char gVal, unsigned char bVal);
        void draw();
};

#endif
