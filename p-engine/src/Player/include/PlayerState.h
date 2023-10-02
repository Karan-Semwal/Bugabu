#pragma once

enum PlayerState
{
    IDLE = 0, MOVE, DYING
};

enum PlayerMovementState
{
    NONE = 0, JUMP, THROWING, CLIMBING, ATTACKING
};

enum PlayerFacingDirection
{
    RIGHT = 0, LEFT, UP, DOWN
};
