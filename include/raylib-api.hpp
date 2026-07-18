#pragma once

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

                AnimationManager(const AnimationManager& other)
                {
                    this->anim_var = other.anim_var;
                    this->animation_frames = new Texture2D[this->anim_var.total_frames];
                    for (auto i{0uz}; i < this->anim_var.total_frames; ++i)
                    {
                        this->animation_frames[i] = other.animation_frames[i];
                    }
                }

                void draw(Vector2 pos, float scale, float rot, Color col);
                void update();

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