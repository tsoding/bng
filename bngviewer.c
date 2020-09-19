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

uint32_t *bng_load(const char *filepath, uint32_t *width, uint32_t *height)
{
    struct Bng *compressed_bng = read_whole_file(filepath);

    uint32_t *pixels = malloc(compressed_bng->width * compressed_bng->height * sizeof(uint32_t));
    decompress_pixels(compressed_bng->pairs, compressed_bng->pairs_count, pixels);

    for (size_t i = 0; i < compressed_bng->width * compressed_bng->height; ++i) {
        pixels[i] = convert_pixel(pixels[i], compressed_bng->pixel_format, RGBA);
    }

    *width = compressed_bng->width;
    *height = compressed_bng->height;

    return pixels;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "./bngviewer <input.bng>");
        exit(1);
    }

    const char *input_filepath = argv[1];

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

    uint32_t width, height;
    uint32_t *pixels = bng_load(input_filepath, &width, &height);

    SDL_Surface* image_surface =
        SDL_CreateRGBSurfaceFrom(pixels,
                                 width,
                                 height,
                                 32,
                                 width * 4,
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

        SDL_Rect rect = {0, 0, width, height};

        SDL_RenderCopy(renderer, texture, &rect, &rect);
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
