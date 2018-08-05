/*!
 * @file VL53L0X_I2C.h
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

/*-- I2C Setting --*/
/*
 *  I2C0 Conncection | I2C1 Conncection | I2C2 Conncection | I2C3 Conncection
 *  ---------------- | ---------------- | ---------------- | ----------------
 *  SCL -------- PB2 | SCL -------- PA6 | SCL -------- PE4 | SCL -------- PD0
 *  SDA -------- PB3 | SDA -------- PA7 | SDA -------- PE5 | SDA -------- PD1
 */
#if 1           // set this to 1 to use I2C0
#define I2C0
#endif

#if 0           // set this to 1 to use I2C1
#define I2C1
#endif

#if 0           // set this to 1 to use I2C2
#define I2C2
#endif

#if 0           // set this to 1 to use I2C3
#define I2C3
#endif

/**
 * VL53L0X_I2C_Init
 * ----------
 * @brief initialize a I2C module with corresponding setting parameters.
 */
void VL53L0X_I2C_Init(void);



