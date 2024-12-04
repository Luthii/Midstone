#include "ObjectMap.h"

OBJECT_TYPE ObjectMapClass::GetObjectType(std::string str)
{
	// creates a search value that represents the type map find function
	auto search = TypeMap.find(str);

	// if our search finds something before it ends return the assoiciated OBJECT_TYPE value
	if (search != TypeMap.end())
		return search->second;
	else  // else return undefined
		return OBJECT_TYPE::UNDEFINED;
}

bool ObjectMapClass::LoadObjectsMap(std::string fileName)
{
	XMLDocument ObjMapXML;

	if (ObjMapXML.LoadFile(fileName.c_str()) != XML_SUCCESS) {
		std::cerr << "Can't open the xml file: " << fileName.c_str() << "\n";
		return false;
	}

	XMLNode* root = ObjMapXML.FirstChild();
	if (root == NULL) {
		std::cout << "TinyXML2 error: " << tinyxml2::XML_ERROR_FILE_READ_ERROR << std::endl;
		return false;
	}
	std::cout << "Root: " << root->FirstChild()->Value() << std::endl;

	XMLElement* ObjData = root->FirstChildElement("Object");

	Object ObjInfo;

	while (ObjData != nullptr) {
		ObjInfo.number = std::stoi(ObjData->FirstChildElement("id")->GetText()) + 1;
		ObjInfo.type = GetObjectType(ObjData->FirstChildElement("type")->GetText());
		ObjInfo.loot = GetObjectType(ObjData->FirstChildElement("loot")->GetText());
		ObjInfo.lootQuantity = std::stoi(ObjData->FirstChildElement("loot_quantity")->GetText());
		ObjInfo.interactionNumber = std::stoi(ObjData->FirstChildElement("num_interaction")->GetText());
		//collision box
		XMLElement* box = ObjData->FirstChildElement("collision_box");
		ObjInfo.collisionBox.topLeftCorner.x = std::stoi(box->FirstChildElement("top_x")->GetText());
		ObjInfo.collisionBox.topLeftCorner.y = std::stoi(box->FirstChildElement("top_y")->GetText());
		ObjInfo.collisionBox.bottomRightCorner.y = std::stoi(box->FirstChildElement("bottom_x")->GetText());
		ObjInfo.collisionBox.bottomRightCorner.y = std::stoi(box->FirstChildElement("botton_y")->GetText());

		OBJECT_MAP.insert(std::pair<unsigned int, Object>(ObjInfo.number, ObjInfo));

		ObjData = ObjData->NextSiblingElement("Object");
	}

	std::cout << "Object Map Created! \n";

	return true;
}
