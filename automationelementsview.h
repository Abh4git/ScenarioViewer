#ifndef AUTOMATIONELEMENTSVIEW_H
#define AUTOMATIONELEMENTSVIEW_H

#include <QWidget>
#include "ui_automationelementsview.h"
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qframe.h>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QApplication>
//plugins
#include <qpluginloader.h>
#include <qplugin.h>
#include "../BOMLibrary/IBOMTypeLoadInterface.h"
#include "../BOMGraphicalLibrary/IBOMInstanceCreation.h"
#include "../BOMGraphicalLibrary/connectorgraphicitem.h"
#include "../BOMGraphicalLibrary/MsgGraphicsItem.h"
#include "../BOMGraphicalLibrary/ActionGraphicsItem.h"
#include <qmenu.h>
#include <qaction.h>
#include <QContextMenuEvent>
#include "animation.h"
#include "../BOMGraphicalLibrary/msgGraphicsItemWithText.h"
#include "../BOMGraphicalLibrary/ActionGraphicsItem.h"
#include <SceneAction.h>
#include <SceneItem.h>
#include <ScenarioReader.h>
#include <sceneviewer.h>
using namespace BOMLIB;

/*class PixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    PixmapItem(const QPixmap &pix) : QGraphicsPixmapItem(pix)
    {
    }
};*/
//! AutomationElementsView
	/*!
		Responsibility: Acts as container for the Graphics Scene and Animation Environment.
		
	*/
class AutomationElementsView : public QWidget
{
	Q_OBJECT

public:
	//! Constructor
	/*!
		\param parent QWidget
	*/
	AutomationElementsView(QWidget *parent = 0);
	//! Destructor
	~AutomationElementsView();
protected:
	//! contextMenuEvent
	/*!
		\param event QContextMenuEvent
		Context Menu override
	*/
	void contextMenuEvent(QContextMenuEvent *event);
private slots:
    //! performLoadTopology
	/*!
		Loading Topology from scenario files
	*/
    //void performLoadTopology();
	
	//! playAnimation
	/*!
		Playing the scenario actions on the topology.
	*/
    /*
	void playAnimation();
	//for CSA Scenario hardcoded
	void loadUserScenarioCSA1Topology();
	void playUserScenarioCSA1();

	//from file
	void loadUserScenarioCSASel();
    void playUserScenarioCSASel();*/
    //! connect elements Hardoced BTG
    /*!
        Connect Elements in scene ie here BTG
    */
    void connectBTG();
    //! clearAll
	/*!
		Clear the Graphics Scene
	*/
	void clearAll();
	//! openSceneFile
	/*!
		Open a scenario File (XML)
	*/
	void openSceneFile();
	//! ReadScenario
	/*!
		From opened scenario read the scenario and fill the in memory objects.
	*/
	void ReadScenario(QString fileName);
	//! playCurrentScenario
	/*!
		From read scenario, play the sceneActions.
	*/
	void playCurrentScenario();
    //! zoomScene

private:
	Ui::AutomationElementsView ui;
    //! setupWidgets
    /*!
        Arranges and sets up GraphicsScene, The right ActionList pane
        and Message Tables.
    */
	void setupWidgets();
    //! LoadPlugins
    /*!
        Checks for QtPlugins and Loads them into memory.
    */
	void LoadPlugins();
    //! loadTypeDefinitions
    /*!
        Uses BOMLibrary to Load the Type Defintions.
    */
    void loadTypeDefinitions();
    //! findInstance
    /*!
        Searches the BOMInstance List and finds the instance based on name
        and instance number.
        \param name string
        \param instNo int
    */
	BOMInstance* findInstance(QString name,int instNo);
    //! startAnimation
    /*!
        Triggers Playing of the scenario by Animation Start
    */
    void startAnimation();

    IBOMTypeLoadInterface* m_BOMTypeLoader;
	IBOMInstanceCreation* m_BOMInstanceCreator;
	QGraphicsScene* m_graphicsScene;
    //QGraphicsView* m_graphicsView;
    SceneViewer* m_graphicsView;
    QAction* m_actConnectElements;

    QAction* m_actClearAll;
	QAction* m_actOpenScenarioFile;
	QAction* m_actPlayScenarioFile;
    QAction* m_actZoomPlus;
    QAction* m_actZoomMinus;

    ActionGraphicsItem* m_item;
    MsgGraphicsItem* m_itemThird;
    QObject* m_itemSecond;
    Animation *m_anim;
    Animation *m_animTrig;

	
    //List of Connections
    QList<ConnectorGraphicitem*> m_Connections;
	QList<BOMInstance*> m_BOMInstancesList;
	ConnectorGraphicitem* findConnection(QString connectIdentifer);

	//current Actions and Topology
	QList<SceneAction*> m_currentSceneActions;
	QList<SceneItem*> m_currentSceneItems;
};

#endif // AUTOMATIONELEMENTSVIEW_H
