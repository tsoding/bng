#ifndef BNG_H_
#define BNG_H_

#define BNG_MAGIC 0x21474E42

#if defined(__GNUC__) || defined(__clang__)
#  define PACKED __attribute__((packed))
#else
#  warning "Packed attributes for struct is not implemented for this compiler. Feel free to fix that and submit a Pull Request to https://github.com/tsoding/bng"
#endif

struct Bng_Pixel_Format
{
    uint8_t red_byte;           // 0
    uint8_t green_byte;         // 1
    uint8_t blue_byte;          // 2
    uint8_t alpha_byte;         // 3
} PACKED;

int bng_pixel_format_equals(struct Bng_Pixel_Format a, struct Bng_Pixel_Format b)
{
    return a.red_byte == b.red_byte &&
        a.green_byte == b.green_byte &&
        a.blue_byte == b.blue_byte &&
        a.alpha_byte == b.alpha_byte;
}

const struct Bng_Pixel_Format RGBA = {0, 1, 2, 3};
const struct Bng_Pixel_Format ABGR = {3, 2, 1, 0};
const struct Bng_Pixel_Format GRAB = {1, 0, 3, 2};

struct Bng
{
    uint32_t magic;
    uint32_t width;
    uint32_t height;
    struct Bng_Pixel_Format pixel_format;
    uint32_t pixels[];
} PACKED;

#define GET_BYTE(bytes, index) ((bytes & (0xFF << ((4 - index - 1) * 8))) >> ((4 - index - 1) * 8))
#define SET_BYTE(bytes, index, byte) bytes = (bytes | (byte << ((4 - index - 1) * 8)))

uint32_t convert_pixel(uint32_t pixel,
                       struct Bng_Pixel_Format source,
                       struct Bng_Pixel_Format desired)
{
    uint32_t result = 0;
    SET_BYTE(result, desired.red_byte,   GET_BYTE(pixel, source.red_byte));
    SET_BYTE(result, desired.green_byte, GET_BYTE(pixel, source.green_byte));
    SET_BYTE(result, desired.blue_byte,  GET_BYTE(pixel, source.blue_byte));
    SET_BYTE(result, desired.alpha_byte, GET_BYTE(pixel, source.alpha_byte));
    return result;
}

#endif  // BNG_H_
