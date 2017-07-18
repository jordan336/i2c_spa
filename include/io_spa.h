/* Jordan Ebel */

#ifndef _IO_SPA_H
#define _IO_SPA_H

#ifdef PLATFORM_LINUX
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#endif

typedef enum
{
    IO_SPA_OK    = 0,
    IO_SPA_ERROR = 1
} IO_SPA_RC;

#endif /* _IO_SPA_H */

