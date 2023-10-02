#include "PlayerAnimator.h"

PlayerAnimator::PlayerAnimator(Player& player, sf::Texture& spriteSheet, int c, int r, float ft)
    : Animator(player.getObject(), spriteSheet, c, r, ft)
{
    currentRow    = 0;
    currentColumn = columns;
    if (player.pstate == PlayerState::IDLE) {
        isIdle = true;
        currentRow    = 0;
        currentColumn = 4;
    }
}

void PlayerAnimator::switchAnimation(Player& player)
{
    switch (player.pstate)
    {
        case PlayerState::IDLE:
            isIdle = true;
            currentRow    = 0;
            currentColumn = 4;
            break;
        case PlayerState::MOVE:
            isIdle = false;
            switch (player.pfacingDirection)
            {
                case PlayerFacingDirection::LEFT:
                    currentRow    = 2;
                    currentColumn = 5;
                    isMovingLeft = true;
                    break;
                case PlayerFacingDirection::RIGHT:
                    currentRow    = 2;
                    currentColumn = 5;
                    isMovingLeft = false;
                    break;
                case PlayerFacingDirection::UP:
                    currentRow    = 3;
                    currentColumn = 3;
                    isMovingLeft = false;
                    break;
                case PlayerFacingDirection::DOWN:
                    currentRow    = 3;
                    currentColumn = 3;
                    isMovingLeft = false;
                    break;
                default:
                    break;
            }

            switch (player.pMovementState)
            {
                case PlayerMovementState::CLIMBING:
                    currentRow    = 3;
                    currentColumn = 3;
                    break;
                case PlayerMovementState::THROWING:
                    currentRow    = 5;
                    currentColumn = 3;
                    break;
                case PlayerMovementState::JUMP:
                    currentRow    = 1;
                    currentColumn = 7;
                    break;
                default:
                    break;
            }
            break;
        case PlayerState::DYING:
            currentRow    = 7;
            currentColumn = 7;
            break;
        default:
            break;

        switch (player.pMovementState)
        {
            case PlayerMovementState::CLIMBING:
                currentRow    = 3;
                currentColumn = 3;
                break;
            case PlayerMovementState::THROWING:
                currentRow    = 5;
                currentColumn = 3;
                break;
            case PlayerMovementState::JUMP:
                currentRow    = 1;
                currentColumn = 7;
                break;
            default:
                break;
        }
    }
}

void PlayerAnimator::update()
{
    int frameX = 0;
    int frameY = 0;

    if (m_timer.getElapsedTime() >= frameTime) 
    {
        if (isMovingLeft) {
            currentFrame++;
            m_timer.reset();

            if (currentFrame <= 0) { // DBG
                currentFrame = 5;
            }

            frameX = currentFrame % currentColumn ;
            frameY = currentRow;
        }
        else {
            currentFrame++;
            m_timer.reset();

            if (currentFrame >= currentColumn) { // DBG
                currentFrame = 0;
            }

            frameX = currentFrame % currentColumn ;
            frameY = currentRow;
        }

        sprite.setTextureRect(sf::IntRect(
            frameX * sprite.getTextureRect().width,
            frameY * sprite.getTextureRect().height,
            sprite.getTextureRect().width,
            sprite.getTextureRect().height)
        );
    }
    m_timer.update();
}
