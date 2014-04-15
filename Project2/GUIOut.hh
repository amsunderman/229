#ifndef GUIOUT
#define GUIOUT

#include <QApplication>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "View.hh"

/**View that outputs to QT GUI (extension of View object)
 * @author Adam Sunderman
 * @modified 04/14/2014 **/
class GUIOut:public View
{
    private:
        int pixelSize;
    public:
        GUIOut(int givenPixelSize); //initialazation constructor
        int draw(GameBoard game, string name, GridDimension terrain, GridDimension window); //outputs gol data
};

#endif
