#include "util.h"

#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

void u_read_header(uint32_t *width, uint32_t *height)
{
    uint8_t header[8];
    u_read(header, sizeof(uint8_t), sizeof(header), stdin);
    if (strncmp(header, "farbfeld", 8)) u_die("error: bad magic value");

    u_read(width, sizeof(uint32_t), 1, stdin);
    u_read(height, sizeof(uint32_t), 1, stdin);

    *width = ntohl(*width);
    *height = ntohl(*height);
}

void u_write_header(uint32_t *width, uint32_t *height)
{
    uint32_t w = htonl(*width), h = htonl(*height);
    u_write("farbfeld", 1, sizeof("farbfeld") - 1, stdout);
    u_write(&w, sizeof(uint32_t), 1, stdout);
    u_write(&h, sizeof(uint32_t), 1, stdout);
}

uint8_t u_r8(void)
{
    uint8_t n;
    u_write(&n, sizeof(uint8_t), 1, stdin);
    return n;
}
uint16_t u_r16(void)
{
    uint16_t n;
    u_read(&n, sizeof(uint16_t), 1, stdin);
    return ntohs(n);
}
uint32_t u_r32(void)
{
    uint32_t n;
    u_read(&n, sizeof(uint32_t), 1, stdin);
    return ntohl(n);
}
void u_w8(uint8_t n)
{
    u_write(&n, sizeof(uint8_t), 1, stdout);
}
void u_w16(uint16_t n)
{
    uint16_t w = htons(n);
    u_write(&w, sizeof(uint16_t), 1, stdout);
}
void u_w32(uint32_t n)
{
    uint32_t w = htonl(n);
    u_write(&w, sizeof(uint32_t), 1, stdout);
}

void u_read(void *p, size_t s, size_t n, FILE *f)
{
    if (fread(p, s, n, f) != n) {
        if (ferror(f)) {
            u_die("fread:");
        } else {
            u_die("fread: unexpected EOF");
        }
    }
}

void u_write(void *p, size_t s, size_t n, FILE *f)
{
    if (fwrite(p, s, n, f) != n) {
        u_die("fwrite:");
    }
}

size_t u_try_read(void *p, size_t s, size_t n, FILE *f)
{
    size_t read;
    if ((read = fread(p, s, n, f)) != n) {
        if (ferror(f)) {
            u_die("fread:");
        }
    }
    return read;
}

// https://git.suckless.org/farbfeld/file/util.c.html
void u_die(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);

    if (*fmt && fmt[strlen(fmt) - 1] == ':') {
        fputc(' ', stderr);
        perror(NULL);
    } else fputc('\n', stderr);

    va_end(ap);

    exit(EXIT_FAILURE);
}
