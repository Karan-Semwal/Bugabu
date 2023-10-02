#pragma once
#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include "PlayerState.h"
#include "TextureManager.h"
#include "Hitbox.h"

// Forward declaration
class PlayerAnimator;
class PlayerController;

class Player
{
public:
    Player();
    ~Player();
    void initTexture();

    sf::Vector2f getPosition()      const { return m_player.getPosition(); }
    sf::RectangleShape& getObject()       { return m_player; }
    sf::Vector2f& getVelocity()           { return m_veloctiy; }
    void setPosition(const sf::Vector2f& pos)  { m_player.setPosition(pos); }
    void setVelocity(const sf::Vector2f& vel)  { this->m_veloctiy = vel; }

    void update(Tilemap& map, sf::Event& event);
    void render(sf::RenderWindow& window);

public:
    Hitbox                hitbox;
    PlayerState           pstate;
    PlayerMovementState   pMovementState;
    PlayerFacingDirection pfacingDirection;

private:
    sf::Vector2f           m_size;
    sf::RectangleShape     m_player;
    sf::Vector2f           m_veloctiy;
    
    PlayerController* m_controller; // handle player input
    PlayerAnimator*   m_animator;   // handle player animations
};