/*!
 * @file VL53L0X.h
 * @brief
 * ----------
 * Adapted code from Adafruit VL53L0X driver for Arduino.
 * You can find the Adafruit VL53L0X driver here:
 * ----------
 *
 * ----------
 * For future development and updates, please follow this repository:
 * ----------
 * If you find any bug or problem, please create new issue or a pull request with a fix in the repository.
 * Or you can simply email me about the problem or bug at zeelivermorium@gmail.com
 * Much Appreciated!
 * ----------
 * @author Zee Livermorium
 * @date Aug 4, 2018
 */


#ifndef __VL53L0X_H__
#define __VL53L0X_H__

#include "vl53l0x_api.h"

#define FAIL              0
#define SUCCESS           1
#define VL53L0X_I2C_ADDR  0x29    // Default sensor I2C address


int VL53L0X_Init ();

int VL53L0X_setAddress(uint8_t newAddress);

VL53L0X_Error getSingleRangingMeasurement (VL53L0X_RangingMeasurementData_t *RangingMeasurementData);

#endif
