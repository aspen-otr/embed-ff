#include "util.h"

int main(void)
{
    uint32_t w, h;
    u_read_header(&w, &h);

    LOOP_CHANNELS(w, h) {
        uint16_t pix = u_r16();
        uint8_t low = pix & 0xff;
        u_w8(low);
    }
}
