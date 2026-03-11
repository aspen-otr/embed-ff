#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>

#if RAND_MAX <= 65535
#error "RAND_MAX <= 65535 not supported, must be at least bigger than 16 bits."
#endif

uint64_t random_pixel_rgba(void);
uint16_t random_u16(void);

void write_u16(FILE *, uint16_t);
void write_u32(FILE *, uint32_t);

void die(const char *s);

int main(void)
{
    FILE *fp = fopen("image.ff", "wb");
    if (fp == NULL) die("failed to open image.ff");

    srand(time(NULL));

    const uint32_t width = 1920;
    const uint32_t height = 1080;

    const int opaque = 1;

    fwrite("farbfeld", 1, (sizeof("farbfeld") - 1), fp);
    write_u32(fp, width); // width
    write_u32(fp, height); // height

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            write_u16(fp, random_u16());
            write_u16(fp, random_u16());
            write_u16(fp, random_u16());

            if (opaque) write_u16(fp, 0xFFFF);
            else write_u16(fp, random_u16());
        }
    }

    fclose(fp);
}

uint16_t random_u16(void)
{
    return rand() & 0xffffL;
}

void write_u16(FILE *fp, uint16_t n)
{
    uint16_t m = htons(n);
    fwrite((uint8_t *)&m, 1, sizeof(uint16_t), fp);
}
void write_u32(FILE *fp, uint32_t n)
{
    uint32_t m = htonl(n);
    fwrite((uint8_t *)&m, 1, sizeof(uint32_t), fp);
}

void die(const char *s)
{
    perror(s);
    exit(1);
}
