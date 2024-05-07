#ifndef shooting_h
#define shooting_h

#include "raylib.h"
#include "engine.h"
#include <stdio.h>
#include "map_management.h"
#include "player_and_enemies.h"
#include "collisions.h"
#include "animations.h"


struct bullet
{
    int x, y, direction;
    Rectangle bullet_collision_model;
    bool is_used;
};

void initiate_bullet (struct bullet *player_bullet, struct tank player);
void load_bullet_textures(Texture2D *bullet_textures);
void move_bullet(struct bullet *player_bullet);
void drawBullet(struct bullet *bullet, Texture2D *bullet_textures);
void unload_bullets(Texture2D *bullet_texture);
void enemyShooting(struct tank *enemies, struct bullet *enemy_bullet, struct animation_data *shoot_animations);
void manage_bullets(struct bullet *player_bullet, struct bullet *enemy_bullet, struct square pola_siatki[][NETSIZE_X], struct walls_on_map *walls,
                    int walls_number, struct tank *player, struct tank *enemies, struct animation_data *explosion_animations, struct animation_data *shoot_animations, struct bonus_data *bonuses);


#endif // shooting_h
