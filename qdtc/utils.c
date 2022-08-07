#include "utils.h"

void format_number(char *buf, uint8_t num) {
    buf[0] = 0x20;
    buf[1] = 0x20;
    buf[3] = 0x0;
    if (num < 10) {
        buf[2] = num + 0x30;
    } else if (num < 100) {
        uint8_t dec = (num / 10);
        buf[1] = dec + 0x30;
        buf[2] = num - dec * 10 + 0x30;
    } else if (num < 1000) {
        uint8_t cen = (num / 100);
        buf[0] = cen + 0x30;
        num = num - cen * 100;
        uint8_t dec = (num / 10);
        buf[1] = dec + 0x30;
        buf[2] = num - dec * 10 + 0x30;
    }
}