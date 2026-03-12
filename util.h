#ifndef _EMBED_FF_H
#define _EMBED_FF_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

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
