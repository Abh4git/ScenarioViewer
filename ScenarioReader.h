

#ifndef SCENEREADER_H
#define SCENEREADER_H
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QDir>
#include <SceneAction.h>
#include <SceneItem.h>
#include <qstringlist.h>
#include <ComAction.h>
	//! ScenarioReader class
	/*!
		Responsibility: Reader or Praser to read in scenario files and create the
		in memory defintions which include SceneTopology, SceneActions and ComActions
	*/
class ScenarioReader
{
public:
    //! Constructor
	/*!
		\param filename as QString
		Name and path of Scenario file
	*/
	ScenarioReader(QString filename);
    
	//! SetDirectory
	/*!
		\param directoryName as QString
		Name of the directory where the file is located
	*/
	bool SetDirectory(QString directoryName);
	//! ReadDefintions
	/*!
		Parses the file, fills the Topology, Scene Actions and
		ComActions lists and returns true is success.
	*/
    bool ReadDefintions();
	//! GetActionSequence
	/*!
		Returns the SceneAction(s) as list
	*/
    QList<SceneAction*> GetActionSequence()
	{
		return m_ActionsList;
	}
	//! GetSceneTopology
	/*!
		Returns the SceneItems(s) as list
	*/
	QList<SceneItem*> GetSceneTopology()
	{
		return m_TopologyItemsList;
	}
	//! GetComActions
	/*!
		Returns the ComAction(s) as list
	*/
	QList<ComAction*> GetComActions()
	{
		return m_CommunicationActionsList;
	}
	//! Desctructor
    ~ScenarioReader();
private:
	bool ReadToplogy();
	bool ReadActions();
	bool ReadSceneItems();
	bool ReadComActions();

    QString filename;
    QFile file;
    QXmlStreamReader reader;
    QDir dir;
	QList<SceneAction*> m_ActionsList;
	QList<SceneItem*> m_TopologyItemsList;
	QList<ComAction*> m_CommunicationActionsList;
	
};



#endif // BOMADAPTATIONREADER_H
