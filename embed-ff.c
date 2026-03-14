#include "util.h"

int main(int argc, char **argv)
{
    if (argc < 2) u_die("usage: %s [data file]", argv[0]);
    FILE *data = fopen(argv[1], "rb");
    if (data == NULL) u_die("fopen:");

    uint32_t w, h;
    u_read_header(&w, &h);
    u_write_header(&w, &h);

    LOOP_CHANNELS(w, h) {
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

    if (data) fclose(data);
}

