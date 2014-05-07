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
	 //removed now -menu.addAction(m_actAllocation);
     menu.exec(event->globalPos());
 }

void AutomationElementsView::setupWidgets()
{
	QFrame *frame = new QFrame;
	QHBoxLayout *frameLayout = new QHBoxLayout(frame);
	this->m_graphicsView = new QGraphicsView(this); 
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


	foreach(SceneAction* action, this->m_currentSceneActions)
	{
		    Animation* messageAnim;
			QGraphicsItem* itemToAdd;
            if (action->getObjectType()==1)
			{
                m_itemSecond= this->m_BOMInstanceCreator->createMessagePacketTxt(QPoint(0,0),"Test");

            } else if (action->getObjectType()==2)
            {
                m_itemSecond= this->m_BOMInstanceCreator->createSignalWithText(QPoint(0,0),"Signal");
            }
            else if (action->getObjectType()==3)
            {
                m_itemSecond= this->m_BOMInstanceCreator->createHeatSteamTransferWithText(QPoint(0,0),"HTSteam");
            }
            else if (action->getObjectType()==4)
            {
                m_itemSecond= this->m_BOMInstanceCreator->createGenericGraphicItemWithText(QPoint(0,0),"HTSteam","callout.png");
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
                 this->m_graphicsScene->addItem(((genericGraphicsItemWithText*) m_itemSecond));
            }
            //QMessageBox msg;
            //msg.setText("Reached here");
            //msg.exec();

            QStringList sourceNameInst=action->getSourceName().split(".");
			BOMInstance* inst= findInstance(sourceNameInst.at(0), sourceNameInst.at(1).toInt());
			messageAnim->setStartValue(inst->GetCenterPosition());
			//messageAnim->setDuration(1000);
			QStringList destNameInst=action->getDestName().split(".");
			BOMInstance* inst2= findInstance(destNameInst.at(0), destNameInst.at(1).toInt());
            messageAnim->setEndValue(inst2->GetCenterPosition());
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
/*void AutomationElementsView::playUserScenarioCSASel()
{
	QSequentialAnimationGroup *animation1SubGroup = new QSequentialAnimationGroup;


	foreach(SceneAction* action, this->m_currentSceneActions)
	{
		    Animation* messageAnim;
			QGraphicsItem* itemToAdd;
			//if (action->getObjectType()==1)
			{
			m_itemSecond= this->m_BOMInstanceCreator->createMessagePacketTxt(QPoint(0,0),"Test"); 
			
			messageAnim= new Animation(m_itemSecond,"pos");
			this->m_graphicsScene->addItem(m_itemSecond);
			QStringList sourceNameInst=action->getSourceName().split(".");
			BOMInstance* inst= findInstance(sourceNameInst.at(0), sourceNameInst.at(1).toInt());
			messageAnim->setStartValue(inst->GetCenterPosition());
			//messageAnim->setDuration(1000);
			QStringList destNameInst=action->getDestName().split(".");
			BOMInstance* inst2= findInstance(destNameInst.at(0), destNameInst.at(1).toInt());
			messageAnim->setEndValue(inst2->GetCenterPosition());
			animation1SubGroup->addAnimation(messageAnim);
			animation1SubGroup->addPause(action->getwaitTimeBeforeNext());
			animation1SubGroup->setLoopCount(action->getNoofTimesToRepeat());
			//build the path...
			}
	}
	animation1SubGroup->start();
}*/

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
//based on loaded scenario
/*
void AutomationElementsView::loadUserScenarioCSASel()
{

	//loading scene
	QDir dir("C:\\Abhilash\\MyToolBox\\SystemsExplorer\\SystemsExplorer\\Scenarios/");

    QStringList filters("*.xml");
    QFileInfoList fileList= dir.entryInfoList(filters);
	QList<SceneItem*> topology;
    foreach(QFileInfo devfileInfo, fileList)
    {
        ScenarioReader* reader1=new ScenarioReader(devfileInfo.fileName());
		reader1->SetDirectory("C:\\Abhilash\\MyToolBox\\SystemsExplorer\\SystemsExplorer\\Scenarios/");
        reader1->ReadDefintions();
        topology= reader1->GetSceneTopology();
		this->m_currentSceneItems=topology;
		//QList<SceneAction*> actions=reader1->GetActionSequence();
		this->m_currentSceneActions=reader1->GetActionSequence();
		QList<ComAction*> comactions=reader1->GetComActions();
		
	}
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
		this->m_graphicsScene->addItem(instToCreate);
		this->m_BOMInstancesList.append(instToCreate);
		if (bomTypeName=="COM_BUS") combusInst=instToCreate;
	}
	foreach(BOMInstance* inst,this->m_BOMInstancesList)
	{ 
		if (inst!=combusInst)
		{
		ConnectorGraphicitem* itemConEng=this->m_BOMInstanceCreator->createConnector(inst->boundingRect().center().x()-40,combusInst->boundingRect().center().y()+10,inst->boundingRect().center().x()-40,inst->boundingRect().bottomRight().y(),"EL-CTRLHARM");
		this->m_graphicsScene->addItem(itemConEng);
		this->m_Connections.append(itemConEng);
		}
	}
	 
	
}

//CSA1

void AutomationElementsView::loadUserScenarioCSA1Topology()
{
	//user
	BOMObject* bomTypeSPlusOPerator= this->m_BOMTypeLoader->FindBOMType("PlantOperator");
	BOMInstance* instBOMPPOPER; 
	instBOMPPOPER=this->m_BOMInstanceCreator->createBOMInstance(bomTypeSPlusOPerator,-240,30,"SPlus User");
	this->m_graphicsScene->addItem(instBOMPPOPER);

	//engg
	BOMObject* bomTypeSPlusEng= this->m_BOMTypeLoader->FindBOMType("ENGG-SPLUS");
	BOMInstance* instBOMENG; 
	instBOMENG=this->m_BOMInstanceCreator->createBOMInstance(bomTypeSPlusEng,-20,10,"SPlus Engineering WS");
	this->m_graphicsScene->addItem(instBOMENG);


	BOMObject* bomTypeSPlusHist= this->m_BOMTypeLoader->FindBOMType("HIST-SPLUS");
	BOMInstance* instBOMHIST; 
	instBOMHIST=this->m_BOMInstanceCreator->createBOMInstance(bomTypeSPlusHist,80,80,"SPlus Historian");
	this->m_graphicsScene->addItem(instBOMHIST);

	BOMObject* bomTypeSPlusOPer= this->m_BOMTypeLoader->FindBOMType("OPER-SPLUS");
	BOMInstance* instBOMOPER; 
	instBOMOPER=this->m_BOMInstanceCreator->createBOMInstance(bomTypeSPlusOPer,200,20,"SPlus Operations Server 1");
	this->m_graphicsScene->addItem(instBOMOPER);

	BOMInstance* instBOMOPERCL; 
	instBOMOPERCL=this->m_BOMInstanceCreator->createBOMInstance(bomTypeSPlusOPer,400,80,"SPlus Operations Client");
	this->m_graphicsScene->addItem(instBOMOPERCL);

	QGraphicsTextItem* highLight; 
	highLight=this->m_BOMInstanceCreator->createHighLightedText(QPoint(500,50),"LogSender");
	this->m_graphicsScene->addItem(highLight);


	BOMInstance* instBOMOPERServer2; 
	instBOMOPERServer2=this->m_BOMInstanceCreator->createBOMInstance(bomTypeSPlusOPer,640,20,"SPlus Operations Server2");
	this->m_graphicsScene->addItem(instBOMOPERServer2);


	BOMObject* bomTypeSPlusHAR= this->m_BOMTypeLoader->FindBOMType("HPC800");
	BOMInstance* instBOMHAR; 
	instBOMHAR=this->m_BOMInstanceCreator->createBOMInstance(bomTypeSPlusHAR,50,300,"SPlus Controller");
	this->m_graphicsScene->addItem(instBOMHAR);

	BOMObject* bomTypePM877= this->m_BOMTypeLoader->FindBOMType("PM877");
	BOMInstance* instBOMREF; 
	instBOMREF=this->m_BOMInstanceCreator->createBOMInstance(bomTypePM877,350,300,"Melody Controller");
	this->m_graphicsScene->addItem(instBOMREF);

	BOMObject* bomCOMBUS= this->m_BOMTypeLoader->FindBOMType("COM_BUS");
	BOMInstance* instBOMBUS; 
	instBOMBUS=this->m_BOMInstanceCreator->createBOMInstance(bomCOMBUS,-30,200,"Ethernet Bus 100 MBps");
	this->m_graphicsScene->addItem(instBOMBUS);
	
	//connector to controller from Main com bus
	ConnectorGraphicitem* itemConEng=this->m_BOMInstanceCreator->createConnector(20,205,20,260,"EL-CTRLHARM");
	this->m_graphicsScene->addItem(itemConEng);
	this->m_Connections.append(itemConEng);

	//connector to engg
	//ConnectorGraphicitem* itemCon=this->m_BOMInstanceCreator->createConnector(-15,200,-15,70,"EL-ENGG");
	//using relative points
	ConnectorGraphicitem* itemCon=this->m_BOMInstanceCreator->createConnector(-15,200,-15,instBOMENG->boundingRect().bottom(),"EL-ENGG");
	this->m_graphicsScene->addItem(itemCon);
	this->m_Connections.append(itemCon);

		//connector to Hist
	ConnectorGraphicitem* itemConHist=this->m_BOMInstanceCreator->createConnector(instBOMHIST->boundingRect().left()+30,200,instBOMHIST->boundingRect().left()+30,instBOMHIST->boundingRect().bottom(),"EL-HIST");
	this->m_graphicsScene->addItem(itemConHist);
	this->m_Connections.append(itemConHist);


	//connector to Ctrol
	ConnectorGraphicitem* itemConCtrl=this->m_BOMInstanceCreator->createConnector(340,205,340,260,"EL-CTRLMEL");
	this->m_graphicsScene->addItem(itemConCtrl);
	this->m_Connections.append(itemConCtrl);

	//connector to operations
	ConnectorGraphicitem* itemConOps=this->m_BOMInstanceCreator->createConnector(200,200,200,instBOMOPER->boundingRect().bottom(),"EL-OPSVR1");
	this->m_graphicsScene->addItem(itemConOps);
	this->m_Connections.append(itemConOps);
	
	//connector to operations
	ConnectorGraphicitem* itemConOpsCl=this->m_BOMInstanceCreator->createConnector(400,200,400,instBOMOPERCL->boundingRect().bottom(),"EL-OPCL1");
	this->m_graphicsScene->addItem(itemConOpsCl);
	this->m_Connections.append(itemConOpsCl);
	
	//connector to operationsServer 2
	ConnectorGraphicitem* itemConOpsSvr=this->m_BOMInstanceCreator->createConnector(640,200,640,instBOMOPERServer2->boundingRect().bottom(),"EL-OPSVR2");
	this->m_graphicsScene->addItem(itemConOpsSvr);
	this->m_Connections.append(itemConOpsSvr);
	
	


}*/

/*
void AutomationElementsView::playUserScenarioCSA1()
{
	/*ConnectorGraphicitem* connectFromOpClient= findConnection("EL-OPCL1");
	m_item= this->m_BOMInstanceCreator->createMessagePacket(QPoint(0,0));
    this->m_graphicsScene->addItem(m_item);
    m_anim = new Animation(m_item, "pos");
    m_anim->setEasingCurve(QEasingCurve::Linear);

	startCSAAnimation();
}
    */

AutomationElementsView::~AutomationElementsView()
{

}
/*
void AutomationElementsView::playAnimation()
{
	/*
	QIcon icon1 =QIcon(":/Icons/Resources/msgpacket.ico");
    QPixmap pixMap= icon1.pixmap(QSize(32, 32),QIcon::Normal, QIcon::On);
    m_item= new PixmapItem(pixMap);
	*/
	/*m_item= this->m_BOMInstanceCreator->createMessagePacket(QPoint(0,0));
    this->m_graphicsScene->addItem(m_item);
    m_anim = new Animation(m_item, "pos");
    m_anim->setEasingCurve(QEasingCurve::Linear);
    startAnimation();
}

void AutomationElementsView::startCSAAnimation()

{

	QSequentialAnimationGroup *animation1SubGroup = new QSequentialAnimationGroup;
    Animation* messageAnim;
		//animation1SubGroup->addPause(1000);
	   
		Animation* actSignalAnim;
		m_item= this->m_BOMInstanceCreator->createActionSignal(QPoint(100,100)); 
		this->m_graphicsScene->addItem(m_item);
		actSignalAnim = new Animation(m_item, "pos");
		actSignalAnim->setStartValue(QPoint(-210,30));//connectGraphItem->getBeginPoint());
        actSignalAnim->setEndValue(QPoint(330,30));//connectGraphItem->getEndPoint());
        actSignalAnim->setLoopCount(2);
		animation1SubGroup->addAnimation(actSignalAnim);
		
		//Animation fading. Test
		QPropertyAnimation *propAnimationFade;
		propAnimationFade  = new QPropertyAnimation(m_item, "opacity");
		propAnimationFade->setDuration(10);
		propAnimationFade->setStartValue(1.0);
		propAnimationFade->setEndValue(0.0);
		animation1SubGroup->addAnimation(propAnimationFade);
		
		//for communication to one Server
		//pause for a while
        animation1SubGroup->addPause(3000);
		//actSignalAnim->stop();
		ConnectorGraphicitem* connectFromOpClient= findConnection("EL-OPCL1");
    	QPointF pointStart=connectFromOpClient->getEndPoint();
		QPointF pointEnd=connectFromOpClient->getBeginPoint();
        
		m_itemSecond= this->m_BOMInstanceCreator->createMessagePacketTxt(QPoint(0,0),"SysLog"); //new PixmapItem(pixMap);
        this->m_graphicsScene->addItem(m_itemSecond);
		//m_itemSecond->setVisible(false);
        messageAnim = new Animation(m_itemSecond, "pos");
		
		messageAnim->setStartValue(pointStart);//connectGraphItem->getBeginPoint());
        messageAnim->setEndValue(pointEnd);//connectGraphItem->getEndPoint());
        messageAnim->setLoopCount(3);

        animation1SubGroup->addAnimation(messageAnim);
		//pause for a while
        animation1SubGroup->addPause(1000);

        Animation* messageAnim1;
		
		messageAnim1 = new Animation(m_itemSecond, "pos");
		
		ConnectorGraphicitem* connectFromOpSvr= findConnection("EL-OPSVR1");
    	QPointF pointStart1=connectFromOpSvr->getBeginPoint();
		QPointF pointEnd1=connectFromOpSvr->getEndPoint();
        messageAnim1->setStartValue(pointStart1);//connectGraphItem->getBeginPoint());
        messageAnim1->setEndValue(pointEnd1);//connectGraphItem->getEndPoint());
        messageAnim1->setLoopCount(3);
		animation1SubGroup->addAnimation(messageAnim1);
		//m_itemSecond->setVisible(true);

		//to redundant server
		animation1SubGroup->addPause(1000);

		Animation* messageAnim2;
		
		messageAnim2 = new Animation(m_itemSecond, "pos");
		
		ConnectorGraphicitem* connectFromOpSvr2= findConnection("EL-OPSVR2");
    	QPointF pointStart2=connectFromOpSvr2->getBeginPoint();
		QPointF pointEnd2=connectFromOpSvr2->getEndPoint();
        messageAnim2->setStartValue(pointStart2);//connectGraphItem->getBeginPoint());
        messageAnim2->setEndValue(pointEnd2);//connectGraphItem->getEndPoint());
        messageAnim2->setLoopCount(3);
		animation1SubGroup->addAnimation(messageAnim2);
		


    animation1SubGroup->start();

}
void AutomationElementsView::performLoadTopology()
{
	this->CreateBOMGraphics();
}
void AutomationElementsView::CreateBOMGraphics()
{
	//this->m_BOMTypeLoader->LoadDefinitions("C:\\Abhilash\\MyToolBox\\SystemsExplorer\\SystemsExplorer\\AutomationModelElements");
	//add Engineering
	BOMObject* bomTypeSPlusEng= this->m_BOMTypeLoader->FindBOMType("ENGG-SPLUS");
	BOMInstance* instBOMENG; 
	instBOMENG=this->m_BOMInstanceCreator->createBOMInstance(bomTypeSPlusEng,20,50,"SPlus Engineering Server");
	this->m_graphicsScene->addItem(instBOMENG);

	BOMObject* bomTypeSPlusOPer= this->m_BOMTypeLoader->FindBOMType("OPER-SPLUS");
	BOMInstance* instBOMOPER; 
	instBOMOPER=this->m_BOMInstanceCreator->createBOMInstance(bomTypeSPlusOPer,340,50,"SPlus Operations");
	this->m_graphicsScene->addItem(instBOMOPER);

	BOMObject* bomTypeSPlusHAR= this->m_BOMTypeLoader->FindBOMType("HPC800");
	BOMInstance* instBOMHAR; 
	instBOMHAR=this->m_BOMInstanceCreator->createBOMInstance(bomTypeSPlusHAR,50,300,"SPlus Controller");
	this->m_graphicsScene->addItem(instBOMHAR);

	BOMObject* bomTypeREF630= this->m_BOMTypeLoader->FindBOMType("IED_REF630");
	BOMInstance* instBOMREF; 
	instBOMREF=this->m_BOMInstanceCreator->createBOMInstance(bomTypeREF630,350,300,"REF 630");
	this->m_graphicsScene->addItem(instBOMREF);

	BOMObject* bomCOMBUS= this->m_BOMTypeLoader->FindBOMType("COM_BUS");
	BOMInstance* instBOMBUS; 
	instBOMBUS=this->m_BOMInstanceCreator->createBOMInstance(bomCOMBUS,10,200,"Ethernet Bus 100 MBps");
	this->m_graphicsScene->addItem(instBOMBUS);
	
	//connector to engg
	ConnectorGraphicitem* itemConEng=this->m_BOMInstanceCreator->createConnector(35,205,35,260,"Ethernet Link1");
	this->m_graphicsScene->addItem(itemConEng);
	this->m_Connections.append(itemConEng);
	//connector to Ctrol
	ConnectorGraphicitem* itemConCtrl=this->m_BOMInstanceCreator->createConnector(340,205,340,260,"Ethernet Link2");
	this->m_graphicsScene->addItem(itemConCtrl);
	this->m_Connections.append(itemConCtrl);
	//connector to operations
	ConnectorGraphicitem* itemConOps=this->m_BOMInstanceCreator->createConnector(340,205,340,70,"Ethernet Link3");
	this->m_graphicsScene->addItem(itemConOps);
	this->m_Connections.append(itemConOps);
	//connector to controller
	ConnectorGraphicitem* itemCon=this->m_BOMInstanceCreator->createConnector(25,200,25,70,"Ethernet Link4");
	this->m_graphicsScene->addItem(itemCon);
	this->m_Connections.append(itemCon);
}*/

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
