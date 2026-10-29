#pragma once
#include "../tilemap/TileMap.h"
#include "../entities/Entity.h"
#include "../objects/Object.h"

class CollisionHandler
{
public:
	static bool CheckEntityWorldCollision(TileMap* map, Entity* entity, float deltaTime);
	static bool CheckEntityCollision(Entity* entity1, Entity* entity2, float deltaTime);
	static bool CheckEntityObjectCollision(Entity* entity, Object* object, float deltaTime);
};

