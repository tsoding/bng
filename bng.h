#ifndef BNG_H_
#define BNG_H_

#define BNG_MAGIC 0x21474E42

#if defined(__GNUC__) || defined(__clang__)
#  define PACKED __attribute__((packed))
#else
#  warning "Packed attributes for struct is not implemented for this compiler. Feel free to fix that and submit a Pull Request to https://github.com/tsoding/bng"
#endif

struct Bng
{
    uint32_t magic;
    uint32_t width;
    uint32_t height;
    uint8_t red_byte;           // 0
    uint8_t green_byte;         // 1
    uint8_t blue_byte;          // 2
    uint8_t alpha_byte;         // 3
    uint8_t data[];
} PACKED;

#endif  // BNG_H_
