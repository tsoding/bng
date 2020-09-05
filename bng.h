#ifndef BNG_H_
#define BNG_H_

#define BNG_MAGIC 0x21474E42

struct Bng
{
    uint32_t magic;
    uint32_t width;
    uint32_t height;
    uint8_t data[];
};

#endif  // BNG_H_
