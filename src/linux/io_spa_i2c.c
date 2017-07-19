/* Jordan Ebel */

#ifdef PLATFORM_LINUX

#include "io_spa.h"

IO_SPA_RC io_spa_i2c_init(IO_SPA_I2C_PARAMS *params)
{
    params->bus_fd = open(params->bus, O_RDWR);
    if (params->bus_fd < 0)
    {
        perror("Open");
        return IO_SPA_ERROR;
    }

    if (ioctl(params->bus_fd, I2C_SLAVE, params->dev_addr) < 0)
    {
        perror("Ioctl");
        close(params->bus_fd);
        return IO_SPA_ERROR;
    }

    return IO_SPA_OK;
}

IO_SPA_RC io_spa_i2c_read(IO_SPA_I2C_PARAMS *params, uint8_t addr, uint8_t num_bytes, uint8_t *data)
{
    if (io_spa_i2c_write_short(params, addr) != IO_SPA_OK)
    {
        return IO_SPA_ERROR;
    }

    if (read(params->bus_fd, data, num_bytes) != num_bytes)
    {
        perror("Read");
        return IO_SPA_ERROR;
    }

    return IO_SPA_OK;
}

IO_SPA_RC io_spa_i2c_read_short(IO_SPA_I2C_PARAMS *params, uint8_t num_bytes, uint8_t *data)
{
    if (read(params->bus_fd, data, num_bytes) != num_bytes)
    {
        perror("Read");
        return IO_SPA_ERROR;
    }

    return IO_SPA_OK;
}

IO_SPA_RC io_spa_i2c_write(IO_SPA_I2C_PARAMS *params, uint8_t addr, uint8_t num_bytes, uint8_t *data)
{
    char buf[num_bytes+1];
    buf[0] = addr;
    for (int i = 0; i < num_bytes; i++)
    {
        buf[num_bytes-i] = data[i];
    }

    if (write(params->bus_fd, buf, num_bytes+1) != num_bytes+1)
    {
        perror("Write");
        return IO_SPA_ERROR;
    }

    return IO_SPA_OK;
}

IO_SPA_RC io_spa_i2c_write_short(IO_SPA_I2C_PARAMS *params, uint8_t data)
{
    uint8_t num_bytes = 1;
    if (write(params->bus_fd, &data, num_bytes) != num_bytes)
    {
        perror("Write");
        return IO_SPA_ERROR;
    }

    return IO_SPA_OK;
}

IO_SPA_RC io_spa_i2c_close(IO_SPA_I2C_PARAMS *params)
{
    close(params->bus_fd);
    return IO_SPA_OK;
}

#endif /* PLATFORM_LINUX */

