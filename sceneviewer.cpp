#include "sceneviewer.h"

//Qt includes
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTextStream>
#include <QScrollBar>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QMessageBox>
SceneViewer::SceneViewer(QWidget *parent) :
    QGraphicsView(parent)
{

    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

        //Set-up the scene
        QGraphicsScene* Scene = new QGraphicsScene(this);
        setScene(Scene);


        //Set-up the view
        setSceneRect(0, 0, 1000, 1000);

        //Use ScrollHand Drag Mode to enable Panning
        setDragMode(ScrollHandDrag);
}

void SceneViewer::zoomPlusScene()
{
    //QMessageBox box;
    //box.setText("Wheel reached");
    //box.exec();
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    //scales down
    //scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    // Zoom Plus
    scale(scaleFactor, scaleFactor);

}

void SceneViewer::zoomMinusScene()
{
    //QMessageBox box;
    //box.setText("Wheel reached");
    //box.exec();
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    //scales down
    scale(1.0 / scaleFactor, 1.0 / scaleFactor);

}

/**
  * Zoom the view in and out.
  */
void SceneViewer::wheelEvent(QWheelEvent* event) {

    QMessageBox box;
    box.setText("Wheel reached");
    box.exec();
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    // Don't call superclass handler here
    // as wheel is normally used for moving scrollbars
}
