Example Description

This example describes how to use SPI stream read/write by mbed api.


The SPI Interface provides a "Serial Peripheral Interface" Master.

This interface can be used for communication with SPI slave devices,
such as FLASH memory, LCD screens and other modules or integrated circuits.


In this example, we use config SPI_IS_AS_MASTER to decide if device is master or slave.
    If SPI_IS_AS_MASTER is 1, then device is master.
    If SPI_IS_AS_MASTER is 0, then device is slave.

We connect wires as below:
    master's MOSI (PG_2) connect to slave's MOSI (PG_2) 
    master's MISO (PG_3) connect to slave's MISO (PG_3) 
    master's SCLK (PG_1) connect to slave's SCLK (PG_1) 
    master's CS   (PG_0) connect to slave's CS   (PG_0) 

This example shows master sends data to slave.
We bootup slave first, and then bootup master.
Then log will presents that master sending data to slave.
To ensure the order is correct, we use a GPIO pin to notify the master that the slave device is ready to write or read data.