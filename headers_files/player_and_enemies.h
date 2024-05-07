#ifndef player_and_enemies_h
#define player_and_enemies_h

#include "raylib.h"
#include "engine.h"
#include "map_management.h"
#include "collisions.h"



// funkcja wczytuje textury pozycji czaolgu do tablicy 4 - elementowej, ktora bedzie je przechowywac
void load_tank_textures(struct tank_direction_textures *player_positions, int choice);
// funkcja podmienia tekstury gracza lub przeciwnikow ze wzgledu na kierunek poruszania sie
void change_tank_textures(struct tank_direction_textures *positions, Texture2D *tank_direction, int direction);
// funkcja wczytuje poczatkawa teksture pozycji gracza czolgu
void loadPlayerStartTexture(Texture2D start_texture, Texture2D *tank);
// inicjacja parametrow gracza
void addPlayer(struct tank *player, struct tank_direction_textures *player_positions);
// inicjacja parametrow przeciwnikow
void addEnemy(struct tank *enemies, struct tank_direction_textures *enemy_positions);
// rysowanie przeciwnikow
void drawEnemies(struct tank *enemies);
// zwolnienie tekstur przeciwnikow z pamieci
void unloadEnemyTextures(struct tank *enemies);
void enemyMovements(struct tank_direction_textures *enemy_positions, struct tank *enemies, struct walls_on_map *walls, int walls_number, Rectangle player);
void load_bonus_textures(struct bonus_textures *bonus_textures);
void unload_bonus_textures(struct bonus_textures *bonus_textures);
void initiate_bonuses(struct bonus_data *bonuses);
void draw_bonuses(struct bonus_textures *bonus_textures, struct bonus_data *bonuses);






#endif // player_and_enemies_h
