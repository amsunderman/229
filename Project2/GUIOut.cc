#include "GUIOut.hh"

GUIOut::GUIOut(int givenPixelSize)
{
    pixelSize = givenPixelSize;
    alive_rVal = alive_gVal = alive_bVal = dead_rVal = dead_gVal = dead_bVal = 0;
}

int GUIOut::draw(GameBoard game, string name, GridDimension terrain, GridDimension window)
{
    int argc = 0;
    char ** argv;

    QApplication app(argc,argv);

    QGraphicsScene scene;
    QGraphicsView view(&scene);

    int x_orig = window.getXLow() - terrain.getXLow();
    int y_orig = window.getYLow() - terrain.getYLow();

    int x_size = (window.getXHigh() - window.getXLow() + 1 + x_orig);
    int y_size = (window.getYHigh() - window.getYLow() + 1 + y_orig);

    const int num_cells = x_size * y_size;

    QGraphicsRectItem** gameGrid = (QGraphicsRectItem**) malloc(num_cells * sizeof(QGraphicsRectItem*));

    int x = pixelSize, y = pixelSize;
    int count = 0;

    view.setFixedSize((pixelSize * x_size + (pixelSize*2)), (pixelSize * y_size + (pixelSize*2)));

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

    QString qstr(name.c_str());

    view.setWindowTitle(qstr);
    view.show();

    return app.exec();

    for(int i = 0; i < num_cells; i++)
    {
        delete gameGrid[i];
    }

    free(gameGrid);

    return 0;
}
