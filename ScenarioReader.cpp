#include "ScenarioReader.h"


ScenarioReader::ScenarioReader(QString fileName)
{
    this->filename=fileName;
}

ScenarioReader::~ScenarioReader(void)
{
}

bool ScenarioReader::ReadDefintions()
{
    QString id;
    QString name;
    QString desc;
    this->filename=dir.absoluteFilePath(this->filename);
    this->file.setFileName(this->filename);
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        return false;
    }
    reader.setDevice(&this->file);
	//Read..
    ReadToplogy();
    this->file.close();
    return true;
}

 bool ScenarioReader::SetDirectory(QString directoryName)
{
    QDir direct(directoryName);
    this->dir=direct;
    return true;
}

 bool ScenarioReader::ReadToplogy()
 {


	  while(!reader.atEnd() && !reader.hasError())
    {
        QString id;
        QString name;
        QXmlStreamAttributes attribs;
        QXmlStreamReader::TokenType token = reader.readNext();
        reader.setNamespaceProcessing(true);
        /* If token is just StartDocument, we'll go to next.*/
        if(token == QXmlStreamReader::StartDocument) {
                            continue;
        }
        /* If token is StartElement, we'll see if we can read it.*/
        if(token == QXmlStreamReader::StartElement)
        {
			if (reader.name()=="SceneTopology")
			{

				 reader.readNextStartElement();
				 ReadSceneItems();
			}
			if(reader.name()=="SceneActions")
			{
				 reader.readNextStartElement();
				 ReadActions();	
			}
			if(reader.name()=="ComActions")
			{
				reader.readNextStartElement();
				ReadComActions();
				 
			}
        

		}
	  }
	  return true;
   
 }

 bool ScenarioReader::ReadComActions()
 {
	   m_CommunicationActionsList==QList<ComAction*>();
        while(reader.name()!="ComActions" )// && (!reader.isEndElement())  && (!reader.atEnd()))
        {
            QXmlStreamAttributes attribsArg= reader.attributes();
            QString id;
            QString sourceObj="";
			QString destObj="";
            int type=0; 
			int assocSceneId=0; int repeat=0;
			int waitTime=0;
            if (attribsArg.count()>0 && reader.name()=="ComAction")
            {

            QString arguments="";
            if (attribsArg.hasAttribute("id"))
            {
                id=attribsArg.value("id").toString();
            }
            if (attribsArg.hasAttribute("type"))
            {
                type=attribsArg.value("type").toString().toInt();
            }
            if (attribsArg.hasAttribute("assocsceneactionid"))
            {
                assocSceneId=attribsArg.value("assocsceneactionid").toString().toInt();
            }
			if (attribsArg.hasAttribute("sourceaddress"))
            {
                sourceObj=attribsArg.value("sourceaddress").toString();
            }
			if (attribsArg.hasAttribute("destaddress"))
            {
                destObj=attribsArg.value("destaddress").toString();
            }

			if (attribsArg.hasAttribute("repeat"))
            {
                repeat=attribsArg.value("repeat").toString().toInt();
            }
			if (attribsArg.hasAttribute("timetonext"))
            {
                waitTime=attribsArg.value("timetonext").toString().toInt();
            }
				
            ComAction* comActNew= new ComAction(id,type,assocSceneId,sourceObj,destObj,repeat,waitTime);
			this->m_CommunicationActionsList.append(comActNew);
            
			}
            reader.readNext();

        }
        return true;

 }
bool ScenarioReader::ReadSceneItems()
{
	  m_TopologyItemsList==QList<SceneItem*>();
	    while(reader.name()!="SceneTopology" ) //&& (!reader.isEndElement()) )// && (!reader.atEnd()))
        {
            QXmlStreamAttributes attribsArg= reader.attributes();
            QString id;
            QString nameofType="";
			QString userDefName="";
			QPoint pointPos;
			QString pos;
			QStringList posXY;
		
            int type=0; 
			int order=0; int repeat=0;
			int waitTime=0;
            if (attribsArg.count()>0 && reader.name()=="SceneItem")
            {

            QString arguments="";
            if (attribsArg.hasAttribute("id"))
            {
                id=attribsArg.value("id").toString();
            }
            if (attribsArg.hasAttribute("type"))
            {
                type=attribsArg.value("type").toString().toInt();
            }
            if (attribsArg.hasAttribute("name"))
            {
                nameofType=attribsArg.value("name").toString();
            }
			/*
			if (attribsArg.hasAttribute("userdefname"))
            {
                userDefName=attribsArg.value("userdefname").toString();
            }*/
			if (attribsArg.hasAttribute("pos"))
            {
               pos=attribsArg.value("pos").toString();
			   posXY= pos.split(",");

            }
			
            SceneItem* itemNew= new SceneItem( id,type,nameofType, QPoint(posXY.at(0).toInt(),posXY.at(1).toInt()) );
			m_TopologyItemsList.append(itemNew);
            
			}
            reader.readNext();

        }
      return true;
}

bool ScenarioReader::ReadActions()
{

      m_ActionsList==QList<SceneAction*>();
        while(reader.name()!="SceneActions" )// && (!reader.isEndElement())  && (!reader.atEnd()))
        {
            QXmlStreamAttributes attribsArg= reader.attributes();
            QString id;
            QString sourceObj="";
			QString destObj="";
            int type=0; 
			int order=0; int repeat=0;
			int waitTime=0;
            if (attribsArg.count()>0 && reader.name()=="SceneAction")
            {

            QString arguments="";
            if (attribsArg.hasAttribute("id"))
            {
                id=attribsArg.value("id").toString();
            }
            if (attribsArg.hasAttribute("type"))
            {
                type=attribsArg.value("type").toString().toInt();
            }
            if (attribsArg.hasAttribute("order"))
            {
                order=attribsArg.value("order").toString().toInt();
            }
			if (attribsArg.hasAttribute("source"))
            {
                sourceObj=attribsArg.value("source").toString();
            }
			if (attribsArg.hasAttribute("dest"))
            {
                destObj=attribsArg.value("dest").toString();
            }

			if (attribsArg.hasAttribute("repeat"))
            {
                repeat=attribsArg.value("repeat").toString().toInt();
            }
			if (attribsArg.hasAttribute("waittime"))
            {
                waitTime=attribsArg.value("waittime").toString().toInt();
            }
				
            SceneAction* actionNew= new SceneAction(id,type,order,sourceObj,destObj,repeat,waitTime);
			this->m_ActionsList.append(actionNew);
            
			}
            reader.readNext();

        }
        return true;

}

