## About
This is a test application for the MS5607 sensor. It can measure temperature
and air pressure.

## Usage
The application will initialize the MS5607 device and display its calibration
coefficients.

Notice that it is necessary to first read the temperature even if only air
pressure is needed.

After initialization, every 2 seconds, the application:
* reads and displays the temperature (°C);
* reads and displays the air pressure (hPa);

## Overruling default parameters

If your device is at a different I2C address than the default (0x77) you can
build the test as follows:

    export CFLAGS=-DMS5607_PARAM_I2C_ADDR=0x76
    BOARD=tk-mprs01v3 make -C tests/driver_ms5607
