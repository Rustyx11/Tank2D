#ifndef map_editor_h
#define map_editor_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"
#include "raylib.h"
#include "map_management.h"
#include<sys/stat.h>


void  fillTheMapEditor(struct square pola_siatki[][NETSIZE_X]);
void fillMapRec( Rectangle MapRec[][NETSIZE_X],struct square pola_siatki[][NETSIZE_X]);
int checkIfFileExists(const char* filename);
void changeTexture(int GroundSelected,Rectangle MapRec[][NETSIZE_X],struct square pola_siatki[][NETSIZE_X]);
int mapEditor();


struct square pola_siatki[NETSIZE_Y][NETSIZE_X];




#endif
