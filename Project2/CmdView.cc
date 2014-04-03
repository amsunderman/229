#include "CmdView.hh"

CmdView::CmdView()
{
    alive = '@';
    dead = '~';
    alive_rVal = alive_gVal = alive_bVal = dead_rVal = dead_gVal = dead_bVal = 0;
}

CmdView::CmdView(char givenAlive, char givenDead, unsigned char given_alive_rVal, unsigned char given_alive_gVal, 
    unsigned char given_alive_bVal, unsigned char given_dead_rVal, unsigned char given_dead_gVal,
    unsigned char given_dead_bVal)
{
    alive = givenAlive;
    dead = givenDead;
    alive_rVal = given_alive_rVal;
    alive_gVal = given_alive_gVal;
    alive_bVal = given_alive_bVal;
    dead_rVal = given_dead_rVal;
    dead_gVal = given_dead_gVal;
    dead_bVal = given_dead_bVal;
}

void CmdView::setAliveChar(char givenAlive)
{
    alive = givenAlive;
}

void CmdView::setDeadChar(char givenDead)
{
    dead = givenDead;
}

void CmdView::setAliveColor(unsigned char rVal, unsigned char gVal, unsigned char bVal)
{
    alive_rVal = rVal;
    alive_gVal = gVal;
    alive_bVal = bVal;
}

void CmdView::setDeadColor(unsigned char rVal, unsigned char gVal, unsigned char bVal)
{
    dead_rVal = rVal;
    dead_gVal = gVal;
    dead_bVal = bVal;
}

void CmdView::draw()
{
    /*TODO*/
}
