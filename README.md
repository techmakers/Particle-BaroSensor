# Particle-BaroSensor Library
Barometric sensor library for Particle.io (Spark.io) Photon
Ported from [https://github.com/freetronics/BaroSensor]()

# BaroSensor Library

This is a Particle.io Library for the for the MS5637-02BA03 Altimeter/Pressure sensor.

# Known Issues

No known issues at the moment (2015-11-16). Just tested with some sample code.

# All Available Functions

## begin()

Usage:

    BaroSensor.begin()

Call this in the `setup()` part of your sketch to initialise the BARO module. If the module later returns any errors for some reason, calling `begin()` again will reset it.

## getTemperature()

Takes a temperature reading and returns it.

### Function signature:

    float getTemperature(TempUnit scale = CELSIUS,
                         BaroOversampleLevel level = OSR_8192);

### Basic Usage:

    float temp = BaroSensor.getTemperature();

### Advanced Usage:

     float temp = BaroSensor.getTemperature(FAHRENHEIT, OSR_1024);

### Arguments:

* `scale` default to CELSIUS but can be set to FAHRENHEIT if needed.
* `level` specifies the oversampling level of the sensor. Higher
  oversampling means higher accuracy but a slower reading. OSR_8192 is
  the default and gives highest accuracy, however
  a temperature reading takes 17 milliseconds. OSR_256 is the lowest
  accuracy, a temperature reading takes 1 millisecond. Intermediate
  values are OSR_512, OSR_1024, OSR_2048, OSR_4096.

### Returns

Either the temperature value as a floating point number, or -9999 if an error occurred.

## getPressure()

Takes an air pressure reading and returns it

### Function signature:

    float getPressure(BaroOversampleLevel level = OSR_8192);

### Basic Usage:

    float pressure = BaroSensor.getPressure();

### Arguments

* `level` specifies the oversampling level of the sensor. Higher
  oversampling means higher accuracy but a slower reading. OSR_8192 is
  the default and gives highest accuracy, however a pressure reading
  takes 34 milliseconds. OSR_256 is the lowest accuracy, a pressure
  reading takes 2 milliseconds. Intermediate values are OSR_512,
  OSR_1024, OSR_2048, OSR_4096.

### Returns

Either the pressure value as a floating point number (mbar), or -1111 if an error occurred.

## getTempAndPressure()

This function allows you to read both temperature and pressure in one
pass. This saves some overhead because a call to `getPressure()` has
to read the temperature as well, but this value is not usually
returned.

Execution time is roughly the same as the `getPressure` function.

The temperature and pressure variables are passed in as pointers to
the function. The result of the function is a boolean value, true for
success.

### Function Signature

     bool getTempAndPressure(float *temperature,
                             float *pressure,
                             TempUnit tempScale = CELSIUS,
                             BaroOversampleLevel level = OSR_8192);

### Basic Usage

    float temp;
    float pressure;
    if(!BaroSensor.getTempAndPressure(&temp, &pressure) {
      Serial.print("Error: ");
      Serial.println(BaroSensor.getError());
    } else {
      Serial.print("Temp: ");
      Serial.println(temp);
      Serial.print("Pressure: ");
      Serial.println(pressure);
    }
    

## isOK() / getError()

### Function Signatures:

    bool isOK();
    byte getError();

### Basic Usage:

    if(!BaroSensor.isOK()) {
      Serial.print("Sensor error occurred. Error number: "); 
      Serial.println(BaroSensor.getError());
      BaroSensor.begin(); // Try to reinitialise the sensor if we can
    }

### Returns

`isOK()` returns true if the sensor is working properly (after
`begin()` has been called.) In this working state, `getError()` will
return zero.

`getError()` can otherwise return any of these error values:

* 0 = No error, sensor working fine.
* 2 = Received NACK on transmit of address (sensor may not be connected/powered properly.)
* 3 = Received NACK on transmit of data (sensor connections may not be good enough quality.)
* 4 = Other "Wire" library i2c error.
* -3 = `begin()` hasn't been called yet.
* -2 = Failed to read back values from sensor (sensor connections may not be good enough quality.)
