#pragma once

#include <unordered_map>

//third party includes

// DEFINITION OF OBJECT TYPES
enum class OBJECT_TYPE {
	UNDEFINED = 0,
	// SHOP ITEMS
	ANVIL,
	// MINES ITEMS
	IRON,
	IRON_ORE,
};

static std::unordered_map<std::string, OBJECT_TYPE>TypeMap = {
	{"ANVIL", OBJECT_TYPE::ANVIL},
	{"IRON", OBJECT_TYPE::IRON},
	{"IRON_ORE", OBJECT_TYPE::IRON_ORE},
};

//DEFINITION OF THE OBJECT STRUCT
/*
	This structure will be used on ObjectMap.h to define ALL the object elements in the game
*/
struct Object {
	unsigned int number;
	OBJECT_TYPE type;
	OBJECT_TYPE loot;
	unsigned int lootQuantity;
	unsigned int interactionNumber;
	
};

//definition of the struct that will be used to keep track of the objects interacted with on the scene
/*
	This structure should be used in a MAP where the key is a Vec2 and the item is a ObjectScene struct
*/
struct ObjectScene {
	unsigned int numberInteractions;
	unsigned int objNumber;
};


struct ObjectLoot {
	//OBJECT_TYPE lootType;
	unsigned int quatity;
	unsigned int maxQuatity = 10;
};