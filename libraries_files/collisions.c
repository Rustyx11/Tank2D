#include "../headers_files/collisions.h"

bool checkCollisionWithBorders(Rectangle *collision_model)
{
    if(collision_model -> x <= 0 || collision_model -> y <= 0 || collision_model -> x + collision_model -> width >= 1000 ||
       collision_model -> y + collision_model -> height >= 600)
            return true;
    return false;
}


// funkcja tworzy modele kolizyjne scian
void createWallsColisionModels(struct walls_on_map *walls, struct square pola_siatki[][NETSIZE_X])
{
    int i, j, licznik = 0;
    for(i = 0; i < NETSIZE_Y; i++)
    {
        for(j = 0; j < NETSIZE_X; j++)
        {
            if(pola_siatki[i][j].type_of_texture == WALL)
            {
                walls[licznik].wall.x = pola_siatki[i][j].x;
                walls[licznik].wall.y = pola_siatki[i][j].y;
                walls[licznik].wall.width = walls[licznik].wall.height = SIZE_OF_SQUARE;
                walls[licznik].id = pola_siatki[i][j].id;
                licznik++;
            }
        }
    }
}

// funkcja rysuje modele kolizyjne scian (funkcja pomocnicza)
void drawWallsColisionModels(struct walls_on_map *walls, int walls_number)
{
    int i;
    for(i = 0; i < walls_number; i++)
        DrawRectangle(walls[i].wall.x, walls[i].wall.y, walls[i].wall.width, walls[i].wall.height, BLUE);
}

// funkcja wykrywa kolizje z gory
bool AAbb_up(Rectangle tank, Rectangle object, int speed)
{

    if(tank.x + PLAYERWIDTH - speed > object.x && tank.x + speed < object.x + object.width
        &&tank.y + PLAYERHEIGHT - speed > object.y && tank.y < object.y + object.height)
        return true;
    else
        return false; // brak kolizji
}
// funkcja wykrywa kolizje z dolu
bool AAbb_down(Rectangle tank, Rectangle object, int speed)
{
    if(tank.x + PLAYERWIDTH - speed > object.x && tank.x + speed < object.x + object.width
        && tank.y + PLAYERHEIGHT >= object.y && tank.y + speed  < object.y + object.height)
        return true;
    else
        return false; // brak kolizji
}
// funkcja wykrywa kolizje z prawej strony
bool AAbb_right(Rectangle tank, Rectangle object,int speed, int character)
{
        if(tank.x + PLAYERWIDTH >= object.x && tank.x + speed * (character + 1) < object.x + object.width
           && tank.y + PLAYERHEIGHT - speed * (character + 1) > object.y && tank.y + speed * (character + 1)< object.y + object.height)
            return true;

    return false; // brak kolizji
}
// funkcja wykrywa kolizje z lewej strony
bool AAbb_left(Rectangle tank, Rectangle object,int speed, int character)
{
        if(tank.x + PLAYERWIDTH - speed * (character + 1)> object.x && tank.x <= object.x + object.width
           && tank.y + PLAYERHEIGHT - speed * (character + 1) > object.y && tank.y + speed * (character + 1) < object.y + object.height)
            return true;

    return false; // brak kolizji
}

bool checkCollisionWithWalls(Rectangle tank_collision_model,int speed, int direction, struct walls_on_map *walls, int walls_number)
{
    int i;
    for(i = 0; i < walls_number; i++)
    {
        switch(direction)
        {
    case UP:
        if(AAbb_up(tank_collision_model, walls[i].wall, speed))
            return true;
        break;
    case DOWN:
        if(AAbb_down(tank_collision_model, walls[i].wall, speed))
            return true;
        break;
    case RIGHT:
        if(AAbb_right(tank_collision_model, walls[i].wall, speed, 0))
            return true;
        break;
    case LEFT:
        if(AAbb_left(tank_collision_model, walls[i].wall, speed, 0))
            return true;
        break;
    default:
        break;
        }
    }
    return false;
}
bool checkCollisionBetweenTanksAndPlayer(struct tank *enemies,int speed, int direction, int which_tank, Rectangle tank_collision_model, Rectangle player_collision_model)
{
    int i;
    for(i = 0; i < NUMBER_OF_ENEMIES; i++)
    {
        if(which_tank == i)
            continue;

        switch(direction)
        {
        case UP:
            if(AAbb_up(tank_collision_model,enemies[i].tank_collision_model, speed) || AAbb_up(tank_collision_model, player_collision_model, speed))
                return true;
            break;
        case DOWN:
            if(AAbb_down(tank_collision_model,enemies[i].tank_collision_model, speed) || AAbb_down(tank_collision_model, player_collision_model, speed))
                return true;
            break;
        case RIGHT:
            if(AAbb_right(tank_collision_model,enemies[i].tank_collision_model, speed, 1) || AAbb_right(tank_collision_model, player_collision_model, speed, 1))
                return true;
            break;
        case LEFT:
            if(AAbb_left(tank_collision_model,enemies[i].tank_collision_model, speed, 1) || AAbb_left(tank_collision_model, player_collision_model, speed, 1))
                return true;
            break;
        default:
            break;
        }
    }
    return false;
}

bool checkCollisionBetweenPlayerAndOtherTanks(struct tank *enemies,int speed, int direction, Rectangle player_collision_model)
{
     int i;
    for(i = 0; i < NUMBER_OF_ENEMIES; i++)
    {
        switch(direction)
        {
        case UP:
            if(AAbb_up(player_collision_model,enemies[i].tank_collision_model, speed))
                return true;
            break;
        case DOWN:
            if(AAbb_down(player_collision_model,enemies[i].tank_collision_model, speed))
                return true;
            break;
        case RIGHT:
            if(AAbb_right(player_collision_model,enemies[i].tank_collision_model, speed, 1))
                return true;
            break;
        case LEFT:
            if(AAbb_left(player_collision_model,enemies[i].tank_collision_model, speed, 1))
                return true;
            break;
        default:
            break;
        }
    }
    return false;
}

int checkColissionBulletWalls(Rectangle bullet_collision_model, struct walls_on_map *walls, int walls_number)
{
    int i;
    for(i = 0; i < walls_number; i++)
           if(CheckCollisionRecs(bullet_collision_model, walls[i].wall))
           {
               walls[i].wall.x = walls[i].wall.y = -300;
               return walls[i].id;
           }

    return -1;
}

bool checkCollisionPlayerBonus(struct tank *player, struct bonus_data *bonuses)
{
    int i;
    for(i = 0; i < NUMBER_OF_ENEMIES; i++)
    {
        if(bonuses[i].is_used && CheckCollisionRecs(player ->tank_collision_model, bonuses[i].bonus_collision_mode))
        {
            bonuses[i].is_used = false;
            switch(bonuses[i].type_of_bonus)
            {
            case EXTRA_LIFE:
                player -> lives += 1;
                break;
            case EXTRA_SPEED:
                player -> speed += 1;
                break;
            default:
                break;
            }
            return true;
        }
    }
    return false;
}

bool checkCollisionBulletEnemies(Rectangle bullet_collision_model, struct tank *enemies, int *tank_destroyed_x, int *tank_destroyed_y, struct bonus_data *bonuses)
{
    int i, j;
    for(i = 0; i < NUMBER_OF_ENEMIES; i++)
    {
        if(CheckCollisionRecs(bullet_collision_model, enemies[i].tank_collision_model))
        {
            enemies[i].lives--;
            *tank_destroyed_x = enemies[i].x;
            *tank_destroyed_y = enemies[i].y;
            if(enemies[i].lives <= 0)
            {
                for(j = 0; j < NUMBER_OF_ENEMIES; j++)
                    if(bonuses[j].is_used == false)
                    {
                        bonuses[j].is_used = true;
                        bonuses[j].type_of_bonus = GetRandomValue(0, NUMBER_OF_BONUSES * 2);
                        bonuses[j].bonus_collision_mode.x = enemies[i].x;
                        bonuses[j].bonus_collision_mode.y = enemies[i].y;
                        break;
                    }
                score += 100;
                enemies_alive--;
                enemies[i].tank_collision_model = (Rectangle){-300, -300, -1, -1};
                enemies[i].speed = 0;
                enemies[i].x = -300;  enemies[i].y = -300;
            }
            return true;
        }
    }
    return false;
}

bool checkCollisionBulletPlayer(Rectangle bullet_collision_model, struct tank *player)
{
    if(CheckCollisionRecs(bullet_collision_model, player -> tank_collision_model))
        {
            player -> lives--;
            if(player -> lives > 0)
            {
                player -> tank_collision_model = (Rectangle){150, 300, PLAYERWIDTH, PLAYERHEIGHT};
                player -> x = 150;  player -> y = 300;
                return true;
            }
            else
            {
                player -> tank_collision_model = (Rectangle){-300, -300, -1, -1};
                player -> speed = 0;
                player -> x = -300;  player -> y = -300;
            }
            return true;
        }
    return false;
}


