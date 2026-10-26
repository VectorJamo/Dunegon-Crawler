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
    return false;
}
