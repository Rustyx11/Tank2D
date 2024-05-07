#ifndef map_management_h
#define map_management_h

#include "raylib.h"
#include "engine.h"
#include <stdio.h>



bool loadMapFromFile( struct square pola_siatki[][NETSIZE_X], int which_map);    // funkcja laduje mape z pliku
void fillTheMap(struct square pola_siatki[][NETSIZE_X]);         // funkcja dobiera textury do mapy
void drawTheMap(struct square pola_siatki[][NETSIZE_X]);         // funkcja rysuje mape na ekranie
void unloadMap(struct square pola_siatki[][NETSIZE_X]);          // usuniecie textur mapy z pamieci RAM
void replace_map_square(struct square pola_siatki[][NETSIZE_X], int id, struct square **pole_siatki);
int howManyWalls(struct square pola_siatki[][NETSIZE_X], int walls_number); // funkcja okresla ile scian jest na mapie
// funkcja okresla granice mapy za ktore czolg nie moze wyjechac
void setBorders(struct tank *tank);
// funkcja rysuje granice mapy na ekranie
void drawTheBorders();





#endif // map_management_h
