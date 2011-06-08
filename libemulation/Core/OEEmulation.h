
/**
 * libemulation
 * OEEmulation
 * (C) 2009-2011 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Controls an emulation.
 */

#ifndef _OEEMULATION_H
#define _OEEMULATION_H

#include <vector>

#include "OEEDL.h"
#include "OEComponent.h"
#include "OEDevice.h"

using namespace std;

typedef void (*EmulationDidUpdate)(void *userData);
typedef OEComponent *(*EmulationCreateCanvas)(void *userData, OEComponent *device);
typedef void (*EmulationDestroyCanvas)(void *userData, OEComponent *canvas);

typedef map<string, OEComponent *> OEComponentsMap;

class OEEmulation : public OEComponent, public OEEDL
{
public:
	OEEmulation();
	~OEEmulation();
	
	void setResourcePath(string path);
	void setDidUpdate(EmulationDidUpdate didUpdate);
	void setCreateCanvas(EmulationCreateCanvas createCanvas);
	void setDestroyCanvas(EmulationDestroyCanvas destroyCanvas);
	void setUserData(void *userData);
	
	bool open(string path);
	
	bool addComponent(string id, OEComponent *component);
	bool removeComponent(string id);
	OEComponent *getComponent(string id);
	string getId(OEComponent *component);
	
	bool addEDL(string path, OEIdMap connectionsMap);
	bool removeDevice(string id);
	
	bool isActive();
	
private:
	string resourcePath;
	OEComponentsMap componentsMap;
	
	EmulationDidUpdate didUpdate;
	EmulationCreateCanvas createCanvas;
	EmulationDestroyCanvas destroyCanvas;
	void *userData;
	
	int activityCount;
	
	bool createEmulation();
	bool createDevice(string id);
	bool createComponent(string id, string className);
	bool configureEmulation();
	bool configureDevice(string id,
						 string label, string image, string group,
						 xmlNodePtr children);
	bool configureComponent(string id, xmlNodePtr children);
	bool initEmulation();
	bool initComponent(string id);
	bool updateEmulation();
	bool updateComponent(string id, xmlNodePtr children);
	void disconnectEmulation();
	void disconnectComponent(string id, xmlNodePtr children);
	void destroyEmulation();
	void destroyComponent(string id, xmlNodePtr children);
	
	bool hasValueProperty(string value, string propertyName);
	string parseValueProperties(string value, map<string, string>& propertiesMap);
	
    friend class OEDevice;
};

#endif
