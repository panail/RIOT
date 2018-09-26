## About
This is a test application for the M24512 EEPROM.

## Usage
The application will initialize the M24512 EEPROM device.

After initialization, the application:
* writes the message {0..255} into the EEPROM
* reads the message from the EEPROM
* prints the read message into the terminal

If your device is at a different I2C address than the default (0x50) you
can build the test as follows:

    export CFLAGS=-DM24512_PARAM_I2C_ADDR=0x51
    BOARD=tk-mprs01v3 make -C tests/driver_m24512
