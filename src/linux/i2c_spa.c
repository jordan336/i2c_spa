/*
 * 
 */

#ifdef PLATFORM_LINUX

#include "i2c_spa.h"

I2C_SPA_RC i2c_spa_init(I2C_SPA_PARAMS *params)
{
    params->bus_fd = open(params->bus, O_RDWR);
    if (params->bus_fd < 0)
    {
        perror("Open");
        return I2C_SPA_ERROR;
    }

    if (ioctl(params->bus_fd, I2C_SLAVE, params->dev_addr) < 0)
    {
        perror("Ioctl");
        close(params->bus_fd);
        return I2C_SPA_ERROR;
    }

    return I2C_SPA_OK;
}

I2C_SPA_RC i2c_spa_read(I2C_SPA_PARAMS *params, uint8_t num_bytes, uint8_t *data)
{
    if (read(params->bus_fd, data, num_bytes) != num_bytes)
    {
        perror("Read");
        return I2C_SPA_ERROR;
    }

    for (int i = 0; i < num_bytes/2; i++)
    {
        uint8_t temp = data[i];
        data[i] = data[num_bytes-i-1];
        data[num_bytes-i-1] = temp;
    }

    return I2C_SPA_OK;
}

I2C_SPA_RC i2c_spa_write_quick(I2C_SPA_PARAMS *params, uint8_t data)
{
    if (write(params->bus_fd, &data, 1))
    {
        perror("Write");
        return I2C_SPA_ERROR;
    }

    return I2C_SPA_OK;
}

I2C_SPA_RC i2c_spa_write(I2C_SPA_PARAMS *params, uint8_t addr, uint8_t num_bytes, uint8_t *data)
{
    char buf[num_bytes+1];
    buf[0] = addr;
    for (int i = 0; i < num_bytes; i++)
    {
        buf[num_bytes-i] = data[i];
    }

    if (write(params->bus_fd, buf, num_bytes+1))
    {
        perror("Write");
        return I2C_SPA_ERROR;
    }

    return I2C_SPA_OK;
}

I2C_SPA_RC i2c_spa_close(I2C_SPA_PARAMS *params)
{
    close(params->bus_fd);
    return I2C_SPA_OK;
}

#endif /* PLATFORM_LINUX */

