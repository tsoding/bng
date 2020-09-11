#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
#include "./bng.h"




struct Bng_Pixel_Format pixel_format_by_name(const char *name)
{
    struct Bng_Pixel_Format result = {0};
    size_t n = strlen(name);
    if (n > 4) n = 4;

    for (size_t i = 0; i < n; ++i) {
        switch (name[i]) {
        case 'R':
            result.red_byte = i;
            break;
        case 'G':
            result.green_byte = i;
            break;
        case 'B':
            result.blue_byte = i;
            break;
        case 'A':
            result.alpha_byte = i;
            break;
        default: {}
        }
    }

    return result;
}

#ifdef TEST
int test_convert_pixel()
{
#define TEST_CASE(input, source, desired, expected)                 \
    do {                                                            \
        uint32_t actual = convert_pixel(input, source, desired);    \
        if (actual != expected) {                                   \
            printf("%s:%d: Oopsie-doopsie!\n", __FILE__, __LINE__); \
            printf("Actual: %08X\n", actual);                       \
            printf("Expected: %08X\n", expected);                   \
            exit(1);                                                \
        }                                                           \
        printf("%08X == %08X, OK\n", actual, expected);             \
    } while (0)

    TEST_CASE(0xAABBCCDD, RGBA, ABGR, 0xDDCCBBAA);
    TEST_CASE(0xAABBCCDD, ABGR, GRAB, 0xCCDDAABB);
    TEST_CASE(0xAABBCCDD, RGBA, GRAB, 0xBBAADDCC);
#undef TEST_CASE
}

int test_pixel_format_by_name()
{
    assert(bng_pixel_format_equals(pixel_format_by_name("RGBA"), RGBA));
    assert(bng_pixel_format_equals(pixel_format_by_name("ABGR"), ABGR));
    assert(bng_pixel_format_equals(pixel_format_by_name("GRAB"), GRAB));
    return 0;
}

int main(int argc, char *argv[])
{
    test_convert_pixel();
    test_pixel_format_by_name();
    return 0;
}

#else

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
#endif
