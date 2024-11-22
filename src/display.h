#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

int window_width;
int window_height;

SDL_Window *window;
SDL_Renderer *renderer;

uint32_t *color_buffer;
SDL_Texture *color_buffer_texture;

bool initialize_window(void);
void destroy_window(void);
void clear_color_buffer(uint32_t color);
void render_color_buffer(void);
void draw_grid(void);
void draw_rect(int x, int y, int width, int height, uint32_t color);

#endif
