#include "display.h"

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing window.\n");
    return false;
  }
  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       window_width, window_height, SDL_WINDOW_BORDERLESS);
  if (!window) {
    fprintf(stderr, "Failed to create window.\n");
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    fprintf(stderr, "Failed to create renderer.\n");
    return false;
  }

  return true;
}

void destroy_window(void) {
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void clear_color_buffer(uint32_t color) {
  for (int y = 0; y < window_height; y++) {
    for (int x = 0; x < window_width; x++) {
      color_buffer[window_width * y + x] = color;
    }
  }
}

void render_color_buffer(void) {
  SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
                    window_width * sizeof(uint32_t));
  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void draw_grid(void) {
  uint32_t color = 0x00000000;
  int size = 25;

  // horizontal line
  for (int x = 0; x < window_width; x += 1) {
    for (int y = size; y < window_height; y += size) {
      color_buffer[window_width * y + x] = color;
    }
  }

  // vertical line
  for (int y = 0; y < window_height; y++) {
    for (int x = size; x < window_width; x += size) {
      color_buffer[window_width * y + x] = color;
    }
  }
}

// Draw a rectangle to color buffer
void draw_rect(int x, int y, int width, int height, uint32_t color) {
  for (int x_pos = x; x_pos <= x + width; x_pos++) {
    for (int y_pos = y; y_pos <= y + height; y_pos++) {
      color_buffer[window_width * y_pos + x_pos] = color;
    }
  }
}
