#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
#include "./bng.h"

int main(int argc, char **argv)
{
    if (argc < 4) {
        fprintf(stderr, "png2bng <input.png> <output.bng> <pixel-format>\n");
        exit(1);
    }

    const char *input_filepath = argv[1];
    const char *output_filepath = argv[2];
    struct Bng_Pixel_Format desired_format = pixel_format_by_name(argv[3]);

    int x, y, n;
    uint32_t *data = (uint32_t*)stbi_load(input_filepath, &x, &y, &n, 4);
    assert(data != NULL);

    struct Bng bng = {
        .magic        = BNG_MAGIC,
        .width        = x,
        .height       = y,
        .pixel_format = desired_format,
    };

    for (size_t i = 0; i < bng.width * bng.height; ++i) {
        data[i] = convert_pixel(data[i], RGBA, desired_format);
    }

    FILE *out = fopen(output_filepath, "wb");
    fwrite(&bng, 1, sizeof(bng), out);
    fwrite(data, 1, x * y * 4, out);
    fclose(out);

    return 0;
}
