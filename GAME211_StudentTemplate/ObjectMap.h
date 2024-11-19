#pragma once

#include <string>
#include <iostream>
#include <map>

#include "tinyxml2.h"

#include "Object.h"

using namespace tinyxml2;

//struct Object {
//	unsigned int number;
//	OBJECT_TYPE type;
//	OBJECT_TYPE loot;
//	unsigned int lootQuantity;
//	unsigned int interactionNumber;
//};
static const Object anvilLeft{5862, OBJECT_TYPE::ANVIL, OBJECT_TYPE::UNDEFINED, 0, 1};
static const Object anvilRight{5863, OBJECT_TYPE::ANVIL, OBJECT_TYPE::UNDEFINED, 0, 1};
static const Object iron{5713, OBJECT_TYPE::IRON, OBJECT_TYPE::IRON_ORE, 3, 9};
static const Object iron_ore{ 5230, OBJECT_TYPE::IRON_ORE, OBJECT_TYPE::UNDEFINED, 0, 2 };


//this is a variable declaration with initialization
static std::map<unsigned int, Object> OBJECT_MAP{
	{anvilLeft.number, anvilLeft},
	{anvilRight.number, anvilRight},
	{iron.number, iron}
};

static OBJECT_TYPE getObjectType(std::string str) {

	// creates a search value that represents the type map find function
	auto search = TypeMap.find(str);

	// if our search finds something before it ends return the assoiciated OBJECT_TYPE value
	if (search != TypeMap.end())
		return search->second;
	else  // else return undefined
		return OBJECT_TYPE::UNDEFINED;
};


static void LoadObjectsMap(std::string fileName) {
	XMLDocument ObjMapXML;

	if (ObjMapXML.LoadFile(fileName.c_str()) != XML_SUCCESS) {
		std::cerr << "Can't open the xml file: " << fileName.c_str() << "\n";
		return;
	}

	XMLNode* root = ObjMapXML.FirstChild();

	XMLElement* ObjData = root->FirstChildElement("Object");

	Object ObjInfo;

	while (ObjData != nullptr) {
		ObjInfo.number = std::stoi(ObjData->FirstChildElement("id")->GetText());
		ObjInfo.type = getObjectType(ObjData->FirstChildElement("type")->GetText());
		ObjInfo.loot = getObjectType(ObjData->FirstChildElement("loot")->GetText());
		ObjInfo.lootQuantity = std::stoi(ObjData->FirstChildElement("loot_quantity")->GetText());
		ObjInfo.interactionNumber = std::stoi(ObjData->FirstChildElement("num_interaction")->GetText());
		//collision box
		XMLElement* box = ObjData->FirstChildElement("collision_box");
		ObjInfo.collisionBox.topLeftCorner.x = std::stoi(box->FirstChildElement("top_x")->GetText());
		ObjInfo.collisionBox.topLeftCorner.y = std::stoi(box->FirstChildElement("top_y")->GetText());
		ObjInfo.collisionBox.bottomRightCorner.y = std::stoi(box->FirstChildElement("bottom_x")->GetText());
		ObjInfo.collisionBox.bottomRightCorner.y = std::stoi(box->FirstChildElement("bottom_y")->GetText());

		OBJECT_MAP.insert(std::pair<unsigned int, Object>(ObjInfo.number, ObjInfo));

		ObjData = ObjData->NextSiblingElement("Animation");
	}
};