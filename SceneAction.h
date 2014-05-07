#ifndef SCENEACT_H
#define SCENEACT_H
#include <qstring.h>
#include <qpoint.h>
//! SceneAction
    /*!
        Responsibility: Represents a ScenceAction (Some action which happens in scene)
        Examples include messages across devices, electric signals or heat transfer across
        objects/equipment.
    */
class SceneAction
{
public:
    //! Constructor
    /*!
        \param id string
        \param type int
        \param orderInList int
        \param sourceObj string
        \param destObj string
        \param repeatNooftimes int
        \param waitTime int
        \param txtTitle string
    */

    SceneAction(QString id,int type,int orderInList,QString sourceObj, QString destObj, int repeatNoofTimes, int waitTime, QString txtTitle,QString extImage="" )
    {
        m_id=id;
        m_type=type;
        m_sourceObj=sourceObj;
        m_destObj=destObj;
        m_timesRepeat=repeatNoofTimes;
        m_waitTimeBeforeNext=waitTime;
        m_extImageFile=extImage;
        m_textTitle= txtTitle;
        //m_point=point;
    }
    //! Destructor
    ~SceneAction(void);
    //! getIdentifier
    /*!
        Returns the identifier as string
    */

    QString getIdentifier()
    {
        return m_id;
    }
    //! getObjectType
    /*!
        Returns the objectType as integer
    */
    int getObjectType()
    {
        return m_type;
    }
    //! getSourceName
    /*!
        Returns the sourceName as string
    */
    QString getSourceName()
    {
        return m_sourceObj;
    }
    //! geDestName
    /*!
        Returns the destName as string
    */
    QString getDestName()
    {
        return m_destObj;
    }
    /*
    QPoint getPosition()
    {
        return m_point;
    }*/
    //! getNoofTimesToRepeat
    /*!
        Returns the no of times to repeat action
    */
    int getNoofTimesToRepeat()
    {
        return m_timesRepeat;
    }
    //! getwaitTimeBeforeNext
    /*!
        Returns the wait time before next action
    */
    int getwaitTimeBeforeNext()
    {
        return m_waitTimeBeforeNext;
    }
    /*!
        Returns the title which is shown on message/callout/signal
    */
    QString gettextTite()
    {
        return m_textTitle;
    }
private:
    QString m_id;
    int m_type;
    QString m_sourceObj;
    QString m_destObj;
    int m_timesRepeat;
    int m_waitTimeBeforeNext;
    QString m_extImageFile;
    QString m_textTitle;
    //QPoint m_point;
};

#endif
