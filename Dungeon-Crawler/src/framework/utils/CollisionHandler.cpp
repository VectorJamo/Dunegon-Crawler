#include "CollisionHandler.h"

bool CollisionHandler::CheckEntityWorldCollision(TileMap* map, Entity* entity, float deltaTime)
{
    switch (entity->GetCurrentDirection())
    {
    case EntityDirection::UP: {
        float newTopLeftX = entity->GetWorldPosition().x;
        float newTopLeftY = entity->GetWorldPosition().y - entity->GetEntitySpeed() * deltaTime;
        float newTopRightX = entity->GetWorldPosition().x + entity->GetEntitySprite()->GetSize().x;
        float newTopRightY = entity->GetWorldPosition().y - entity->GetEntitySpeed() * deltaTime;

        uint32_t topLeftTileCol = newTopLeftX / 32;
        uint32_t topLeftTileRow = newTopLeftY / 32;
        uint32_t topRightTileCol = newTopRightX / 32;
        uint32_t topRightTileRow = newTopRightY / 32;

        if (map->GetMap()[topLeftTileRow][topLeftTileCol] != 0 || map->GetMap()[topRightTileRow][topRightTileCol] != 0)
            return true;
        return false;
        break;
    }
    case EntityDirection::DOWN: {
        float newBottomLeftX = entity->GetWorldPosition().x;
        float newBottomLeftY = entity->GetWorldPosition().y + entity->GetEntitySprite()->GetSize().y + entity->GetEntitySpeed() * deltaTime;
        float newBottomRightX = entity->GetWorldPosition().x + entity->GetEntitySprite()->GetSize().x;
        float newBottomRightY = entity->GetWorldPosition().y + entity->GetEntitySprite()->GetSize().y + entity->GetEntitySpeed() * deltaTime;

        uint32_t bottomLeftTileCol = newBottomLeftX / 32;
        uint32_t bottomLeftTileRow = newBottomLeftY / 32;
        uint32_t bottomRightTileCol = newBottomRightX / 32;
        uint32_t bottomRightTileRow = newBottomRightY / 32;

        if (map->GetMap()[bottomLeftTileRow][bottomLeftTileCol] != 0 || map->GetMap()[bottomRightTileRow][bottomRightTileCol] != 0)
            return true;
        return false;
        break;
    }    
    case EntityDirection::LEFT: {
        float newTopLeftX = entity->GetWorldPosition().x - entity->GetEntitySpeed() * deltaTime;
        float newTopLeftY = entity->GetWorldPosition().y;
        float newBottomLeftX = entity->GetWorldPosition().x - entity->GetEntitySpeed() * deltaTime;
        float newBottomLeftY = entity->GetWorldPosition().y + entity->GetEntitySprite()->GetSize().y;

        uint32_t topLeftTileCol = newTopLeftX / 32;
        uint32_t topLeftTileRow = newTopLeftY / 32;
        uint32_t bottomLeftTileCol = newBottomLeftX / 32;
        uint32_t bottomLeftTileRow = newBottomLeftY / 32;

        if (map->GetMap()[topLeftTileRow][topLeftTileCol] != 0 || map->GetMap()[bottomLeftTileRow][bottomLeftTileCol] != 0)
            return true;
        return false;
        break;
    }
    case EntityDirection::RIGHT: {
        float newTopRightX = entity->GetWorldPosition().x + entity->GetEntitySprite()->GetSize().x + entity->GetEntitySpeed() * deltaTime;
        float newTopRightY = entity->GetWorldPosition().y;
        float newBottomRightX = entity->GetWorldPosition().x + entity->GetEntitySprite()->GetSize().x + entity->GetEntitySpeed() * deltaTime;
        float newBottomRightY = entity->GetWorldPosition().y + entity->GetEntitySprite()->GetSize().y;

        uint32_t topRightTileCol = newTopRightX / 32;
        uint32_t topRightTileRow = newTopRightY / 32;
        uint32_t bottomRightTileCol = newBottomRightX / 32;
        uint32_t bottomRightTileRow = newBottomRightY / 32;

        if (map->GetMap()[topRightTileRow][topRightTileCol] != 0 || map->GetMap()[bottomRightTileRow][bottomRightTileCol] != 0)
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
