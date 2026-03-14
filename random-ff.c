#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "util.h"

#if RAND_MAX <= 65535
#error "RAND_MAX <= 65535 not supported, must be at least bigger than 16 bits."
#endif

uint64_t random_pixel_rgba(void);
uint16_t random_u16(void);

int main(int argc, char **argv)
{
    srand(time(NULL));

    uint32_t width = 1920;
    uint32_t height = 1080;

    int arg = 1;
    while (arg < (argc - 1)) {
        if (strcmp(argv[arg], "-w") == 0) width = atol(argv[++arg]);
        else if (strcmp(argv[arg], "-h") == 0) height = atol(argv[++arg]);

        arg++;
    }

    const int opaque = 1;

    u_write_header(&width, &height);
    for (uint32_t h = 0; h < height; h++) {
        for (uint32_t w = 0; w < width; w++) {
            for (int c = 0; c < 4; c++) {
                if ((c & 3) == 3 && opaque) u_w16(0xffffL);
                else u_w16(random_u16());
            }
        }
    }
}

uint16_t random_u16(void)
{
    return rand() & 0xffffL;
}

