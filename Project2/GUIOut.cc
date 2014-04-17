#include "GUIOut.hh"

/**constructor that initializes pixel size of gui cells
 * @author Adam Sunderman
 * @modified 04/14/14 **/
GUIOut::GUIOut(int givenPixelSize)
{
    pixelSize = givenPixelSize;
    alive_rVal = alive_gVal = alive_bVal = dead_rVal = dead_gVal = dead_bVal = 0;
}

int GUIOut::draw(GameBoard game, string name, GridDimension terrain, GridDimension window)
{
    // dummy arguments to use for qt creation
    int argc = 0;
    char ** argv;

    // initialize qt app
    QApplication app(argc,argv);
    QGraphicsScene scene;
    QGraphicsView view(&scene);

    // calculate window offset to start at correct terrain coordinate
    int x_orig = window.getXLow() - terrain.getXLow();
    int y_orig = window.getYLow() - terrain.getYLow();

    // determine window size
    int x_size = (window.getXHigh() - window.getXLow() + 1 + x_orig);
    int y_size = (window.getYHigh() - window.getYLow() + 1 + y_orig);

    // num cells to output
    const int num_cells = x_size * y_size;

    // allocate memory for game grid of qt rectangles
    QGraphicsRectItem** gameGrid = (QGraphicsRectItem**) malloc(num_cells * sizeof(QGraphicsRectItem*));

    // initialize x and y for qt output
    int x = pixelSize, y = pixelSize;

    // index for gamegrid
    int count = 0;

    // initialize gui size
    view.setFixedSize((pixelSize * x_size + (pixelSize*2)), (pixelSize * y_size + (pixelSize*2)));

    // loop through terrain and make q graphics rectangles for all relevant cells
    for(int i = y_size - 1; i > y_orig - 1; i--)
    {
        for(int j = x_orig; j < x_size; j++)
        {
            if(game.getCell(j, i).isAlive())
            {
                gameGrid[count] = new QGraphicsRectItem(x * pixelSize, y * pixelSize, pixelSize, pixelSize);
                gameGrid[count]->setBrush(QColor(alive_rVal, alive_gVal, alive_bVal));
                scene.addItem(gameGrid[count++]);
                x++;
            }
            else
            {
                gameGrid[count] = new QGraphicsRectItem(x * pixelSize, y * pixelSize, pixelSize, pixelSize);
                gameGrid[count]->setBrush(QColor(dead_rVal, dead_gVal, dead_bVal));
                scene.addItem(gameGrid[count++]);
                x++;
            }
        }
        y++;
        x = pixelSize;
    }

    // change name to c_string to sent to qt api
    QString qstr(name.c_str());

    // set title of window and display
    view.setWindowTitle(qstr);
    view.show();

    // execute application
    app.exec();

    // free memory
    for(int i = 0; i < num_cells; i++)
    {
        delete gameGrid[i];
    }

    free(gameGrid);

    return 0;
}
