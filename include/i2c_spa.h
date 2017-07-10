/* 
 *
 */

#ifndef _I2C_SPA_H
#define _I2C_SPA_H

#ifdef PLATFORM_LINUX
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#endif

typedef enum
{
    I2C_SPA_OK,
    I2C_SPA_ERROR
} I2C_SPA_RC;

typedef struct
{
    uint8_t dev_addr;
#ifdef PLATFORM_LINUX
    const char *bus;
    int bus_fd;
#endif
} I2C_SPA_PARAMS;


I2C_SPA_RC i2c_spa_init(I2C_SPA_PARAMS *params);
I2C_SPA_RC i2c_spa_read(I2C_SPA_PARAMS *params, uint8_t num_bytes, uint8_t *data);
I2C_SPA_RC i2c_spa_write_quick(I2C_SPA_PARAMS *params, uint8_t data);
I2C_SPA_RC i2c_spa_write(I2C_SPA_PARAMS *params, uint8_t addr, uint8_t num_bytes, uint8_t *data);
I2C_SPA_RC i2c_spa_close(I2C_SPA_PARAMS *params);

#endif /* _I2C_SPA_H */

