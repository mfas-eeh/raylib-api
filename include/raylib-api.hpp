#pragma once

#include <iostream>
#include "raylib.h"
#include <string>
#include <cstdint>      // required for fixed size integers

namespace Animations
{
    // Two seperate type of animations i.e for a single component and a collective character
    namespace One_D
    {
        struct AnimationComponent
        {
            uint16_t animation_speed, curr_index;
            uint8_t total_frames;
        };

        class AnimationManager
        {
            private:
                AnimationComponent anim_var;
                Texture2D* animation_frames;

            public:
                AnimationManager(AnimationComponent& anim_comp, const char* file_path) 
                : anim_var(anim_comp), animation_frames(new Texture2D[anim_var.total_frames])
                {
                    for (auto i{0uz}; i < anim_var.total_frames; ++i)
                    {
                        std::string anim_file_path = file_path + std::to_string(i+1) + ".png";
                        animation_frames[i] = LoadTexture(anim_file_path.c_str());
                    }
                }

                AnimationManager(const AnimationManager& other) = delete;
                AnimationManager& operator=(const AnimationManager& other) = delete;

                void draw(Vector2 pos, float scale, float rot, Color col);
                void update();

                void clear_vram();

                ~AnimationManager()
                {
                    delete[] animation_frames;
                }
        };
    };

    namespace Two_D
    {

    };
};