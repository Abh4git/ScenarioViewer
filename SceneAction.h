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
	*/
	SceneAction(QString id,int type,int orderInList,QString sourceObj, QString destObj, int repeatNoofTimes, int waitTime, QString extImage="" )
	{
		m_id=id;
		m_type=type;
		m_sourceObj=sourceObj;
		m_destObj=destObj;
		m_timesRepeat=repeatNoofTimes;
		m_waitTimeBeforeNext=waitTime;
		m_extImageFile=extImage;
		//m_point=point;
	}
	//! Destructor
	~SceneAction(void);
	//! getIdentifier
	/*!
		Returns the identifier of scene action
	*/
	QString getIdentifier()
	{
		return m_id;
	}
	//! getObjectType
	/*!
		Returns the object type of scene item
	*/
	int getObjectType()
	{
		return m_type;
	}
	//! getSourceName
	/*!
		Returns the source object name of scene action as string
	*/
	QString getSourceName()
	{
		return m_sourceObj;
	}
	//! getDestName
	/*!
		Returns the dest object name of scene action
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
		Returns the number of times the action repeats
	*/
	int getNoofTimesToRepeat()
	{
		return m_timesRepeat;
	}
	//! getwaitTimeBeforeNext
	/*!
		Returns the waiting time in millisecond till next scene action
	*/
	int getwaitTimeBeforeNext()
	{
		return m_waitTimeBeforeNext;
	}
private:
	QString m_id;
	int m_type;
	QString m_sourceObj;
	QString m_destObj;
	int m_timesRepeat;
	int m_waitTimeBeforeNext;
	QString m_extImageFile;
	//QPoint m_point;
};

#endif