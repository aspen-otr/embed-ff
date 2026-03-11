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

uint16_t read_u16(FILE *);
uint32_t read_u32(FILE *);

void die(const char *s);

int main(void)
{
    FILE *fp = fopen("image.ff", "rb");
    FILE *wf = fopen("altered.ff", "wb");
    FILE *rf = fopen("data.bin", "rb");
    if (fp == NULL) die("failed to open image.ff");
    if (wf == NULL) die("failed to open altered.ff");
    if (rf == NULL) die("failed to open data.bin");

    char farbfeld[8] = "farbfeld";

    fread(farbfeld, 1, sizeof(farbfeld), fp); // clear FF header of image.ff
    fwrite(farbfeld, 1, sizeof(farbfeld), wf); // set FF header of new file.

    uint32_t width = read_u32(fp);
    uint32_t height = read_u32(fp);

    write_u32(wf, width);
    write_u32(wf, height);

    int done_with_data = 0;

    for (uint32_t i = 0; i < width; i++) {
        for (uint32_t j = 0; j < height; j++) {
            for (int c = 0; c < 4; c++) {
                uint16_t pix = read_u16(fp);

                if (done_with_data) {
                    write_u16(wf, pix);
                    continue;
                }

                uint8_t byte;
                if (fread(&byte, sizeof(uint8_t), 1, rf) != 1) {
                    done_with_data = 1; // error OR EOF doesn't matter.
                    write_u16(wf, pix);
                    continue;
                }

                write_u16(wf, (pix &~ 0xFFL) | (uint16_t)byte);
            }
        }
    }

    fclose(fp);
    fclose(rf);
    fclose(wf);
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

uint16_t read_u16(FILE *fp)
{
    uint16_t rv;
    if (fread(&rv, sizeof(uint16_t), 1, fp) != 1) die("error reading u16");
    return ntohs(rv);
}
uint32_t read_u32(FILE *fp)
{
    uint32_t rv;
    if (fread(&rv, sizeof(uint32_t), 1, fp) != 1) die("error reading u32");
    return ntohl(rv);
}

void die(const char *s)
{
    perror(s);
    exit(1);
}
