#ifndef SEMIHOST_H
#define SEMIHOST_H

#include "mbed.h"
#include "platform/mbed_semihost_api.h"

inline void
semihost_putchar(int c) {
    unsigned char s = c;
    semihost_write(2, &s, 1, 0);
}

inline void
semihost_puts(const char *s) {
    semihost_write(2, (unsigned char *)s, strlen(s), 0);
}

void
semihost_printf(const char *format, ...);

#endif
