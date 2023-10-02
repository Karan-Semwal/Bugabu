#pragma once
#include "Animator.h"
#include "PlayerState.h"
#include "Player.h"

class PlayerAnimator : public Animator
{
public:
    PlayerAnimator(Player& player, sf::Texture& spriteSheet, int c, int r, float ft);
    ~PlayerAnimator() { }

    void switchAnimation(Player& player);
    void update() override;

private:
    bool isIdle       {true};
    bool isMovingLeft {false};
    
    int currentRow;
    int currentColumn;
};
