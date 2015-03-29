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
#include <QFileDialog>
#include "persistence.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	PERSISTENCE_INIT( "VHeinitz", "OpenGLCellViewer" );
    PERSISTENT("LastImagesPath", &_lastImagesPath, this );
	PERSISTENT("OptionNormalized", ui->actionNormalize, "checked");
	PERSISTENT("Geometry", this, "geometry");

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
	QString img = index.data().toString();
	if ( !QFileInfo(img).exists() )
	{
		img = QString(":/")+index.data().toString();
	}
	glWidget->normalize( ui->actionNormalize->isChecked() );
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

void MainWindow::on_actionNormalize_triggered()
{
    glWidget->normalize( ui->actionNormalize->isChecked() );
}

void MainWindow::on_actionLoad_Images_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames( this, tr("Select Images ..."), _lastImagesPath, "*.png" );
    if ( !files.isEmpty() )
    {
        _imagesModel.setStringList(files);
		_lastImagesPath = QFileInfo(files.at(0)).path();
    }
}
