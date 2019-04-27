/*!
 * @file  xshut.c
 * @brief Implementation for interfacing xshut pins for VL53L0X for multi sensor projects.
 * ----------
 * ST VL53L0X datasheet: https://www.st.com/resource/en/datasheet/vl53l0x.pdf
 * ----------
 * For future development and updates, please follow this repository: https://github.com/ZeeLivermorium/VL53L0X_TM4C123G
 * ----------
 * If you find any bug or problem, please create new issue or a pull request with a fix in the repository.
 * Or you can simply email me about the problem or bug at zeelivermorium@gmail.com
 * Much Appreciated!
 * @author Zee Livermorium and Tariq Muhanna
 * @date   Sep 19, 2018
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "VL53L0X.h"

uint8_t mask = 0x01;

void xshut_Init(void) {
    /* Port E Activation */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;               // enable GPIO Port E clock
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R4) == 0){};    // allow time for activating
    
    /* Port E Set Up */
    GPIO_PORTE_CR_R = 0x0F;                                // allow changes to PE0-3
    GPIO_PORTE_DIR_R = 0x0F;                               // make PE0-3 output
    GPIO_PORTE_AMSEL_R &= ~0x0F;                           // disable analog on PE0-3
    GPIO_PORTE_PCTL_R &= ((~GPIO_PCTL_PE0_M) &             // configure PE0 as GPIO
                          (~GPIO_PCTL_PE1_M) &             // configure PE1 as GPIO
                          (~GPIO_PCTL_PE2_M) &             // configure PE2 as GPIO
                          (~GPIO_PCTL_PE3_M));             // configure PE3 as GPIO
    GPIO_PORTE_AFSEL_R  &= ~0x0F;                          // disable alt functtion on PE0-3
    GPIO_PORTE_DEN_R = 0x0F;                               // enable digital I/O on PE0-3
    
    GPIO_PORTE_DATA_R = 0x00 ;                             // put all sensors low
    delay(50);
    GPIO_PORTE_DATA_R = 0xFF ;                             // put all sensors high
    delay(50);
    GPIO_PORTE_DATA_R = mask;
}

void xshut_Switch(void) {
    mask <<= 1;			                                       // must activate devices 1 by 1
    mask += 0x01;		                                       // must not reset any of the previous devices
    GPIO_PORTE_DATA_R = mask;
    delay(50);
}


