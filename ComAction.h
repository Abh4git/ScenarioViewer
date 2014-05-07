#ifndef COMACT_H
#define COMACT_H
#include <qstring.h>
#include <qpoint.h>
	//! ComAction
	/*!
		Responsibility: Represents a Communication Action 
	*/
class ComAction
{
public:
	//! Constructor
	/*!
		\param id string
		\param type int
		\param assocSceneActId int
		\param sourceAddress string
		\param destAddress string
		\param repeattimes int
		\param timeToNext int
	*/
	ComAction(QString id,int type,int assocSceneActId,QString sourceAddress, QString destAddress, int repeatTimes, int timeToNext )
	{
		m_id=id;
		m_type=type;
		m_sourceAddress=sourceAddress;
		m_assocSceneActId=assocSceneActId;
		m_destAddress=destAddress;
		m_timesRepeat=repeatTimes;
		m_timeToNext=timeToNext;
	}
	//! Destructor
	~ComAction(void)
	{
	}
	//! getIdentifier
	/*!
		Returns the identifier of communication action
	*/
	QString getIdentifier()
	{
		return m_id;
	}
	//! getObjectType
	/*!
		Returns the object Type of communication action
	*/
	int getObjectType()
	{
		return m_type;
	}
	//! getSourceAddress
	/*!
		Returns the source address of the communication action
	*/
	QString getSourceAddress()
	{
		return m_sourceAddress;
	}
	//! getDestAddress
	/*!
		Returns the destination address of the communication action
	*/
	QString getDestAddress()
	{
		return m_destAddress;
	}
	//! getNoofTimesToRepeat
	/*!
		Returns the number ot times the scene action need be repeated
	*/
	int getNoofTimesToRepeat()
	{
		return m_timesRepeat;
	}
	//! waitTimeBeforeNext
	/*!
		Returns in millesecond the time to wait before the next scene action
	*/
	int waitTimeBeforeNext()
	{
		return m_timeToNext;
	}
private:
	QString m_id;
	int m_type;
	QString m_sourceAddress;
	QString m_destAddress;
	int m_assocSceneActId;
	int m_timesRepeat;
	int m_timeToNext;
	
};

#endif