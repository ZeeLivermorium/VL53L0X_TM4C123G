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

/*
 *  I2C0 Conncection | I2C1 Conncection | I2C2 Conncection | I2C3 Conncection
 *  ---------------- | ---------------- | ---------------- | ----------------
 *  SCL -------- PB2 | SCL -------- PA6 | SCL -------- PE4 | SCL -------- PD0
 *  SDA -------- PB3 | SDA -------- PA7 | SDA -------- PE5 | SDA -------- PD1
 */
#if 1           // set this to 1 to use I2C0
    #define I2C0
#elif 0         // set this to 1 to use I2C1
    #define I2C1
#elif 0         // set this to 1 to use I2C2
    #define I2C2
#else           // I2C3 if all 0 above
    #define I2C3
#endif

/**
 * VL53L0X_I2C_Init
 * ----------
 * @brief initialize a I2C module with corresponding setting parameters.
 */
void VL53L0X_I2C_Init(void);

int VL53L0X_write_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata, uint32_t count);
int VL53L0X_read_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata, uint32_t count);
int VL53L0X_write_byte(uint8_t deviceAddress, uint8_t index, uint8_t data);
int VL53L0X_write_word(uint8_t deviceAddress, uint8_t index, uint16_t data);
int VL53L0X_write_dword(uint8_t deviceAddress, uint8_t index, uint32_t data);
int VL53L0X_read_byte(uint8_t deviceAddress, uint8_t index, uint8_t *data);
int VL53L0X_read_word(uint8_t deviceAddress, uint8_t index, uint16_t *data);
int VL53L0X_read_dword(uint8_t deviceAddress, uint8_t index, uint32_t *data);
