//#include <stdio.h>
#include <iostream>
//#include <stdint.h>
#include <cstdint>
#include <cstdlib>
//#include <stdlib.h>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

// Define the SPI device path
#define SPI_DEVICE_PATH "/dev/spidev0.0"

int main(int argc, char **argv) {

    if (argc<2 )
    {
      perror("Error:  Missing argument: ID[0-11]\n");
      exit(EXIT_FAILURE);
    }
    int spi_fd;
    uint8_t tx_buffer[1] = {*argv[1]-48};
    uint8_t rx_buffer[1];

    // Open the SPI device
    spi_fd = open(SPI_DEVICE_PATH, O_RDWR);
    if (spi_fd < 0) {
        perror("Error opening SPI device");
        return 1;
    }

    // Set SPI mode and speed
    uint8_t mode = SPI_MODE_0;
    uint32_t speed = 1000000;

    if (ioctl(spi_fd, SPI_IOC_WR_MODE, &mode) == -1) {
        perror("Error setting SPI mode");
        return 1;
    }

    if (ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1) {
        perror("Error setting SPI speed");
        return 1;
    }

    // Transfer data to the SPI device
    struct spi_ioc_transfer transfer = {
        .tx_buf = (unsigned long)tx_buffer,
        .rx_buf = (unsigned long)rx_buffer,
        .len = sizeof(tx_buffer),
        .speed_hz = speed,
        .delay_usecs = 0,
        .bits_per_word = 8,
    };

    if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &transfer) < 0) {
        perror("Error transferring SPI data");
        return 1;
    }

    // Print received data
    std::cout << "Received data: ";
    for (int i = 0; i < sizeof(rx_buffer); i++) {
        printf("%d ", rx_buffer[i]);
    }
// %02X
    std::cout << "\n";

    // Close the SPI device
    close(spi_fd);

    return 0;
}

