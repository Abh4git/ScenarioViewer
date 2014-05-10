#include "automationelementsview.h"
#include <qpoint.h>
#include <QSequentialAnimationGroup>
#include <ScenarioReader.h>
#include "..\BOMGraphicalLibrary\bominstance.h"
#include <QMessageBox>
using namespace WSIMINST;
AutomationElementsView::AutomationElementsView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setupWidgets();
	LoadPlugins();
	loadTypeDefinitions();
	//CreateBOMGraphics();

	
}

//Load Definitions needed for all
void AutomationElementsView::loadTypeDefinitions()
{
	QString pathToTypeDef= QDir::currentPath()+ "\\ModelElements";
	//this->m_BOMTypeLoader->LoadDefinitions("C:\\Abhilash\\MyToolBox\\SystemsExplorer\\SystemsExplorer\\AutomationModelElements");
	this->m_BOMTypeLoader->LoadDefinitions(pathToTypeDef);

	


}
void AutomationElementsView ::startAnimation()
{

    QSequentialAnimationGroup *animation1SubGroup = new QSequentialAnimationGroup;
    Animation* messageAnim;
	int Count=0;
    foreach(ConnectorGraphicitem* connectGraphItem, this->m_Connections)
    {
        //new signal
		
        if(connectGraphItem->data(1).toString()=="message")
        {
        //m_itemSecond= this->m_BOMInstanceCreator->createMessagePacket(QPoint(10*Count,10*Count)); //new PixmapItem(pixMap);
        //this->m_graphicsScene->addItem(m_itemSecond);
        //messageAnim = new Animation(m_itemSecond, "pos");
        }
        else if(connectGraphItem->data(1).toString()=="display")
        {
        m_itemThird=this->m_BOMInstanceCreator->createMessagePacket(QPoint(100,100));// new PixmapItem(pixMap);
        this->m_graphicsScene->addItem(m_itemThird);
        messageAnim = new Animation(m_itemThird, "pos");
        }
        else
        {
            messageAnim= new Animation(m_item,"pos");
        }
		QPointF pointStart=connectGraphItem->getBeginPoint();
		QPointF pointEnd=connectGraphItem->getEndPoint();
        messageAnim->setStartValue(pointStart);//connectGraphItem->getBeginPoint());
        messageAnim->setEndValue(pointEnd);//connectGraphItem->getEndPoint());
        messageAnim->setLoopCount(5);
        animation1SubGroup->addAnimation(messageAnim);
        animation1SubGroup->addPause(1000);
		Count=Count+2;
    }
     
    animation1SubGroup->start();

}

void AutomationElementsView::contextMenuEvent(QContextMenuEvent *event)
 {
     //QMenu menu(this);
	 QMenu menu(this->m_graphicsView);
    /* menu.addAction(m_actLoadTopology);
	 menu.addAction(m_actStartAnimation);
	 menu.addAction(m_actUserScenarioCSA1TopologyLoad);
	 menu.addAction(m_actUserScenarioCSA1);
	 //from file
	 menu.addAction(m_actUserScenarioBasedOnSelect);
     menu.addAction(m_actPlayUserScenarioBasedOnSelect);*/
         menu.addAction(m_actConnectElements);
	 menu.addAction(m_actClearAll);
	 menu.addAction(m_actOpenScenarioFile);
	 menu.addAction(m_actPlayScenarioFile);
     menu.addAction(m_actZoomPlus);
     menu.addAction(m_actZoomMinus);
	 //removed now -menu.addAction(m_actAllocation);
     menu.exec(event->globalPos());
 }

void AutomationElementsView::setupWidgets()
{
	QFrame *frame = new QFrame;
	QHBoxLayout *frameLayout = new QHBoxLayout(frame);
    //this->m_graphicsView = new QGraphicsView(this);
    this->m_graphicsView = new SceneViewer(this);
	this->m_graphicsView->setSceneRect(50, 50, 350, 350);
	
	this->m_graphicsScene= new QGraphicsScene(this);
	this->m_graphicsView->setScene(this->m_graphicsScene);

	frameLayout->addWidget(this->m_graphicsView);
	this->setLayout(frameLayout);

	//menus
//	m_actLoadTopology = new QAction(tr("&Load Topology"), this);
  //   m_actLoadTopology->setShortcuts(QKeySequence::Open);
    // m_actLoadTopology->setStatusTip(tr("Load a Defined Topology"));
     //connect(m_actLoadTopology, SIGNAL(triggered()), this, SLOT(performLoadTopology()));
	 //menu for animation - action
     //m_actStartAnimation = new QAction(tr("&Play Animation"), this);
     //m_actStartAnimation->setShortcuts(QKeySequence::New);
     //m_actStartAnimation->setStatusTip(tr("Play Defined Sequqnce"));
     //connect(m_actStartAnimation, SIGNAL(triggered()), this, SLOT(playAnimation()));

	 //menus for CSA User scenario
     //m_actUserScenarioCSA1TopologyLoad = new QAction(tr("&Load Topology for CSA1"), this);
     //m_actLoadTopology->setShortcuts(QKeySequence::Open);
     //m_actUserScenarioCSA1TopologyLoad->setStatusTip(tr("Load CSA1 Defined Topology"));
     //connect(m_actUserScenarioCSA1TopologyLoad, SIGNAL(triggered()), this, SLOT(loadUserScenarioCSA1Topology()));
	//playing
      //m_actUserScenarioCSA1 = new QAction(tr("&Play Use Scenario CSA1"), this);
     //m_actLoadTopology->setShortcuts(QKeySequence::Open);
     //m_actUserScenarioCSA1->setStatusTip(tr("Play CSA1 Scenario"));
     //connect(m_actUserScenarioCSA1, SIGNAL(triggered()), this, SLOT(playUserScenarioCSA1()));
	
	 //from scene file
     //m_actUserScenarioBasedOnSelect = new QAction(tr("&Load Topology From Selected"), this);
     //m_actLoadTopology->setShortcuts(QKeySequence::Open);
     //m_actUserScenarioBasedOnSelect->setStatusTip(tr("Load Topology From Selected"));
     //connect(m_actUserScenarioBasedOnSelect, SIGNAL(triggered()), this, SLOT(loadUserScenarioCSASel()));
	
     //m_actPlayUserScenarioBasedOnSelect= new QAction(tr("&Play Scenario From Selected"), this);
     //m_actLoadTopology->setShortcuts(QKeySequence::Open);
     //m_actPlayUserScenarioBasedOnSelect->setStatusTip(tr("Play Scenario From Selected"));
     //connect(m_actPlayUserScenarioBasedOnSelect, SIGNAL(triggered()), this, SLOT(playUserScenarioCSASel()));

    //clear all
     m_actConnectElements = new QAction(tr("&Connect Boiler,Turbine,Generator Plus Control"), this);
    //m_actLoadTopology->setShortcuts(QKeySequence::Open);
    m_actConnectElements->setStatusTip(tr("Connect BTG"));
    connect(m_actConnectElements, SIGNAL(triggered()), this, SLOT(connectBTG()));


    //clear all
	  m_actClearAll = new QAction(tr("&Clear All"), this);
     //m_actLoadTopology->setShortcuts(QKeySequence::Open);
     m_actClearAll->setStatusTip(tr("Clear Scenarios"));
     connect(m_actClearAll, SIGNAL(triggered()), this, SLOT(clearAll()));
	
	 	 //clear all
	  m_actOpenScenarioFile = new QAction(tr("&Open Scenario File"), this);
     //m_actLoadTopology->setShortcuts(QKeySequence::Open);
     m_actOpenScenarioFile->setStatusTip(tr("Open Scenarios"));
     connect(m_actOpenScenarioFile, SIGNAL(triggered()), this, SLOT(openSceneFile()));
	 //Play scene file
	 m_actPlayScenarioFile = new QAction(tr("&Play Scenario File"), this);
     //m_actLoadTopology->setShortcuts(QKeySequence::Open);
     m_actPlayScenarioFile->setStatusTip(tr("Play Scenario"));
     connect(m_actPlayScenarioFile, SIGNAL(triggered()), this, SLOT(playCurrentScenario()));

     //ZoomPlus
     m_actZoomPlus = new QAction(tr("Zoom Plus"), this);
     m_actZoomPlus->setStatusTip(tr("Zoom+"));
     connect(m_actZoomPlus, SIGNAL(triggered()), this->m_graphicsView, SLOT(zoomPlusScene() ));

     //ZoomMinus
     m_actZoomMinus = new QAction(tr("Zoom Minus"), this);
     m_actZoomMinus->setStatusTip(tr("Zoom-"));
     connect(m_actZoomMinus, SIGNAL(triggered()), this->m_graphicsView, SLOT(zoomMinusScene()));

	 //connections
	 this->m_Connections= QList<ConnectorGraphicitem*>();
}


void AutomationElementsView::connectBTG()
{
    BOMInstance* boiler;
    BOMInstance* turbine;
    BOMInstance* generator;
    BOMInstance* controldev;
    boiler= findInstance("BOILER", 1);
    generator= findInstance("GENERATOR", 1);
    turbine= findInstance("TURBINE", 1);
    controldev=findInstance("CONTROL_DEVICE", 1);

    //from boiler to turbine
    if (boiler!=NULL && turbine!=NULL)
    {
    ConnectorGraphicitem* itemConToTurbine;
    itemConToTurbine=this->m_BOMInstanceCreator->createConnector(boiler->boundingRect().topRight().x()-70,boiler->boundingRect().center().y(),turbine->boundingRect().topLeft().x(),boiler->boundingRect().center().y(),"Steam flow");
    this->m_graphicsScene->addItem(itemConToTurbine);
    }
    //from turbine to generator
    if (generator!=NULL && turbine!=NULL)
    {

    ConnectorGraphicitem* itemConFromTurbine;
    itemConFromTurbine=this->m_BOMInstanceCreator->createConnector(turbine->boundingRect().topRight().x()-40,turbine->boundingRect().center().y(),generator->boundingRect().topLeft().x(),turbine->boundingRect().center().y(),"Power");
    this->m_graphicsScene->addItem(itemConFromTurbine);
    }

    //from turbine to generator
    if (boiler!=NULL && controldev!=NULL)
    {

    ConnectorGraphicitem* itemConBoilerToDev;
    itemConBoilerToDev=this->m_BOMInstanceCreator->createConnector(boiler->boundingRect().bottomRight().x()-40,boiler->boundingRect().bottomRight().y()+10,controldev->boundingRect().topLeft().x(),boiler->boundingRect().bottomRight().y()+10,"Signal flow");
    this->m_graphicsScene->addItem(itemConBoilerToDev);
    }

}

void AutomationElementsView::playCurrentScenario()
{

	QSequentialAnimationGroup *animation1SubGroup = new QSequentialAnimationGroup;
    bool isCallout=false;

	foreach(SceneAction* action, this->m_currentSceneActions)
	{
		    Animation* messageAnim;
			QGraphicsItem* itemToAdd;
            if (action->getObjectType()==1)
			{
                m_itemSecond= this->m_BOMInstanceCreator->createMessagePacketTxt(QPoint(0,0),action->gettextTite());

            } else if (action->getObjectType()==2)
            {
                m_itemSecond= this->m_BOMInstanceCreator->createSignalWithText(QPoint(0,0),action->gettextTite());
            }
            else if (action->getObjectType()==3)
            {
                m_itemSecond= this->m_BOMInstanceCreator->createHeatSteamTransferWithText(QPoint(0,0),action->gettextTite());
            }
            else if (action->getObjectType()==4)
            {
                m_itemSecond= this->m_BOMInstanceCreator->createCallOutGraphicItemWithText(QPoint(0,0),action->gettextTite());
                isCallout=true;
            }

            else if (action->getObjectType()==5)
            {
                m_itemSecond= this->m_BOMInstanceCreator->createGenericGraphicItemWithText(QPoint(0,0),action->gettextTite(),"callout.png");
            }

			messageAnim= new Animation(m_itemSecond,"pos");
            if (action->getObjectType()==1)
            {
                this->m_graphicsScene->addItem(((msgGraphicsItemWithText*) m_itemSecond));
            } else if (action->getObjectType()==2)
            {
                this->m_graphicsScene->addItem(((signalGraphicsItemWithText*) m_itemSecond));
            }
            else if (action->getObjectType()==3)
            {
                 this->m_graphicsScene->addItem(((steamGraphicsItemWithText*) m_itemSecond));
            }
            else if (action->getObjectType()==4)
            {
                 this->m_graphicsScene->addItem(((calloutGraphicsItem*) m_itemSecond));
            }
            else if (action->getObjectType()==5)
            {
                 this->m_graphicsScene->addItem(((genericGraphicsItemWithText*) m_itemSecond));
            }

            //QMessageBox msg;
            //msg.setText("Reached here");
            //msg.exec();

            QStringList sourceNameInst=action->getSourceName().split(".");
			BOMInstance* inst= findInstance(sourceNameInst.at(0), sourceNameInst.at(1).toInt());
            QPointF startPoint;
            if (isCallout)
            {
             startPoint=inst->GetBoundingRect().topRight();
             startPoint.setY(startPoint.y()-60);
             startPoint.setX(startPoint.x()+40);
            } else
            {
             startPoint=inst->GetCenterPosition();
            }
            messageAnim->setStartValue(startPoint);//inst->GetCenterPosition());
            //messageAnim->setStartValue(inst->GetPosition());
            //messageAnim->setDuration(1000);
			QStringList destNameInst=action->getDestName().split(".");
			BOMInstance* inst2= findInstance(destNameInst.at(0), destNameInst.at(1).toInt());
            QPointF endPoint;
            if (isCallout)
            {
            endPoint=inst2->GetBoundingRect().topLeft();
            endPoint.setY(endPoint.y()-60);
            endPoint.setX(endPoint.x()-40);
            } else
            {
                endPoint=inst2->GetCenterPosition();
            }
            messageAnim->setEndValue(endPoint);//inst2->GetCenterPosition());
			animation1SubGroup->addAnimation(messageAnim);
			animation1SubGroup->addPause(action->getwaitTimeBeforeNext());
			animation1SubGroup->setLoopCount(action->getNoofTimesToRepeat());
			//build the path...
            //}
            animation1SubGroup->start();
	}
    //animation1SubGroup->start();
}
void AutomationElementsView::openSceneFile()
{
	QString selfilter = tr("XML (*.xml)");
    QString fileName = QFileDialog::getOpenFileName(this,"Open Scene File","C:",  tr("XML Scenaio files (*.xml)" ), &selfilter );
	ReadScenario(fileName);

}

BOMInstance* AutomationElementsView::findInstance(QString name,int instNo)
{
	foreach(BOMInstance* inst, this->m_BOMInstancesList)
	{
		if (inst->GetContainedBOMType()->GetModelIdentification()->GetName()==name && inst->GetInstanceNumber()==instNo)
		{
			return inst;
		}
	}
}
void AutomationElementsView::clearAll()
{
	this->m_Connections.clear();
	this->m_graphicsScene->clear();
	
}

void AutomationElementsView::ReadScenario(QString fileName)
{
	ScenarioReader* reader1=new ScenarioReader(fileName);
		reader1->SetDirectory("C:/");
        reader1->ReadDefintions();
        QList<SceneItem*> topology;
		topology= reader1->GetSceneTopology();
		this->m_currentSceneItems=topology;
		//QList<SceneAction*> actions=reader1->GetActionSequence();
		this->m_currentSceneActions=reader1->GetActionSequence();
		QList<ComAction*> comactions=reader1->GetComActions();
		BOMInstance* combusInst;
	this->m_BOMInstancesList=  QList<BOMInstance*>();
	foreach(SceneItem* item,topology)
	{
		QString identifier=item->getIdentifier();
		QStringList idParts=identifier.split(".");
		QString bomTypeName;
		bomTypeName= idParts.at(0);
		int instNo=idParts.at(1).toInt();
		BOMObject* bomType= this->m_BOMTypeLoader->FindBOMType( bomTypeName);
		BOMInstance* instToCreate;
		instToCreate=this->m_BOMInstanceCreator->createBOMInstance(bomType,item->getPosition().x(),item->getPosition().y(),"");
		instToCreate->setInstanceNumber(instNo);
		this->m_graphicsScene->addItem(instToCreate);
		this->m_BOMInstancesList.append(instToCreate);
        //if (bomTypeName=="COM_BUS") combusInst=instToCreate;
	}
    //QMessageBox msg;
    //msg.setText(QString::number(topology.count()));
    //msg.exec();
    /*
	if (combusInst!=NULL)
	{
	foreach(BOMInstance* inst,this->m_BOMInstancesList)
	{ 
		if (inst!=combusInst)
		{
		ConnectorGraphicitem* itemConEng=this->m_BOMInstanceCreator->createConnector(inst->boundingRect().center().x()-40,combusInst->boundingRect().center().y()+10,inst->boundingRect().center().x()-40,inst->boundingRect().bottomRight().y(),"EL-CTRLHARM");
		this->m_graphicsScene->addItem(itemConEng);
		this->m_Connections.append(itemConEng);
		}
	}
    }*/

}



AutomationElementsView::~AutomationElementsView()
{

}


void AutomationElementsView::LoadPlugins()
{
	//loading BOMLibrary
	//QPluginLoader loaderType("C:\\Abhilash\\MyToolBox\\SystemsExplorer\\Win32\\Release\\BOMLibrary.dll");
	//for debug mode enable this below and comment above

	//QPluginLoader loaderType("C:\\Abhilash\\MyToolBox\\SystemsExplorer\\Win32\\Debug\\BOMLibrary.dll");
    QString pluginPath=QDir::currentPath()  ;
	QPluginLoader loaderType( pluginPath+ "\\BOMLibrary.dll");
    QObject *pluginType = loaderType.instance();
	QString error=loaderType.errorString();
	if (pluginType) this->m_BOMTypeLoader=qobject_cast<IBOMTypeLoadInterface*> (pluginType);
	//loading BOmGraphicalLibrary
	//QPluginLoader loaderInst("C:\\Abhilash\\MyToolBox\\SystemsExplorer\\Win32\\Release\\BOMGraphicalLibrary.dll");
	//for debug mode enable this below and comment above
	//QPluginLoader loaderInst("C:\\Abhilash\\MyToolBox\\SystemsExplorer\\Win32\\Debug\\BOMGraphicalLibrary.dll");
	QPluginLoader loaderInst(pluginPath + "\\BOMGraphicalLibrary.dll");
	QObject *pluginInst = loaderInst.instance();
	QString insterror=loaderInst.errorString();
	if (pluginInst) this->m_BOMInstanceCreator=qobject_cast<IBOMInstanceCreation*> (pluginInst);

}

ConnectorGraphicitem* AutomationElementsView:: findConnection(QString connectIdentifer)
{
	
	foreach(ConnectorGraphicitem* conntr,this->m_Connections)
	{
		if (conntr->getIdentifier() ==connectIdentifer)
		{
			
			return conntr;
		}
	}
	
}
