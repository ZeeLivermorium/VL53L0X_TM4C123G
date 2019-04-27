# VL53L0X ToF Ranging Sensor Library for TM4C123G

## Introduction
Driver Library for **STMicroelectronics VL53L0X Time-of-Flight Ranging Sensor** on **TI TM4C123G MCU**. Example Projects using this dirver is available in [project](proj) folder. Keil uVision project files are included, which means you can just simply double click on them to open the example files and load to your TM4C123, if using Keil. Otherwise, you have to manage all source files by yourself. Source code used and provided by STMicroelectronics is in [core](lib/core) and [platform](lib/platform) folders. Other files used in this repository are also in [lib](lib) folder.

## Documents
#### [TI TM4C123GXL Data Sheet](http://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf)
#### [ST VL53L0X Data Sheet](https://www.st.com/resource/en/datasheet/vl53l0x.pdf)

## Protocols
VL53L0X only runs on I2C protocol. To use different I2C ports, adjust the preprocessor setting in [I2C.h](lib/common/inc/I2C.h#L17).

## Multiple VL53L0Xs
To use multiple VL53L0Xs at the same time using the same I2C bus, we need to first change the device I2C address. To avoid the address conflict during the address modification, the XSHUT pin is used. Pulling XSHUT down pin low puts VL53L0X into shutdown mode. By keeping only one sensor awake at a time, you can modify the device address for the awake VL53L0X, using the [*VL53L0X_setAddress*](lib/LiDAR/VL53L0X/VL53L0X/inc/VL53L0X.h#L64) API. To wire multiple devices, you can use a few GPIO vins from TM4C123, a shift register with separated input and output clock like the 74HC595 or a decoder IC, if saving pins is needed for your project. Of course, you should try any other circuit configuration, if you think it's needed. 

You can view my current set up for multiple sensor in [xshut.c](lib/LiDAR/VL53L0X/VL53L0X/src/xshut.c). A few GPIO pins on Port E are used to control the xshut pins on multiple sensors.

## Projects
### Single Ranging Default Mode
[VL53L0X_SingleRanging_1](proj/VL53L0X_SingleRanging_1)
> Interfacing 1 sensor and output the result to serial output.

[VL53L0X_SingleRanging_1_ST7735](proj/VL53L0X_SingleRanging_1_ST7735)
> Interfacing 1 sensor and output the result to a ST7735 display.

[VL53L0X_SingleRanging_2](proj/VL53L0X_SingleRanging_2)
> Interfacing 2 sensor and output the result to serial output.

[VL53L0X_SingleRanging_2_ST7735](proj/VL53L0X_SingleRanging_2_ST7735)
> Interfacing 2 sensor and output the result to a ST7735 display.

[VL53L0X_SingleRanging_3](proj/VL53L0X_SingleRanging_3)
> Interfacing 3 sensor and output the result to serial output.

[VL53L0X_SingleRanging_3_ST7735](proj/VL53L0X_SingleRanging_3_ST7735)
> Interfacing 3 sensor and output the result to a ST7735 display.

[VL53L0X_SingleRanging_4](proj/VL53L0X_SingleRanging_4)
> Interfacing 4 sensor and output the result to serial output.

[VL53L0X_SingleRanging_4_ST7735](proj/VL53L0X_SingleRanging_4_ST7735)
> Interfacing 4 sensor and output the result to a ST7735 display.

### Continuous Ranging Mode
> In Dev

## Problems and Bugs
If you find any bug or problem, please create new issue or a pull request with a fix in the repository.
Or you can simply email me about the problem or bug at zeelivermorium@gmail.com .
Much Appreciated!

## Copyright Note
This repository adpated and modified some source code from [Adafruit's VL53L0X Arduino driver](https://github.com/adafruit/Adafruit_VL53L0X) to make it run on TI TM4C123G MCU.
