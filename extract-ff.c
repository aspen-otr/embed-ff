#include "util.h"

int main(void)
{
    uint32_t w, h;
    u_read_header(&w, &h);

    for (uint32_t i = 0; i < h; i++) {
        for (uint32_t j = 0; j < w; j++) {
            for (int c = 0; c < 4; c++) {
                uint16_t pix = u_r16();
                uint8_t low = pix & 0xff;
                u_w8(low);
            }
        }
    }
}
