#ifndef _EMBED_FF_H
#define _EMBED_FF_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

// can use i,j,c if necessary (see random-ff.c)
#define LOOP_CHANNELS(WIDTH, HEIGHT) \
    for (uint32_t i = 0; i < (HEIGHT); i++) \
        for (uint32_t j = 0; j < (WIDTH); j++) \
            for (int c = 0; c < 4; c++)

void u_read_header(uint32_t *width, uint32_t *height);
void u_write_header(uint32_t *width, uint32_t *height);

uint8_t u_r8(void);
uint16_t u_r16(void);
uint32_t u_r32(void);
void u_w8(uint8_t n);
void u_w16(uint16_t n);
void u_w32(uint32_t n);

void u_read(void *p, size_t s, size_t n, FILE *f);
void u_write(void *p, size_t s, size_t n, FILE *f);

size_t u_try_read(void *p, size_t s, size_t n, FILE *f);

void u_die(const char *fmt, ...);

#endif // _EMBED_FF_H
