#ifndef collisions_h
#define collisions_h

#include "engine.h"
#include "raylib.h"
#include "map_management.h"
#include "player_and_enemies.h"



// funkcja tworzy modele kolizyjne scian
void createWallsColisionModels(struct walls_on_map *walls, struct square pola_siatki[][NETSIZE_X]);
// funkcja rysuje modele kolizyjne scian (funkcja pomocnicza)
void drawWallsColisionModels(struct walls_on_map *walls, int walls_number);
// funkcja wykrywa kolizje z gory
bool AAbb_up(Rectangle tank, Rectangle object, int speed);
// funkcja wykrywa kolizje z dolu
bool AAbb_down(Rectangle tank, Rectangle object, int speed);
// funkcja wykrywa kolizje z prawej strony
bool AAbb_right(Rectangle tank, Rectangle object,int speed, int character);
// funkcja wykrywa kolizje z lewej strony
bool AAbb_left(Rectangle tank, Rectangle object,int speed, int character);

bool checkCollisionWithBorders(Rectangle *collision_model);
bool checkCollisionWithWalls(Rectangle tank_collision_model,int speed, int direction, struct walls_on_map *walls, int walls_number);

bool checkCollisionBetweenTanksAndPlayer(struct tank *enemies,int speed, int direction, int which_tank, Rectangle tank_collision_model, Rectangle player_collision_model);
bool checkCollisionBetweenPlayerAndOtherTanks(struct tank *enemies,int speed, int direction, Rectangle player_collision_model);

int checkColissionBulletWalls(Rectangle bullet_collision_model, struct walls_on_map *walls, int walls_number);

bool checkCollisionBulletEnemies(Rectangle bullet_collision_model, struct tank *enemies, int *tank_destroyed_x, int *tank_destroyed_y, struct bonus_data *bonuses);
bool checkCollisionBulletPlayer(Rectangle bullet_collision_model, struct tank *player);

bool checkCollisionPlayerBonus(struct tank *player, struct bonus_data *bonuses);





#endif // collisions_h
