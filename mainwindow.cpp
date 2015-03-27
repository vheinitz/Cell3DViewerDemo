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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GLWidget.h"

#include <QDir>
#include <QKeyEvent>
#include <QSizePolicy>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    glWidget = new GLWidget;
	glWidget->setMinimumWidth(500);
	glWidget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));

    ui->ltMain->addWidget(glWidget);
    QStringList cells = QDir( ":/" ).entryList(QStringList()<<"*.png");

    _imagesModel.setStringList(cells);
    ui->lvCells->setModel(&_imagesModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lvCells_activated(const QModelIndex &index)
{
    QString img = QString(":/")+index.data().toString();
	glWidget->setImage(img);


}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void MainWindow::on_lvCells_clicked(const QModelIndex &index)
{
    on_lvCells_activated(index);
}
