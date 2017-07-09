/*
 * 
 */

#ifdef PLATFORM_LINUX

#include "i2c_spa.h"

I2C_SPA_RC i2c_spa_init(I2C_SPA_PARAMS *params)
{
    return I2C_SPA_OK;
}

I2C_SPA_RC i2c_spa_read_bytes(I2C_SPA_PARAMS *params, uint8_t addr, uint8_t num, uint8_t *data)
{
    return I2C_SPA_OK;
}

I2C_SPA_RC i2c_spa_write_bytes(I2C_SPA_PARAMS *params, uint8_t addr, uint8_t num, uint8_t *data)
{
    return I2C_SPA_OK;
}

I2C_SPA_RC i2c_spa_close(I2C_SPA_PARAMS *params)
{
    return I2C_SPA_OK;
}

#endif /* PLATFORM_LINUX */

