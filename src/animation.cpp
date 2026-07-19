#include "raylib-api.hpp"

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
void Animations::One_D::AnimationManager::clear_vram()
{
    for (auto i{0uz}; i < anim_var.total_frames; ++i)
        UnloadTexture(animation_frames[i]);
}



void Animations::Two_D::AnimationManager::clear_vram()
{
    for (auto i{0uz}; i < anim_comp.total_animations; ++i)
    {
        for (auto j {0uz}; j < anim_comp.total_variant_frames[i]; ++j)
        {
            UnloadTexture(entity_animations[i][j]);
        }
    }
}
void Animations::Two_D::AnimationManager::setAnimation(const uint8_t& newAnimation) {   anim_comp.curr_animation = newAnimation;    }
void Animations::Two_D::AnimationManager::draw(const Vector2& pos, const float& rot, const float& scale)
{
    DrawTextureEx(entity_animations[anim_comp.curr_animation][anim_comp.curr_index / anim_comp.animation_speed],
    pos, rot, scale, WHITE);
}
void Animations::Two_D::AnimationManager::update()
{
    anim_comp.curr_index++;
    if (anim_comp.curr_index >= (anim_comp.animation_speed * 
        anim_comp.total_variant_frames[anim_comp.curr_animation]))
    {
            anim_comp.curr_index = 0;
    }
}



void Animations::SpriteSheet::AnimationManager::draw(const Vector2& pos)
{
    DrawTextureRec(spritesheet, source_rect, pos, WHITE);
}
void Animations::SpriteSheet::AnimationManager::update()
{
    anim_frame_index += GetFrameTime();

    if (anim_frame_index >= sheet_comp.animation_speed)
    {
        anim_frame_index = 0.0f;
        sheet_comp.curr_frame = (sheet_comp.curr_frame + 1) % sheet_comp.total_variant_frames[sheet_comp.curr_animation];
    }

    source_rect = {
        static_cast<float>(sheet_comp.curr_frame * sheet_comp.frame_width),
        static_cast<float>(sheet_comp.curr_animation * sheet_comp.frame_height),
        static_cast<float>(sheet_comp.frame_width),
        static_cast<float>(sheet_comp.frame_height)
    };
}
void Animations::SpriteSheet::AnimationManager::setAnimation(const uint8_t& newAnimation)   {   sheet_comp.curr_animation = newAnimation;   }
void Animations::SpriteSheet::AnimationManager::clear_vram()
{
    UnloadTexture(spritesheet);
}