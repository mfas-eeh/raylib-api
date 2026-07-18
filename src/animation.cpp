#include "raylib-api.hpp"
#include "raylib.h"

void Animations::One_D::AnimationManager::draw(Vector2 pos, float scale, float rot, Color col)
{
    DrawTextureEx(animation_frames[anim_var.curr_index / anim_var.animation_speed], pos, rot, scale, col);
}

void Animations::One_D::AnimationManager::update()
{
    anim_var.curr_index++;
    if (anim_var.curr_index >= (anim_var.total_frames * anim_var.animation_speed))
    {
        anim_var.curr_index = 0;
    }
}