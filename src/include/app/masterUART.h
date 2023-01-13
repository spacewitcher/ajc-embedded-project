#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

int enableMasterUART() {

    // Open UART port on the Master Raspberry Pi
    int uart_fd_master = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);


    if (uart_fd_master == -1) {
            printf("Error opening UART.\n");
            return -1;
    }

    // Configure UART port on the Master Raspberry Pi's
    struct termios options;
    tcgetattr(uart_fd_master, &options);
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart_fd_master, TCIFLUSH);
	tcsetattr(uart_fd_master, TCSANOW, &options);


    while (true) {
        // receive data on master
	    char receiveBuffer[100];

        int bytes_read = read(uart_fd_master, receiveBuffer, sizeof(receiveBuffer));

        if (bytes_read < 0) {
            printf("No data received from the slave.\n");
        }

        if (bytes_read >= 0) {
            std::cout<<"Buffer received successfully: " <<receiveBuffer<<std::endl;
        }

        sleep(1);
    }

   return 0;
}