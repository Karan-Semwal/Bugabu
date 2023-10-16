#include "Player.h"
#include "PlayerController.h"
#include "PlayerAnimator.h"

Player::Player()
    : m_player(),
      m_veloctiy(1.5f, 1.5f),
      hitbox({0., 0.}, {0., 0.}),
      m_animator(new PlayerAnimator(*this, TextureManager::get_player_texture(), PLAYER_TEXTURE_COLUMNS, PLAYER_TEXTURE_ROWS, 0.15f)),
      m_controller(new PlayerController()),
      pstate(PlayerState::IDLE),
      pMovementState(PlayerMovementState::NONE),
      pfacingDirection(PlayerFacingDirection::RIGHT)
{
    m_size.x = m_player.getSize().x;
    m_size.y = m_player.getSize().y;
    sf::Vector2f origin(m_size.x / 2.f, m_size.y / 2.f);
    hitbox.setSize({m_size.x - 30.f, m_size.y - 10.f});
    hitbox.getObject().setOrigin(origin);
    this->m_player.setOrigin(origin);
}

Player::~Player()
{
    delete m_animator;
    delete m_controller;
}

void Player::initTexture()
{
    m_player.setTexture(&TextureManager::get_player_texture());
    float w = TextureManager::get_player_texture().getSize().x;
    float h = TextureManager::get_player_texture().getSize().y;
    m_player.setTextureRect(sf::IntRect(0, 0, w / 4, h / 4));
}

void Player::update(Tilemap& map, sf::Event& event)
{
    m_controller->update(*this, map, event);
    m_animator->switchAnimation(*this);
    m_animator->update();
    hitbox.update({m_player.getPosition().x, m_player.getPosition().y});
}

void Player::render(sf::RenderWindow& window) 
{
    window.draw(m_player);
    hitbox.render(window);
}


