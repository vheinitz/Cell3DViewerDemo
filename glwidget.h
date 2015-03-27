/* ===========================================================================
 * Copyright 2015: Valentin Heinitz, www.heinitz-it.de
 * HEp-2 Cell viewer demo
 * Author: Valentin Heinitz, 2015-03-28
 * License: MIT License
 *
 * D E S C R I P T I O N
 *  Demonstration of 2D -Image to 3D Height Map conversion using OpenGL.
 * The code is mainly derived from Qt's OpenGL examples helloGL and buffer.
 ========================================================================== */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QImage>
#include <QMutex>

//! Class which actually loads, renders and displays the image contents in 3D
class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setImage (QString);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	void initVertexes();

private:

    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;
    GLuint _vertexes;
    QImage qimg;
	QMutex _vertexesMx;
};

#endif
