#ifndef main_menu_h
#define main_menu_h

#include "raylib.h"
#include "engine.h"



void loadMenuTextures(struct menu_textures *menu);
void load_end_window(struct end_window_textures *end_window);
void unloadMenuTextures(struct menu_textures *menu);
void unload_end_window_textures(struct end_window_textures *end_window);
void drawAnimatedMenu(struct menu_textures *menu);
bool draw_win_end_window(struct end_window_textures end_window, Sound win_sound);
void draw_lose_end_window(struct end_window_textures end_window, struct tank player);


#endif // main_menu_h
