#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "bng.h"

void test_convert_pixel()
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

void test_pixel_format_by_name()
{
#define TEST_CASE(input, expected)\
    do {\
        const struct Bng_Pixel_Format actual = pixel_format_by_name(input);\
        if (!bng_pixel_format_equals(expected, actual)) {\
            fprintf(stderr, "%s:%d: Oopsie-doopsie!\n", __FILE__, __LINE__);\
            fprintf(stderr, "Actual: %s\n", name_of_pixel_format(actual));\
            fprintf(stderr, "Expected: %s\n", name_of_pixel_format(expected));\
            exit(1);\
        }\
        printf("%s == %s, OK\n", name_of_pixel_format(actual).cstr, name_of_pixel_format(expected).cstr);\
    } while(0);

    TEST_CASE("RGBA", RGBA);
    TEST_CASE("ABGR", ABGR);
    TEST_CASE("GRAB", GRAB);
#undef TEST_CASE
}

int main(int argc, char *argv[])
{
    test_convert_pixel();
    test_pixel_format_by_name();
    return 0;
}

