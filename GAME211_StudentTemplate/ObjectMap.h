#pragma once

#include <string>
#include <iostream>
#include <map>

#include "tinyxml2.h"

#include "Object.h"

using namespace tinyxml2;

class ObjectMapClass {
private:
	std::map<unsigned int, Object> OBJECT_MAP;

	OBJECT_TYPE GetObjectType(std::string str);

	bool LoadObjectsMap(std::string fileName);

public:
	ObjectMapClass() {}
	~ObjectMapClass() {}

	bool OnCreate() {
		return LoadObjectsMap("xml/ObjectMap.xml");
	}

	std::map<unsigned int, Object>::iterator find(unsigned int key) {
		return OBJECT_MAP.find(key);
	}

	std::map<unsigned int, Object>::iterator end() {
		return OBJECT_MAP.end();
	}
	Object& at(unsigned int key) {
		return OBJECT_MAP.at(key);
	}
};