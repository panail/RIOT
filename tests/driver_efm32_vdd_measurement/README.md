## About
This is a test application for the EFM32 VDD Measurement using ADC. It can measure
voltage.

## Usage
The application will initialize the EFM32 VDD Measurement device.

After initialization, every 2 seconds, the application:
* reads and displays the voltage (V);

## Overruling default parameters

If your devie is at a different ADC Line than the default (VDD_MEASS_LINE) you
can build the test as follows:

    export CFLAGS=-DEFM32_VDD_MEASUREMENT_PARAM_ADC_LINE=ADC_LINE(2)
    BOARD=tk-mprs01v3 make -C tests/driver_efm32_vdd_measurement
