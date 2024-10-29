#pragma once

#include <map>
#include "Object.h"

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

static const std::map<unsigned int, Object> OBJECT_MAP{
	{anvilLeft.number, anvilLeft},
	{anvilRight.number, anvilRight},
	{iron.number, iron}
};
