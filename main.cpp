/* ===========================================================================
 * Copyright 2015: Valentin Heinitz, www.heinitz-it.de
 * HEp-2 Cell viewer demo
 * Author: Valentin Heinitz, 2015-03-28
 * License: MIT License
 *
 * D E S C R I P T I O N
 *  Demonstration of 2D -Image to 3D Height Map conversion using OpenGL.
 * The code is mainly derived from Qt's OpenGL examples helloGL and buffer.
 *
 * Credits:
 * ========
 * The demo uses SNPHEp-2 - cell images data set
 * Copyright 2013 - Arnold Wiliem, Peter Hobson, Brian C. Lovell, University of Queensland, 
 * Sullivan Nicolaides Pathology. 
 * contact: a.wiliem@uq.edu.au; arnold.wiliem@ieee.org
 ========================================================================== */

#include <QApplication>
#include <QDesktopWidget>
#include "MainWindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
