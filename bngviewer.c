#include <assert.h>
#include <SDL.h>
#include "bng.h"

void* read_whole_file(const char *filename)
{
    FILE *f = fopen(filename, "rb");

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    void *data = malloc(size);
    size_t read_size = fread(data, 1, size, f);

    return data;
}

struct Bng *bng_load(const char *filepath)
{
    return read_whole_file(filepath);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window =
        SDL_CreateWindow(
            "BNG Viewer",
            0, 0, 800, 600,
            SDL_WINDOW_RESIZABLE);


    SDL_Renderer *renderer =
        SDL_CreateRenderer(
                window, -1,
                SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    struct Bng *bng = bng_load("tsodinw.bng");

    SDL_Surface* image_surface =
        SDL_CreateRGBSurfaceFrom(bng->data,
                                 bng->width,
                                 bng->height,
                                 32,
                                 bng->width * 4,
                                 0x000000FF,
                                 0x0000FF00,
                                 0x00FF0000,
                                 0xFF000000);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image_surface);

    int quit = 0;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: {
                quit = 1;
            } break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_Rect rect = {0, 0, bng->width, bng->height};

        SDL_RenderCopy(renderer, texture, &rect, &rect);
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
