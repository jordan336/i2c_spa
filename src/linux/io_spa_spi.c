/* Jordan Ebel */

#ifdef PLATFORM_LINUX

#include "io_spa.h"

IO_SPA_RC io_spa_spi_init(IO_SPA_SPI_PARAMS *params)
{
    uint8_t bits_per_word = params->bits_per_word;
    uint32_t max_speed = params->max_speed_hz;
    uint8_t mode = 0x0;

    params->bus_fd = open(params->bus, O_RDWR);
    if (params->bus_fd < 0)
    {
        perror("Open");
        return IO_SPA_ERROR;
    }

    /* Bits per word */
    if (ioctl(params->bus_fd, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word) < 0)
    {
        perror("Ioctl (BITS_PER_WORD)");
        return IO_SPA_ERROR;
    }

    /* Max speed */
    if (ioctl(params->bus_fd, SPI_IOC_WR_MAX_SPEED_HZ, &max_speed) < 0)
    {
        perror("Ioctl (MAX_SPEED_HZ)");
        return IO_SPA_ERROR;
    }

    /* Mode */
    if (params->lsb_first) mode |= SPI_LSB_FIRST;
    if (params->clk_sample_falling_edge) mode |= SPI_CPHA;
    if (params->clk_idle_high) mode |= SPI_CPOL;
    if (params->three_wire) mode |= SPI_3WIRE;
    if (params->no_chip_select) mode |= SPI_NO_CS;
    if (ioctl(params->bus_fd, SPI_IOC_WR_MODE, &mode) < 0)
    {
        perror("Ioctl (Mode)");
        return IO_SPA_ERROR;
    }

    return IO_SPA_OK;
}

IO_SPA_RC io_spa_spi_add_transfer(IO_SPA_SPI_PARAMS *params, uint8_t *read_buf, uint8_t *write_buf, uint32_t len, bool cs_change, uint16_t cs_change_delay_us)
{
    uint32_t num_transfers = params->_num_transfers;
    uint32_t num_transfer_bytes = num_transfers * sizeof(struct spi_ioc_transfer);

    /* Allocate new transfer struct, copy old structs */
    struct spi_ioc_transfer *new_transfers = malloc(num_transfer_bytes + sizeof(struct spi_ioc_transfer));

    memcpy(new_transfers, params->_transfers, num_transfer_bytes);
    free(params->_transfers);
    params->_transfers = new_transfers;
    params->_num_transfers++;

    /* Set up new transfer struct */
    struct spi_ioc_transfer *new_transfer = params->_transfers + num_transfers;
    memset(new_transfer, 0x0, sizeof(struct spi_ioc_transfer));
    new_transfer->tx_buf = (uint32_t)write_buf;
    new_transfer->rx_buf = (uint32_t)read_buf;
    new_transfer->len = len;
    new_transfer->cs_change = cs_change;
    new_transfer->delay_usecs = cs_change_delay_us;

    return IO_SPA_OK;
}

IO_SPA_RC io_spa_spi_send_transfers(IO_SPA_SPI_PARAMS *params)
{
    if (ioctl(params->bus_fd, SPI_IOC_MESSAGE(params->_num_transfers), params->_transfers) < 0)
    {
        perror("Ioctl (SPI_IOC_MESSAGE)");
        return IO_SPA_ERROR;
    }

    free(params->_transfers);
    params->_transfers = NULL;
    params->_num_transfers = 0;

    return IO_SPA_OK;
}

IO_SPA_RC io_spa_spi_read(IO_SPA_SPI_PARAMS *params, uint8_t *buf, uint32_t len)
{
    return IO_SPA_OK;
}

IO_SPA_RC io_spa_spi_write(IO_SPA_SPI_PARAMS *params, uint8_t *buf, uint32_t len)
{
    return IO_SPA_OK;
}

IO_SPA_RC io_spa_spi_read_write(IO_SPA_SPI_PARAMS *params, uint8_t *read_buf, uint8_t *write_buf, uint32_t len)
{
    return IO_SPA_OK;
}

IO_SPA_RC io_spa_spi_close(IO_SPA_SPI_PARAMS *params)
{
    close(params->bus_fd);
    free(params->_transfers);
    params->_transfers = NULL;
    params->_num_transfers = 0;
    return IO_SPA_OK;
}

#endif /* PLATFORM_LINUX */

