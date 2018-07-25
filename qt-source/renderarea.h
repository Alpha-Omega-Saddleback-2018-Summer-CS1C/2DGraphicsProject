/*
 *  2D Graphics Modeler
 *  July 2018
 *
 *  David Epstein <DavidE92@live.com>
 *  Greg Graffius <ggraffius0@saddleback.edu>
 *  Justis Ketcham <justis.ketcham@gmail.com>
 *  Brett Saiki <bsaiki0@saddleback.edu>
 *
 *  Descr:   Final project for CS1C at Saddleback College (Summer 2018)
 *  Teacher: John Kath
 *
 *  Draws shapes using QPainter. Shapes can be loaded from a file, added
 *  to a vector, manipulated and later saved. A login is required to access
 *  the program.
 *
 **/
/*
    File: renderarea.h

    Defines a main window
 */

#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QPen>
#include <QWidget>
#include "custom_vector.h"
#include "shape.h"

using shape::Shape;

/**	Implements a QWidget that renders shapes. */
class RenderArea : public QWidget
{
public:

	/**	Default constructor. Initializes widgets */
    explicit RenderArea(QWidget* parent = 0);
	
	/**	Passes the shape vector */
    void passParams(Vector<Shape*>* shapes);

public slots:

protected:
	/** Updates the render area when a shape is changed */
    void paintEvent(QPaintEvent* event) override;

private:
    Vector<Shape*>* shapeVector;
};

#endif // RENDERAREA_H
