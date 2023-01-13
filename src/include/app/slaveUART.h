#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

int enableSlaveUART() {

     // Open UART port on the Slave Raspberry Pi
    int uart_fd_slave = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);


    if (uart_fd_slave == -1) {
            printf("Error opening UART.\n");
            return -1;
    }

    // Configure UART port on both Raspberry Pi's
	struct termios options;
	tcgetattr(uart_fd_slave, &options);
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart_fd_slave, TCIFLUSH);
	tcsetattr(uart_fd_slave, TCSANOW, &options);

    // Send random serialized string
    std::string data = "HelloWorld";
    
    // Send data over UART on slave
    while(true) {
        int bytes_written = write(uart_fd_slave, data.c_str(), data.length());

        // Check for errors
        if (bytes_written < 0) {
            printf("No data sent to the Master.\n");
        }

         if (bytes_written >= 0) {
            printf("Successfully sent data to the Master.\n");
        }

        sleep(5);
    }

    return 0;
}









