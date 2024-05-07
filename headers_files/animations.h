#ifndef animations_h
#define animations_h

#include "raylib.h"
#include "engine.h"


struct animation_data
{
    int x;
    int y;
    int frames_counter;
    int direction;
    bool is_used;
};

struct explosion_animation_textures
{
    Texture2D stage_1;
    Texture2D stage_2;
    Texture2D stage_3;
    Texture2D stage_4;
    Texture2D stage_5;
    Texture2D stage_6;
    Texture2D stage_7;
};

struct shoot_animation_textures
{
    Texture2D stage_1_up;
    Texture2D stage_2_up;
    Texture2D stage_3_up;

    Texture2D stage_1_left;
    Texture2D stage_2_left;
    Texture2D stage_3_left;

    Texture2D stage_1_down;
    Texture2D stage_2_down;
    Texture2D stage_3_down;

    Texture2D stage_1_right;
    Texture2D stage_2_right;
    Texture2D stage_3_right;
};

void load_explosion_textures(struct explosion_animation_textures *explosion_textures);
void unload_explosion_textures(struct explosion_animation_textures *explosion_textures);
void draw_explosion_animation(struct animation_data *animation, struct explosion_animation_textures explosion_animation, int index);

void load_shoot_textures(struct shoot_animation_textures *shoot_textures);
void unload_shoot_textures(struct shoot_animation_textures *shoot_textures);
void draw_shoot_animation(struct animation_data *animation, struct shoot_animation_textures shot_animation, int index, int direction);



#endif // animations_h
