
#ifndef ANIMATION_H
#define ANIMATION_H

#include <QtGui>

#include <QtCore/qpropertyanimation.h>
#include <QGraphicsItemGroup>
	//! Animation
	/*!
		Responsibility: Inheriting from QPropertyAnimation, this class is responsible for having the engine
		for animating the objects in the Graphics Scene.
	*/
class Animation : public QPropertyAnimation {
public:
    enum PathType {
        LinearPath,
        CirclePath,
        NPathTypes
    };
	//! Constructor
	/*!
		\param target QObject
		\param prop
	*/
    Animation(QObject *target, const QByteArray &prop)
        : QPropertyAnimation(target, prop)
    {
        setPathType(LinearPath);
    }

	/*
	Animation(QGraphicsItemGroup *target, const QByteArray &prop)
        : QPropertyAnimation(target, prop)
    {
        setPathType(LinearPath);
    }*/
	//! setPathType
	/*!
		\param pathType as path
		
	*/
    void setPathType(PathType pathType)
    {
        if (pathType >= NPathTypes)
            qWarning("Unknown pathType %d", pathType);

        m_pathType = pathType;
        m_path = QPainterPath();
    }

	//! updateCurrentTime
	/*!
		\param currentTime as int
		
	*/
    void updateCurrentTime(int currentTime)
    {
        if (m_pathType == CirclePath) {
            if (m_path.isEmpty()) {
                QPointF to = endValue().toPointF();
                QPointF from = startValue().toPointF();
                m_path.moveTo(from);
                m_path.addEllipse(QRectF(from, to));
            }
            int dura = duration();
            const qreal progress = ((dura == 0) ? 1 : ((((currentTime - 1) % dura) + 1) / qreal(dura)));

            qreal easedProgress = easingCurve().valueForProgress(progress);
            if (easedProgress > 1.0) {
                easedProgress -= 1.0;
            } else if (easedProgress < 0) {
                easedProgress += 1.0;
            }
            QPointF pt = m_path.pointAtPercent(easedProgress);
            updateCurrentValue(pt);
            emit valueChanged(pt);
        } else {
            QPropertyAnimation::updateCurrentTime(currentTime);
        }
    }

    QPainterPath m_path;
    PathType m_pathType;
};

#endif // ANIMATION_H
