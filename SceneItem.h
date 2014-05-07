#ifndef SCENETOP_H
#define SCENETOP_H
#include <qstring.h>
#include <qpoint.h>
	//! SceneItem
	/*!
		Responsibility: Represents a ScenceItem or an item in the topology.
		Examples include devices like controller, switch, equipment like boiler.
	*/
class SceneItem
{
public:
	//! Constructor
	/*!
		\param id as string
		\param type as int
		\param userdefname as string
		\param point QPoint
	*/
	SceneItem(QString id,int type,QString userdefname, QPoint point )
	{
		m_id=id; //Id should be concat of Type Name and Instance Number
		m_type=type;
		m_userDefname=userdefname;
		m_point=point;
	}
	//! Destructor
	~SceneItem(void)
	{
	}
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
		Returns the objecttype as int
	*/
	int getObjectType()
	{
		return m_type;
	}
	//! getUserDefName
	/*!
		Returns the User defined name as string
	*/
	QString getUserDefName()
	{
		return m_userDefname;
	}
	//! getPosition
	/*!
		Returns the position of the item as QPoint
	*/
	QPoint getPosition()
	{
		return m_point;
	}
private:
	QString m_id;
	int m_type;
	QString m_typeName;
	QString m_userDefname;
	QPoint m_point;
};

#endif