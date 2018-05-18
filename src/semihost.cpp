#include "mbed.h"
#include "semihost.h"

#ifdef DEVICE_LOCALFILESYSTEM

void
semihost_printf(const char *format, ...) {
    char buf[100];
    va_list ap;
    va_start(ap, format);
    vsnprintf(buf, sizeof(buf), format, ap);
    semihost_puts(buf);
    va_end(ap);
}

#endif
