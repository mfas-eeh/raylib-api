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

        struct AnimationComponent
        {
            uint8_t* total_variant_frames;      // total columns for each row
            uint16_t animation_speed;
            uint16_t curr_index{0uz};
            uint8_t total_animations;
            uint8_t curr_animation{0uz};
        };

        class AnimationManager
        {
            private:
                AnimationComponent anim_comp;
                Texture2D** entity_animations;

            public:
                AnimationManager(AnimationComponent& anim, const char* file_path, std::string* folder)
                : anim_comp(anim)
                {
                    entity_animations = new Texture2D*[anim_comp.total_animations];     //allocating total rows
                    for (auto i{0uz}; i < anim_comp.total_animations; ++i)
                    {
                        entity_animations[i] = new Texture2D[anim_comp.total_variant_frames[i]]; // allocating different number of columns
                    }

                    for (auto i{0uz}; i < anim_comp.total_animations; ++i)
                    {
                        for (auto j{0uz}; j < anim_comp.total_variant_frames[i]; ++j)
                        {
                            std::string anim_frame_file = file_path + *(folder + i) + std::to_string(j+1) + ".png";
                            entity_animations[i][j] = LoadTexture(anim_frame_file.c_str());
                        }
                    }   
                }

                AnimationManager(const AnimationManager& other) = delete;
                AnimationManager& operator=(const AnimationManager& other) = delete;

                void draw();
                void update();
                void clear_vram();

                ~AnimationManager()
                {
                    for (auto i{0uz}; i < anim_comp.total_animations; ++i)
                    {
                        delete[] entity_animations[i];
                    }
                    delete[] entity_animations;
                }
        };
    };
};