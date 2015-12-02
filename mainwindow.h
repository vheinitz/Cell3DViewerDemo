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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class GLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_lvCells_activated(const QModelIndex &index);

    void on_lvCells_clicked(const QModelIndex &index);

    void on_actionNormalize_triggered();

    void on_actionLoad_Images_triggered();

    void on_actionExport_as_image_triggered();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    GLWidget *glWidget;
    QStringListModel _imagesModel;
	QString _lastImagesPath;
    QString _lastStorePath;
};

#endif // MAINWINDOW_H
