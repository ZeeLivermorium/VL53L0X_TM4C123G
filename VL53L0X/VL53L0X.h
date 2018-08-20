/*!
 * @file  VL53L0X.h
 * @brief VL53L0X driver APIs.
 * ----------
 * Adapted code from Adafruit VL53L0X driver for Arduino.
 * You can find the Adafruit VL53L0X driver here: https://github.com/adafruit/Adafruit_VL53L0X
 * ----------
 * ST VL53L0X datasheet: https://www.st.com/resource/en/datasheet/vl53l0x.pdf
 * ----------
 * For future development and updates, please follow this repository: https://github.com/ZeeLivermorium/VL53L0X_TM4C123
 * ----------
 * If you find any bug or problem, please create new issue or a pull request with a fix in the repository.
 * Or you can simply email me about the problem or bug at zeelivermorium@gmail.com
 * Much Appreciated!
 * ----------
 * @author Zee Livermorium
 * @date   Aug 4, 2018
 */


#ifndef __VL53L0X_H__
#define __VL53L0X_H__

#include "vl53l0x_api.h"

#define FAIL              0
#define SUCCESS           1
#define DISABLE           0
#define ENABLE            1
#define VL53L0X_I2C_ADDR  0x29          // Default sensor I2C address

/*
 *  I2C0 Conncection | I2C1 Conncection | I2C2 Conncection | I2C3 Conncection
 *  ---------------- | ---------------- | ---------------- | ----------------
 *  SCL -------- PB2 | SCL -------- PA6 | SCL -------- PE4 | SCL -------- PD0
 *  SDA -------- PB3 | SDA -------- PA7 | SDA -------- PE5 | SDA -------- PD1
 */

typedef int VL53L0X_I2C_Port;

int VL53L0X_Init(uint8_t I2C_address);

int VL53L0X_setAddress(uint8_t newAddress);

VL53L0X_Error VL53L0X_getSingleRangingMeasurement (VL53L0X_RangingMeasurementData_t *RangingMeasurementData);

/****************************************************
 *                                                  *
 *                 Helper Functions                 *
 *                                                  *
 ****************************************************/

/**
 * delay
 * ----------
 * Description: delay N time unit
 */
static void delay(uint32_t N) {
    for(int n = 0; n < N; n++)                         // N time unitss
        for(int msec = 10000; msec > 0; msec--);       // 1 time unit
}

#endif
