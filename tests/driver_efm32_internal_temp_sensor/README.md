## About
This is a test application for the EFM32 Internal Temp Sensor using ADC.
It can measure temperature.

## Usage
The application wil initialize the EFM32 Internal Temp Sensor device.

After initialization, every 2 seconds, the application:
* reads and displays the temperature (°C);

## Overruling default parameters

If your device is at a different ADC Line than the default
(INTERNAL_TEMP_SENSOR_MEASS_LINE) you can build the test as follows:

    export CFLAGS=-DEFM32_INTERNAL_TEMP_SENSOR_PARAM_ADC_LINE=ADC_LINE(1)
    BOARD=tk-mprs01v3 make -C tests/driver_efm32_internal_temp_sensor
