/* Jordan Ebel */

#ifndef _IO_SPA_H
#define _IO_SPA_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#ifdef PLATFORM_LINUX
#include <linux/i2c-dev.h>
#include <linux/spi/spidev.h>
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
    const char *bus;  // Linux only
    int bus_fd;       // Linux only
} IO_SPA_I2C_PARAMS;

IO_SPA_RC io_spa_i2c_init(IO_SPA_I2C_PARAMS *params);
IO_SPA_RC io_spa_i2c_read(IO_SPA_I2C_PARAMS *params, uint8_t addr, uint8_t num_bytes, uint8_t *data);
IO_SPA_RC io_spa_i2c_read_short(IO_SPA_I2C_PARAMS *params, uint8_t num_bytes, uint8_t *data);
IO_SPA_RC io_spa_i2c_write(IO_SPA_I2C_PARAMS *params, uint8_t addr, uint8_t num_bytes, uint8_t *data);
IO_SPA_RC io_spa_i2c_write_short(IO_SPA_I2C_PARAMS *params, uint8_t data);
IO_SPA_RC io_spa_i2c_close(IO_SPA_I2C_PARAMS *params);
/*********************/


/******** SPI ********/
typedef struct
{
    const char *bus;
    int bus_fd;             // Linux only
    uint8_t bits_per_word;
    uint32_t max_speed_hz;
    bool lsb_first;
    bool clk_sample_falling_edge;
    bool clk_idle_high;
    bool three_wire;
    bool no_chip_select;

    /* Internal parameters */
#ifdef PLATFORM_LINUX
    uint32_t _num_transfers;
    struct spi_ioc_transfer *_transfers;
#endif
} IO_SPA_SPI_PARAMS;

IO_SPA_RC io_spa_spi_init(IO_SPA_SPI_PARAMS *params);
IO_SPA_RC io_spa_spi_add_transfer(IO_SPA_SPI_PARAMS *params, uint8_t *read_buf, uint8_t *write_buf, uint32_t len, bool cs_change, uint16_t cs_change_delay_us);
IO_SPA_RC io_spa_spi_send_transfers(IO_SPA_SPI_PARAMS *params);
IO_SPA_RC io_spa_spi_read(IO_SPA_SPI_PARAMS *params, uint8_t *buf, uint32_t len);
IO_SPA_RC io_spa_spi_write(IO_SPA_SPI_PARAMS *params, uint8_t *buf, uint32_t len);
IO_SPA_RC io_spa_spi_read_write(IO_SPA_SPI_PARAMS *params, uint8_t *read_buf, uint8_t *write_buf, uint32_t len);
IO_SPA_RC io_spa_spi_close(IO_SPA_SPI_PARAMS *params);
/*********************/


#endif /* _IO_SPA_H */

