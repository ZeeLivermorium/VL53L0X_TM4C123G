/*!
 * @file  VL53L0X_Distance_Measure_ST7735.c
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
#include "PLL.h"
#include "ST7735.h"
#include "VL53L0X.h"

int main(void) {
    /*-- TM4C123 Init --*/
    PLL_Init(Bus80MHz);                             // bus clock at 80 MHz
    
    /*-- ST7735 Init --*/
    ST7735_InitR(INITR_REDTAB);
    
    ST7735_SetCursor(0, 0);
    ST7735_FillScreen(ST7735_BLACK);
    
    ST7735_OutString("@author: Zee Lv");
    ST7735_OutChar('\n');
    ST7735_OutString("--------------------");
    ST7735_OutChar('\n');
    
    /*-- VL53L0X Init --*/
    if(!VL53L0X_Init(VL53L0X_I2C_ADDR)) {
        ST7735_OutString("Fail to initialize VL53L0X :(");
        delay(1);
        return 0;
    } else {
        ST7735_OutString("VL53L0X Ready~ ");
        ST7735_OutChar('\n');
    }
    
    VL53L0X_RangingMeasurementData_t measurement;
    
    /*-- loop --*/
    while(1) {
        VL53L0X_getSingleRangingMeasurement(&measurement);
        if (measurement.RangeStatus != 4) {
            ST7735_OutString("Distance: ");
            ST7735_OutUDec(measurement.RangeMilliMeter);
            ST7735_OutString(" mm");
            ST7735_OutChar('\n');
        } else {
            ST7735_OutString("Out of range :( ");
            ST7735_OutChar('\n');
        }
        delay(1000);                                // take a break
        ST7735_SetCursor(0, 3);
    }
}
