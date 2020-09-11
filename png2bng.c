#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
#include "./bng.h"

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "png2bng <input.png> <output.bng>\n");
        exit(1);
    }

    const char *input_filepath = argv[1];
    const char *output_filepath = argv[2];

    int x, y, n;
    unsigned char *data = stbi_load(input_filepath, &x, &y, &n, 4);
    assert(data != NULL);

    struct Bng bng = {
        .magic      = BNG_MAGIC,
        .width      = x,
        .height     = y,
        .red_byte   = 0,
        .green_byte = 1,
        .blue_byte  = 2,
        .alpha_byte = 3,
    };

    FILE *out = fopen(output_filepath, "wb");
    fwrite(&bng, 1, sizeof(bng), out);
    fwrite(data, 1, x * y * 4, out);
    fclose(out);

    return 0;
}
