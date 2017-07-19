/* Jordan Ebel */

#ifndef _IO_SPA_H
#define _IO_SPA_H

#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef PLATFORM_LINUX
#include <linux/i2c-dev.h>
#endif

typedef enum
{
    IO_SPA_OK    = 0,
    IO_SPA_ERROR = 1
} IO_SPA_RC;


/******** I2C ********/
typedef struct
{
    uint8_t dev_addr;
#ifdef PLATFORM_LINUX
    const char *bus;
    int bus_fd;
#endif
} IO_SPA_I2C_PARAMS;

IO_SPA_RC io_spa_i2c_init(IO_SPA_I2C_PARAMS *params);
IO_SPA_RC io_spa_i2c_read(IO_SPA_I2C_PARAMS *params, uint8_t addr, uint8_t num_bytes, uint8_t *data);
IO_SPA_RC io_spa_i2c_read_short(IO_SPA_I2C_PARAMS *params, uint8_t num_bytes, uint8_t *data);
IO_SPA_RC io_spa_i2c_write(IO_SPA_I2C_PARAMS *params, uint8_t addr, uint8_t num_bytes, uint8_t *data);
IO_SPA_RC io_spa_i2c_write_short(IO_SPA_I2C_PARAMS *params, uint8_t data);
IO_SPA_RC io_spa_i2c_close(IO_SPA_I2C_PARAMS *params);


#endif /* _IO_SPA_H */

