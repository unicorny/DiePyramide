#include "Level.h"
#include "SpriteManager.h"

Level::Level(const char* levelXml)
: mLevelTimer(0.0f), mLevelXMLName(levelXml)
{
     
}

Level::~Level()
{
    for(std::map<DHASH, KI*>::iterator it = mKIMap.begin(); it != mKIMap.end(); it++)
        KI::destroyKI(it->second);
    mKIMap.clear();

    for(std::list<Entity*>::iterator it = mActiveEntitys.begin(); it != mActiveEntitys.end(); it++)
        DR_SAVE_DELETE(*it);
    mActiveEntitys.clear();

    for(std::list<Entity*>::iterator it = mEntitys.begin(); it != mEntitys.end(); it++)
        DR_SAVE_DELETE(*it);
    mEntitys.clear();
}

int Level::load()
{
    //load xml file
    tinyxml2::XMLDocument doc;
    const char* f = mLevelXMLName.data();
    if(doc.LoadFile(f))
    {
        LOG_XML_WARNING(doc.GetErrorStr1(), f);
        LOG_XML_WARNING(doc.GetErrorStr2(), f);
    }
    

	// Structure of the XML file:
	// - Element "level"      the root Element, which is the 
	//                       FirstChildElement of the Document
	// - - Element "background"   child of the root level Element
	// - - - Text            child of the background Element
	
	// Text is just another Node to TinyXML-2. The more
	// general way to get to the XMLText:
    tinyxml2::XMLElement* root = doc.FirstChildElement( "level" );
    if(!root) LOG_XML_ERROR("root element 'level' didn't exist", f, -1);
    tinyxml2::XMLElement* background = root->FirstChildElement("background");
    if(background)
    {
        const char* text = background->GetText();
        if(!text) LOG_XML_ERROR("background element didn't contain text", f, -1);

        mBackgroundImage = DRTextureManager::Instance().getTexture(text, true);
    }
    else
        LOG_XML_WARNING("level has no background element", f);

    // read in KI types
    tinyxml2::XMLElement* KIs = root->FirstChildElement("KIs");
    if(!KIs) LOG_XML_ERROR("no KIs found", f, -1);
    tinyxml2::XMLElement* currentKI = KIs->FirstChildElement("KI");
    while(currentKI)
    {
        const char* KIName = currentKI->Attribute("name");
        DHASH id = DRMakeStringHash(KIName);
        if(mKIMap.find(id) != mKIMap.end())
            LOG_ERROR("KI doublette in xml", -2);
        KI* newKI = KI::createKI(currentKI, f);
        mKIMap.insert(KI_MAP_PAIR(id, newKI));
        currentKI = currentKI->NextSiblingElement();
    }

    //read in Entitys
    tinyxml2::XMLElement* entitys = root->FirstChildElement("entitys");
    if(!entitys) LOG_XML_ERROR("no entitys found", f, DR_ERROR);
    tinyxml2::XMLElement* currentEntity = entitys->FirstChildElement("entity");
    while(currentEntity)
    {
        const char* KIName = currentEntity->Attribute("KI");
        DHASH id = DRMakeStringHash(KIName);
        if(mKIMap.find(id) == mKIMap.end())
            LOG_ERROR("KI didn't exist", -2);

        Entity* newEntity = new Entity(currentEntity, mKIMap[id]);
        if(newEntity->isActive()) mActiveEntitys.push_back(newEntity);
        else mEntitys.push_back(newEntity);

        currentEntity = currentEntity->NextSiblingElement();
    }
    mEntitys.sort();

    return 0;
}

DRReturn Level::move(float fTime)
{
    mLevelTimer += fTime;
    for(std::list<Entity*>::iterator it = mActiveEntitys.begin(); it != mActiveEntitys.end(); it++)
        (*it)->move(fTime);
    return DR_OK;
}

DRReturn Level::render(float fTime)
{
    // background
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    mBackgroundImage->bind();
    glColor3f(1.0f, 1.0f, 1.0f);
    SpriteManager::Instance().renderSprite();

    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_MODELVIEW);
    for(std::list<Entity*>::iterator it = mActiveEntitys.begin(); it != mActiveEntitys.end(); ++it)
        (*it)->render();

    return DR_OK;
}
