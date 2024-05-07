#include "../headers_files/player_and_enemies.h"
#include <time.h>

// funkcja wczytuje textury pozycji czaolgu do tablicy 4 - elementowej, ktora bedzie je przechowywac
void load_tank_textures(struct tank_direction_textures *player_positions, int choice)
{
    Image temp, tmp;
      switch(choice)
      {
      case PLAYER:
        temp = LoadImage("img/tank.png");
        break;
      case ENEMY:
        temp = LoadImage("img/enemy_tank.png");
        break;
      default:
        temp = LoadImage("img/enemy_tank.png");
        break;
      }
    tmp = ImageFromImage(temp, (Rectangle){0, 0, PLAYERWIDTH , PLAYERHEIGHT});
    player_positions[0].direction = LoadTextureFromImage(tmp);
    tmp = ImageFromImage(temp, (Rectangle){45,0, PLAYERHEIGHT , PLAYERWIDTH});
    player_positions[1].direction = LoadTextureFromImage(tmp);
    tmp = ImageFromImage(temp, (Rectangle){90, 0, PLAYERHEIGHT , PLAYERWIDTH});
    player_positions[2].direction = LoadTextureFromImage(tmp);
    tmp = ImageFromImage(temp, (Rectangle){135, 0, PLAYERWIDTH , PLAYERHEIGHT});
    player_positions[3].direction = LoadTextureFromImage(tmp);

    UnloadImage(temp);
    UnloadImage(tmp);
}

void change_tank_textures(struct tank_direction_textures *positions, Texture2D *tank_direction, int direction)
{

    switch(direction)
    {
    case DOWN:
        *tank_direction = positions[0].direction;
        break;
    case LEFT:
        *tank_direction = positions[1].direction;
        break;
    case RIGHT:
        *tank_direction = positions[2].direction;
        break;
    case UP:
        *tank_direction = positions[3].direction;
        break;
    default:
        *tank_direction = positions[0].direction;
        break;
    }
}

// funkcja wczytuje player_positions czolgu
void loadPlayerStartTexture(Texture2D start_texture, Texture2D *tank)
{
    *tank = start_texture;
}

void addPlayer(struct tank *player, struct tank_direction_textures *player_positions)
{
    player -> x = 320;
    player -> y = 320;
    player -> direction = DOWN;
    player -> speed = 3;
    player -> movement_counter = rand_number(0,4);
    player -> lives = 3;
    player -> tank_collision_model = (Rectangle){player -> x, player -> y, PLAYERWIDTH, PLAYERHEIGHT};
    player -> tank_direction = player_positions[0].direction;
}


void addEnemy(struct tank *enemies, struct tank_direction_textures *enemy_positions)
{
    int i;
    for(i = 0; i < NUMBER_OF_ENEMIES; i++)
    {
        enemies[i].x = 600;
        enemies[i].y = (i+2) * 45;
        enemies[i].direction = 0;
        enemies[i].speed = 2;
        enemies[i].movement_counter = GetRandomValue(0,3);
        enemies[i].lives = 1;
        enemies[i].tank_collision_model = (Rectangle){enemies[i].x, enemies[i].y, PLAYERWIDTH, PLAYERHEIGHT};
        enemies[i].tank_direction = enemy_positions[0].direction;
    }

}
void unloadEnemyTextures(struct tank *enemies)
{
    int i;
    for(i = 0; i < NUMBER_OF_ENEMIES; i++)
        UnloadTexture(enemies[i].tank_direction);
}

void drawEnemies(struct tank *enemies)
{
    int i;
    for(i = 0; i < NUMBER_OF_ENEMIES; i++)
        if(enemies[i].lives > 0)
            DrawTextureEx(enemies[i].tank_direction, (Vector2){enemies[i].x, enemies[i].y}, 0, 1, RAYWHITE);
}

void enemyMovements(struct tank_direction_textures *enemy_positions, struct tank *enemies, struct walls_on_map *walls, int walls_number, Rectangle player)
{

    int i;
    for(i = 0; i < NUMBER_OF_ENEMIES; i++)
    {
        switch(enemies[i].direction)
            {
            case LEFT:
                if(!checkCollisionWithWalls(enemies[i].tank_collision_model,enemies[i].speed, LEFT,  walls, walls_number) &&
                   !checkCollisionBetweenTanksAndPlayer(enemies, enemies[i].speed, LEFT, i, enemies[i].tank_collision_model, player) && enemies[i].movement_counter != 40)
                {
                    change_tank_textures(enemy_positions, &enemies[i].tank_direction, LEFT);
                    enemies[i].tank_collision_model.x -= enemies[i].speed;
                    enemies[i].x -= enemies[i].speed;
                    enemies[i].movement_counter++;
                }
                else
                {
                    enemies[i].direction = rand_number(0,4);
                    enemies[i].movement_counter = 0;
                }
                break;
            case RIGHT:
                if(!checkCollisionWithWalls(enemies[i].tank_collision_model,enemies[i].speed, RIGHT,  walls, walls_number) &&
                   !checkCollisionBetweenTanksAndPlayer(enemies, enemies[i].speed, RIGHT, i, enemies[i].tank_collision_model, player) && enemies[i].movement_counter != 40)
                {
                    change_tank_textures(enemy_positions, &enemies[i].tank_direction, RIGHT);
                    enemies[i].tank_collision_model.x += enemies[i].speed;
                    enemies[i].x += enemies[i].speed;
                    enemies[i].movement_counter++;
                }
                else
                    {
                    enemies[i].direction = rand_number(0,4);
                    enemies[i].movement_counter = 0;
                }
                break;
            case DOWN:
                if(!checkCollisionWithWalls(enemies[i].tank_collision_model,enemies[i].speed, DOWN,  walls, walls_number) &&
                   !checkCollisionBetweenTanksAndPlayer(enemies, enemies[i].speed, DOWN, i, enemies[i].tank_collision_model, player) && enemies[i].movement_counter != 80)
                {
                    change_tank_textures(enemy_positions, &enemies[i].tank_direction, DOWN);
                    enemies[i].tank_collision_model.y += enemies[i].speed;
                    enemies[i].y += enemies[i].speed;
                    enemies[i].movement_counter++;
                }
                else
                    {
                    enemies[i].direction = rand_number(0,4);
                    enemies[i].movement_counter = 0;
                }
                break;
            case UP:
                if(!checkCollisionWithWalls(enemies[i].tank_collision_model,enemies[i].speed, UP, walls, walls_number) &&
                   !checkCollisionBetweenTanksAndPlayer(enemies, enemies[i].speed, DOWN, i, enemies[i].tank_collision_model, player) && enemies[i].movement_counter != 80)
                {
                    change_tank_textures(enemy_positions, &enemies[i].tank_direction, UP);
                    enemies[i].tank_collision_model.y -= enemies[i].speed;
                    enemies[i].y -= enemies[i].speed;
                    enemies[i].movement_counter++;
                }
                else
                    {
                    enemies[i].direction = rand_number(0,4);
                    enemies[i].movement_counter = 0;
                }
                break;
            default:
                enemies[i].direction = rand_number(0,4);
                enemies[i].movement_counter = 0;
                break;

            }

        if(enemies[i].x > 1000 - PLAYERWIDTH)  { enemies[i].x  = enemies[i].tank_collision_model.x  =  1000 - PLAYERWIDTH; enemies[i].direction = rand_number(0,4);}
        if(enemies[i].y > 600 - PLAYERHEIGHT)  { enemies[i].y  = enemies[i].tank_collision_model.y  = 600 - PLAYERWIDTH; enemies[i].direction = rand_number(0,4);}
        if(enemies[i].x  < 0)                  { enemies[i].x  = enemies[i].tank_collision_model.x  = 0; enemies[i].direction = rand_number(0,4);}
        if(enemies[i].y  < 0)                  { enemies[i].y  = enemies[i].tank_collision_model.y  = 0; enemies[i].direction = rand_number(0,4);}

    }

}

void load_bonus_textures(struct bonus_textures *bonus_textures)
{
    bonus_textures -> extra_life_texture = LoadTexture("img/extra_life.png");
    bonus_textures -> extra_speed_texture = LoadTexture("img/extra_speed.png");
}

void unload_bonus_textures(struct bonus_textures *bonus_textures)
{
    UnloadTexture(bonus_textures ->extra_life_texture);
    UnloadTexture(bonus_textures ->extra_speed_texture);
}

void initiate_bonuses(struct bonus_data *bonuses)
{
    int i;
    for(i = 0; i < NUMBER_OF_ENEMIES; i++)
    {
        bonuses[i].bonus_collision_mode.height = bonuses[i].bonus_collision_mode.width = 50;
        bonuses[i].bonus_collision_mode.x = bonuses[i].bonus_collision_mode.y = -1;
        bonuses[i].is_used = false;
        bonuses[i].type_of_bonus = -1;
    }
}

void draw_bonuses(struct bonus_textures *bonus_textures, struct bonus_data *bonuses)
{
    int i;
    for(i = 0; i < NUMBER_OF_ENEMIES; i++)
        if(bonuses[i].is_used == true)
        {
            switch(bonuses[i].type_of_bonus)
            {
            case EXTRA_LIFE:
                DrawTexture(bonus_textures -> extra_life_texture, bonuses[i].bonus_collision_mode.x, bonuses[i].bonus_collision_mode.y, RAYWHITE);
                break;
            case EXTRA_SPEED:
                DrawTexture(bonus_textures -> extra_speed_texture, bonuses[i].bonus_collision_mode.x, bonuses[i].bonus_collision_mode.y, RAYWHITE);
                break;
            default:
                break;
            }
        }
}


