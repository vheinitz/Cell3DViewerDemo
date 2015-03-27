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

#include <QtGui>
#include <QtOpenGL>
#include <QImage>

#include <math.h>

#include "glwidget.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
	xRot(1440),
	yRot(1440),
	zRot(0),
	_vertexes(0)
{

}

GLWidget::~GLWidget()
{
}


static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}


void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}


void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}


void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setImage (QString img)
{
	qimg = QImage(img);
	initVertexes();
	//paintGL();
	update();
}

void GLWidget::initVertexes()
{

	if ( qimg.isNull() )
		return;

	int width = qimg.width();
	int height = qimg.height();

	float sz = 1.0 / 100; //255; scaling images as they have very low intensity
	float sx=1.0 / width;
	float sy=1.0 / height;
	float xo = sx/2;
	float yo = sy/2;
	float zo = sz/2;

	_vertexesMx.lock();
	glDeleteLists(_vertexes,1);
    _vertexes = glGenLists(1);
    glNewList(_vertexes, GL_COMPILE);
	GLenum mode = GL_TRIANGLES;//GL_TRIANGLES GL_POINTS GL_LINES GL_POINTS GL_TRIANGLE_STRIP GL_QUADS
	glBegin(mode);
	
	for (int y = 0; y < height - 2; y++) {
		int x = 0;
		float gy = y*sy -yo;
		float gy1 = (y+1)*sy-yo;
		for (x; x < width-2; x++) {

			float z = qGray(qimg.pixel(x, y));
			float gx = x*sx -xo;			
			float gx1 = (x+1)*sx -xo;	

			float gz = qGray(qimg.pixel(x, y))*sz -zo;
			glColor3f(0, gz, 0);
			glVertex3f(gx, gz, gy);

			gz = qGray(qimg.pixel(x, y+1))*sz -zo;
			glColor3f(0, gz, 0);
			glVertex3f(gx, gz, gy1);

			gz = qGray(qimg.pixel(x+1, y))*sz -zo;
			glColor3f(0, gz, 0);
			glVertex3f(gx1, gz, gy);
			
			glVertex3f(gx1, gz, gy);

			gz = qGray(qimg.pixel(x, y+1))*sz -zo;
			glColor3f(0, gz, 0);
			glVertex3f(gx, gz, gy1);

			gz = qGray(qimg.pixel(x+1, y+1))*sz -zo;
			glColor3f(0, gz, 0);
			glVertex3f(gx1, gz, gy1);
			
		}			
	}
	glEnd();
	glEndList();
	_vertexesMx.unlock();
}

void GLWidget::initializeGL()
{
	qglClearColor(qtPurple.dark());   

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    initVertexes();

	
}




void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-.25, -.25, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    glScalef(.6f, .6f, .6f);	
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	_vertexesMx.lock();
	if ( _vertexes )
		glCallList(_vertexes);
	_vertexesMx.unlock();
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}



void GLWidget::resizeGL(int width, int height)
{
 int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);

	 //reshape(w,h);
}



void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}



void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}

