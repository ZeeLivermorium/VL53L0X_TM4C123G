/*!
 * @file  VL53L0X_Distance_Measure_1.c
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
 * @date   Aug 5, 2018
 */

#include <stdint.h>
#include "../../inc/PLL.h"
#include "../../inc/Serial.h"
#include "../../VL53L0X/VL53L0X.h"

int main(void) {
    /*-- TM4C123 Init --*/
    PLL_Init(Bus80MHz);                   // bus clock at 80 MHz
    VL53L0X_Init();                       // init and wake up VL53L0X
    Serial_Init();                        // for serial I/O

    /*-- loop --*/
    while(1) {                            // read and process

    }
}
