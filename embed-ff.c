#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>

#include "util.h"

int main(int argc, char **argv)
{
    if (argc < 2) u_die("embed-ff [data file]");
    FILE *data = fopen(argv[1], "rb");
    if (data == NULL) u_die("fopen:");

    uint32_t w, h;
    u_read_header(&w, &h);
    u_write_header(&w, &h);

    for (uint32_t i = 0; i < h; i++) {
        for (uint32_t j = 0; j < w; j++) {
            for (int c = 0; c < 4; c++) {
                uint16_t pix = u_r16();
                if (data == NULL) {
                    u_w16(pix);
                    continue;
                }

                uint8_t byte;
                if (u_try_read(&byte, 1, 1, data) < 1) {
                    fclose(data);
                    data = NULL;
                    u_w16(pix);
                    continue;
                }

                u_w16((pix &~ 0xffL) | byte);
            }
        }
    }

    if (data) fclose(data);
}

