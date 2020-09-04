#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
#include "./bng.h"

int main()
{
    int x, y, n;
    unsigned char *data = stbi_load("./tsodinw.png", &x, &y, &n, 4);
    assert(data != NULL);

    struct Bng bng = {};
    bng.magic = BNG_MAGIC;
    bng.width = x;
    bng.height = y;

    FILE *out = fopen("./tsodinw.bng", "wb");
    fwrite(&bng, 1, sizeof(bng), out);
    fwrite(data, 1, x * y * 4, out);
    fclose(out);

    return 0;
}
