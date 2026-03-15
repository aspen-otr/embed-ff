#include <stdlib.h>
#include <string.h>

#include "util.h"

int main(int argc, char **argv)
{
    if (argc == 1 || argc == 3)
        u_die("usage: %s [-offset OFFSET] [FILE]", argv[0]);

    int file_index = (argc < 4) ? 1 : 3;
    FILE *data = fopen(argv[file_index], "rb");
    if (data == NULL) u_die("fopen:");

    uint32_t offset;
    if (file_index == 1) offset = 0;
    else {
        if (strcmp(argv[1], "-offset"))
            u_die("usage: %s [-offset OFFSET] [FILE]", argv[0]);
        offset = atol(argv[2]);
    }

    uint32_t w, h;
    u_read_header(&w, &h);
    u_write_header(&w, &h);

    uint32_t cur = 0;
    LOOP_CHANNELS(w, h) {
        uint16_t pix = u_r16();
        if (data == NULL || cur < offset) {
            u_w16(pix);
            cur++;
            continue;
        }

        uint8_t byte;
        if (u_try_read(&byte, 1, 1, data) < 1) {
            fclose(data);
            data = NULL;
            u_w16(pix);
            continue;
        }

        u_w16((pix & ~ 0xffL) | byte);
    }

    if (data) fclose(data);
}
