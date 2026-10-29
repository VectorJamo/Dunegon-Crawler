#include "CollisionHandler.h"

bool CollisionHandler::CheckEntityWorldCollision(TileMap* map, Entity* entity, float deltaTime)
{
    switch (entity->GetCurrentDirection())
    {
    case EntityDirection::UP: {
        float newTopLeftX = entity->GetWorldPosition().x + entity->GetEntityCollisionRect().x;
        float newTopLeftY = (entity->GetWorldPosition().y + entity->GetEntityCollisionRect().y) - entity->GetEntitySpeed() * deltaTime;
        float newTopRightX = newTopLeftX + entity->GetEntityCollisionRect().width;
        float newTopRightY = newTopLeftY;

        uint32_t topLeftTileCol = newTopLeftX / 32;
        uint32_t topLeftTileRow = newTopLeftY / 32;
        uint32_t topRightTileCol = newTopRightX / 32;
        uint32_t topRightTileRow = newTopRightY / 32;

        int32_t topLeftTileNum = map->GetMap()[topLeftTileRow][topLeftTileCol];
        int32_t topRightTileNum = map->GetMap()[topRightTileRow][topRightTileCol];

        if ((topLeftTileNum != -1 && map->GetTileFromNumber(topLeftTileNum)->isCollideable) || (topRightTileNum != -1 && map->GetTileFromNumber(topRightTileNum)->isCollideable))
            return true;
        return false;
        break;
    }
    case EntityDirection::DOWN: {
        float newBottomLeftX = entity->GetWorldPosition().x + entity->GetEntityCollisionRect().x;
        float newBottomLeftY = (entity->GetWorldPosition().y + entity->GetEntityCollisionRect().y + entity->GetEntityCollisionRect().height) + entity->GetEntitySpeed() * deltaTime;
        float newBottomRightX = newBottomLeftX + entity->GetEntityCollisionRect().width;
        float newBottomRightY = newBottomLeftY;

        uint32_t bottomLeftTileCol = newBottomLeftX / 32;
        uint32_t bottomLeftTileRow = newBottomLeftY / 32;
        uint32_t bottomRightTileCol = newBottomRightX / 32;
        uint32_t bottomRightTileRow = newBottomRightY / 32;

        int32_t bottomLeftTileNum = map->GetMap()[bottomLeftTileRow][bottomLeftTileCol];
        int32_t bottomRightTileNum = map->GetMap()[bottomRightTileRow][bottomRightTileCol];

        if ((bottomLeftTileNum != -1 && map->GetTileFromNumber(bottomLeftTileNum)->isCollideable) || (bottomRightTileNum != -1 && map->GetTileFromNumber(bottomRightTileNum)->isCollideable))
            return true;
        return false;
        break;
    }    
    case EntityDirection::LEFT: {
        float newTopLeftX = (entity->GetWorldPosition().x + entity->GetEntityCollisionRect().x) - entity->GetEntitySpeed() * deltaTime;
        float newTopLeftY = entity->GetWorldPosition().y + entity->GetEntityCollisionRect().y;
        float newBottomLeftX = newTopLeftX;
        float newBottomLeftY = entity->GetWorldPosition().y + entity->GetEntityCollisionRect().y + entity->GetEntityCollisionRect().height;

        uint32_t topLeftTileCol = newTopLeftX / 32;
        uint32_t topLeftTileRow = newTopLeftY / 32;
        uint32_t bottomLeftTileCol = newBottomLeftX / 32;
        uint32_t bottomLeftTileRow = newBottomLeftY / 32;

        int32_t topLeftTileNum = map->GetMap()[topLeftTileRow][topLeftTileCol];
        int32_t bottomLeftTileNum = map->GetMap()[bottomLeftTileRow][bottomLeftTileCol];


        if ((topLeftTileNum != -1 && map->GetTileFromNumber(topLeftTileNum)->isCollideable) || (bottomLeftTileNum != -1 && map->GetTileFromNumber(bottomLeftTileNum)->isCollideable))
            return true;
        return false;
        break;
    }
    case EntityDirection::RIGHT: {
        float newTopRightX = entity->GetWorldPosition().x + entity->GetEntityCollisionRect().x + entity->GetEntityCollisionRect().width + entity->GetEntitySpeed() * deltaTime;
        float newTopRightY = entity->GetWorldPosition().y + entity->GetEntityCollisionRect().y;
        float newBottomRightX = newTopRightX;
        float newBottomRightY = entity->GetWorldPosition().y + entity->GetEntityCollisionRect().y + entity->GetEntityCollisionRect().height;

        uint32_t topRightTileCol = newTopRightX / 32;
        uint32_t topRightTileRow = newTopRightY / 32;
        uint32_t bottomRightTileCol = newBottomRightX / 32;
        uint32_t bottomRightTileRow = newBottomRightY / 32;

        int32_t topRightTileNum = map->GetMap()[topRightTileRow][topRightTileCol];
        int32_t bottomRightTileNum = map->GetMap()[bottomRightTileRow][bottomRightTileCol];

        if (( topRightTileNum != -1 && map->GetTileFromNumber(topRightTileNum)->isCollideable) || (bottomRightTileNum != -1 && map->GetTileFromNumber(bottomRightTileNum)->isCollideable))
            return true;
        return false;
        break;
    }
    default:
        return false;
    }
}

bool CollisionHandler::CheckEntityCollision(Entity* entity1, Entity* entity2, float deltaTime)
{
    Rect entity1CollisionRect, entity2CollisionRect;
    entity1CollisionRect.x = entity1->GetWorldPosition().x + entity1->GetEntityCollisionRect().x;
    entity1CollisionRect.y = entity1->GetWorldPosition().y + entity1->GetEntityCollisionRect().y;
    entity1CollisionRect.width = entity1->GetEntityCollisionRect().width;
    entity1CollisionRect.height = entity1->GetEntityCollisionRect().height;

    entity2CollisionRect.x = entity2->GetWorldPosition().x + entity2->GetEntityCollisionRect().x;
    entity2CollisionRect.y = entity2->GetWorldPosition().y + entity2->GetEntityCollisionRect().y;
    entity2CollisionRect.width = entity2->GetEntityCollisionRect().width;
    entity2CollisionRect.height = entity2->GetEntityCollisionRect().height;

    // TODO: PERFORMANCE OPTIMIZATION. Only check for collision if the entity is within a certain distance of the another entity


    switch (entity1->GetCurrentDirection())
    {
    case EntityDirection::UP:
        entity1CollisionRect.y -= entity1->GetEntitySpeed() * deltaTime;
        break;
    case EntityDirection::DOWN:
        entity1CollisionRect.y += entity1->GetEntitySpeed() * deltaTime;
        break;
    case EntityDirection::LEFT:
        entity1CollisionRect.x -= entity1->GetEntitySpeed() * deltaTime;
        break;
    case EntityDirection::RIGHT:
        entity1CollisionRect.x += entity1->GetEntitySpeed() * deltaTime;
        break;
    }

    switch (entity2->GetCurrentDirection())
    {
    case EntityDirection::UP:
        entity2CollisionRect.y -= entity1->GetEntitySpeed() * deltaTime;
        break;
    case EntityDirection::DOWN:
        entity2CollisionRect.y += entity1->GetEntitySpeed() * deltaTime;
        break;
    case EntityDirection::LEFT:
        entity2CollisionRect.x -= entity1->GetEntitySpeed() * deltaTime;
        break;
    case EntityDirection::RIGHT:
        entity2CollisionRect.x += entity1->GetEntitySpeed() * deltaTime;
        break;
    }

    if (entity1CollisionRect.x > entity2CollisionRect.x + entity2CollisionRect.width || entity1CollisionRect.x + entity1CollisionRect.width < entity2CollisionRect.x
        || entity1CollisionRect.y > entity2CollisionRect.y + entity2CollisionRect.height || entity1CollisionRect.y + entity1CollisionRect.height < entity2CollisionRect.y)
    {
        return false;
    }

    return true;
}

bool CollisionHandler::CheckEntityObjectCollision(Entity* entity, Object* object, float deltaTime)
{
    Rect entityCollisionRect;
    entityCollisionRect.x = entity->GetWorldPosition().x + entity->GetEntityCollisionRect().x;
    entityCollisionRect.y = entity->GetWorldPosition().y + entity->GetEntityCollisionRect().y;
    entityCollisionRect.width = entity->GetEntityCollisionRect().width;
    entityCollisionRect.height = entity->GetEntityCollisionRect().height;
    
    Rect objectCollisionRect;
    objectCollisionRect.x = object->GetWorldPosition().x;
    objectCollisionRect.y = object->GetWorldPosition().y;
    objectCollisionRect.width = object->GetObjectSprite()->GetSize().x;
    objectCollisionRect.height = object->GetObjectSprite()->GetSize().y;

    // TODO: PERFORMANCE OPTIMIZATION. Only check for collision if the object is within a certain distance of the entity

    switch (entity->GetCurrentDirection())
    {
    case EntityDirection::UP:
        entityCollisionRect.y -= entity->GetEntitySpeed() * deltaTime;
        break;
    case EntityDirection::DOWN:
        entityCollisionRect.y += entity->GetEntitySpeed() * deltaTime;
        break;
    case EntityDirection::LEFT:
        entityCollisionRect.x -= entity->GetEntitySpeed() * deltaTime;
        break;
    case EntityDirection::RIGHT:
        entityCollisionRect.x += entity->GetEntitySpeed() * deltaTime;
        break;
    }

    if (entityCollisionRect.x > objectCollisionRect.x + objectCollisionRect.width || entityCollisionRect.x + entityCollisionRect.width < objectCollisionRect.x
        || entityCollisionRect.y > objectCollisionRect.y + objectCollisionRect.height || entityCollisionRect.y + entityCollisionRect.height < objectCollisionRect.y)
    {
        return false;
    }

    return true;
}
