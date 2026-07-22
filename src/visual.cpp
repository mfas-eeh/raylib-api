#include "raylib-api.hpp"

void VisualEffects::apply_rgb(Color& object_color, const float& speed)          // to eliminate sine's range from going into negative we added 127.5f so at minimum the channel is off
{                                                                               // morever unsigned char has a range of 8 bits, ie. 0-255
    constexpr float phase_120 = (2.f * PI) / 3.f;
    constexpr float phase_240 = (4.f * PI) / 3.f;
    float angle = GetTime() * speed;

    object_color.r = static_cast<unsigned char>(127.5f + (127.5f * sinf(angle)));
    object_color.g = static_cast<unsigned char>(127.5f + (127.5f * sinf(angle + phase_120)) );
    object_color.b = static_cast<unsigned char>(127.5f + (127.5f * sinf(angle + phase_240)) );
}

void VisualEffects::apply_flash(const Rectangle& rect, float& flash_index, const float& decay_speed, const Color& color, const float& round)
{   
    if (flash_index > 0)
    {
        flash_index -= decay_speed; 
        Color c = {color.r, color.g, color.b, static_cast<unsigned char>(flash_index)};
        DrawRectangleRounded(rect, round, 20, c);
    }
}