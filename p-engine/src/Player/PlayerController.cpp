#include "PlayerController.h"
#include "Global.h"
#include <cmath>

PlayerController::PlayerController()
    : m_velocity(5.f, 5.f)
{
}

bool PlayerController::canMove(const sf::Vector2f& pos, Tilemap& map) {
    float playerX = pos.x;
    float playerY = pos.y;

    int pTileX = int(playerX / TILE_WIDTH_SIZE);
    int pTileY = int(playerY / TILE_HEIGHT_SIZE);

    char playerTile = map.getChatAtMap(pTileX, pTileY);
    return playerTile != '#';
}

void PlayerController::gravity(Player& player, Tilemap& map) {
    
    if (isOnFloor) {
        GRAVITY = lerpValue(GRAVITY, GRAVITY_LIMIT, GRAVITY_LERP_VALUE);
        sf::Vector2f pos = player.getPosition();
        if (canMove({player.hitbox.getBottomLeft().x, player.hitbox.getBottomLeft().y + GRAVITY} , map)) {
            if (canMove({player.hitbox.getBottomRight().x, player.hitbox.getBottomRight().y + GRAVITY} , map))
                player.setPosition({pos.x, pos.y + GRAVITY});
        }
    }
    else {
        GRAVITY = 0.f;
    }
}

bool isOnGround(Player& player, Tilemap& map)
{
    sf::Vector2f playerPos(player.getPosition());
    int pTileX = int(playerPos.x / TILE_WIDTH_SIZE);
    int pTileY = int(playerPos.y / TILE_HEIGHT_SIZE);

    char playerTile = map.getChatAtMap(pTileX, pTileY + 1);
    return playerTile == '#';
}

void PlayerController::update(Player& player, Tilemap& map, sf::Event& event)
{
    sf::Vector2f pos = player.getPosition();
    sf::Vector2f vel{m_currentVelocity};

    if (isPressed(sf::Keyboard::W))
    {
        player.pstate = PlayerState::MOVE;
        player.pMovementState = PlayerMovementState::CLIMBING;
        player.pfacingDirection = PlayerFacingDirection::UP;
    }
    else if (isPressed(sf::Keyboard::A))
    {
        m_currentVelocity.x = lerpValue(m_currentVelocity.x, m_velocity.x, m_velocityLerpValue);
        
        player.pstate = PlayerState::MOVE;
        player.pfacingDirection = PlayerFacingDirection::LEFT;
        if (canMove({player.hitbox.getTopLeft().x - vel.x, player.hitbox.getTopLeft().y} , map)) {
            if (canMove({player.hitbox.getBottomLeft().x - vel.x, player.hitbox.getBottomLeft().y} , map))
                player.setPosition({pos.x - vel.x, pos.y});
        }
        jump(player, map, event);
    }
    else if (isPressed(sf::Keyboard::S))
    {
        player.pstate = PlayerState::MOVE;
        player.pMovementState = PlayerMovementState::CLIMBING;
    }
    else if (isPressed(sf::Keyboard::D))
    {
        m_currentVelocity.x = lerpValue(m_currentVelocity.x, m_velocity.x, m_velocityLerpValue);
        
        player.pstate = PlayerState::MOVE;
        player.pfacingDirection = PlayerFacingDirection::RIGHT;
        jump(player, map, event);
        if (canMove({player.hitbox.getTopRight().x + vel.x, player.hitbox.getTopRight().y} , map)) {
            if (canMove({player.hitbox.getBottomRight().x + vel.x, player.hitbox.getBottomRight().y} , map))
                player.setPosition({pos.x + vel.x, pos.y});
        }
    }
    else if (isPressed(sf::Keyboard::E))
    {
        player.pMovementState = PlayerMovementState::THROWING;
    }
    else
    {
        player.pstate         = PlayerState::IDLE; 
        player.pMovementState = PlayerMovementState::NONE;           
    }

    // Reset the current velocity to zero when key is released
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
            m_currentVelocity = {0.f, 0.f};
        }
        if (event.key.code == sf::Keyboard::E) {
            player.pMovementState = PlayerMovementState::NONE;
        }
    }

    jump(player, map, event);
    gravity(player, map);
}

void PlayerController::jump(Player& player, Tilemap& map, sf::Event& event)
{
    sf::Vector2f pos = player.getPosition();
    if (!isJumping) {
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
            if (canMove({pos.x, pos.y + GRAVITY}, map)) {
                isJumping = true;
                std::cout << "Jumping started\n";
            }
        }
    }
    if (isJumping) {
        isOnFloor = false;
        tmpVelocity += JUMP_MAGNITUDE;
        pos.y -= JUMP_MAGNITUDE;
        if (tmpVelocity >= JUMP_LIMIT) {
            tmpVelocity = 0.f;
            isJumping = false;
            isOnFloor = true;
            std::cout << "Jumping stopped\n";
        }
        player.setPosition(pos);
    }
}
