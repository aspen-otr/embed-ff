#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>

void write_u8(FILE *, uint8_t);

uint16_t read_u16(FILE *);
uint32_t read_u32(FILE *);

void die(const char *s);

int main(void)
{
    FILE *fp = fopen("altered.ff", "rb");
    FILE *lb = fopen("low-bytes.bin", "wb");
    if (fp == NULL) die("Cannot open altered.ff");
    if (lb == NULL) die("Cannot open low-bytes.bin");

    char farbfeld[8] = "farbfeld";
    fread(farbfeld, 1, sizeof(farbfeld), fp);

    uint32_t width = read_u32(fp);
    uint32_t height = read_u32(fp);

    for (uint32_t h = 0; h < height; h++) {
        for (uint32_t w = 0; w < width; w++) {
            for (int c = 0; c < 4; c++) {
                uint16_t px = read_u16(fp);
                uint8_t masked = px & 0xff;
                write_u8(lb, masked);
            }
        }
    }

    fclose(lb);
    fclose(fp);
}

uint16_t random_u16(void)
{
    return rand() & 0xffffL;
}

void write_u8(FILE *fp, uint8_t n)
{
    fwrite(&n, 1, sizeof(uint8_t), fp);
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
