## About
This is a test application for the Battery Monitor using ADC. It can
measure voltage.

## Usage
The application will initialize the Battery Monitor device.

After initialization, every 2 seconds, the application:
* reads and displays the voltage (V);

## Overruling default parameters

If your device is at a different ADC Line than the default (BATT_MEASS_LINE)
you can build the testa as follows:

    export CFLAGS=-DBATTERY_MONITOR_PARAM_ADC_LINE=ADC_LINE(1)
    BOARD=tk-mprs01v3 make -C tests/driver_battery_monitor
