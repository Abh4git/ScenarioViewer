#ifndef SCENEVIEWER_H
#define SCENEVIEWER_H

#include <QGraphicsView>
#include <QGraphicsRectItem>
class SceneViewer : public QGraphicsView
{
    Q_OBJECT
public:
    SceneViewer(QWidget *parent = NULL);

signals:

public slots:
    /*!
       Does Zooming Plus
     */
      void zoomPlusScene();
      /*!
         Does Zooming Minus
       */
        void zoomMinusScene();

protected:

    //Take over the interaction
    virtual void wheelEvent(QWheelEvent* event);


};

#endif // SCENEVIEWER_H
