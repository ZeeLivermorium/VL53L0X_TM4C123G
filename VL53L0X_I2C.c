/*!
 * @file VL53L0X_I2C.c
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

#include <stdint.h>
#include "VL53L0X_I2C.h"
#include "../inc/tm4c123gh6pm.h"

/**
 * VL53L0X_I2C_Init
 * ----------
 * @brief initialize a I2C module with corresponding setting parameters.
 */
void VL53L0X_I2C_Init(void) {
#ifdef I2C0
    /*-- I2C0 and Port B Activation --*/
    SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R0;                 // enable I2C Module 0 clock
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;               // enable GPIO Port B clock
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1) == 0) {};  // allow time for activating
    
    /*-- Port B Set Up --*/
    GPIO_PORTB_AFSEL_R |= 0x0C;                            // enable alt function on PB2, 3
    GPIO_PORTB_ODR_R |= 0x08;                              // enable open drain on PB3
    GPIO_PORTB_DEN_R |= 0x0C;                              // enable digital I/O on PB2,3
    GPIO_PORTB_PCTL_R &= ((~GPIO_PCTL_PB2_M) &             // clear bit fields for PB2
                          (~GPIO_PCTL_PB3_M));             // clear bit fields for PB3
    GPIO_PORTB_PCTL_R |= (GPIO_PCTL_PB2_I2C0SCL |          // configure PB2 as I2C0SCL
                          GPIO_PCTL_PB3_I2C0SDA);          // configure PB3 as I2C0SDA
    GPIO_PORTB_AMSEL_R &= ~0x0C;                           // disable analog functionality on PB2, 3
    
    /*-- I2C0 Set Up --*/
    I2C0_MCR_R = I2C_MCR_MFE;                              // master function enable
    I2C0_MTPR_R = 24;                                      // configure for 100 kbps clock
    // 20 * (TPR + 1) * 20ns = 10us, with TPR=24
#endif
#ifdef I2C1
    /*-- I2C1 and Port A Activation --*/
    SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R1;                 // enable I2C Module 1 clock
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;               // enable GPIO Port A clock
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0) == 0) {};  // allow time for activating
    
    /*-- Port A Set Up --*/
    GPIO_PORTA_AFSEL_R |= 0xC0;                            // enable alt function on PA6, 7
    GPIO_PORTA_ODR_R |= 0x80;                              // enable open drain on PA7
    GPIO_PORTA_DEN_R |= 0xC0;                              // enable digital I/O on PA6, 7
    GPIO_PORTA_PCTL_R &= ((~GPIO_PCTL_PA6_M) &             // clear bit fields for PA6
                          (~GPIO_PCTL_PA7_M));             // clear bit fields for PA7
    GPIO_PORTA_PCTL_R |= (GPIO_PCTL_PA6_I2C1SCL |          // configure PA6 as I2C1SCL
                          GPIO_PCTL_PA7_I2C1SDA);          // configure PA7 as I2C1SDA
    GPIO_PORTA_AMSEL_R &= ~0xC0;                           // disable analog functionality on PA6, 7
    
    /*-- I2C1 Set Up --*/
    I2C1_MCR_R = I2C_MCR_MFE;                              // master function enable
    I2C1_MTPR_R = 24;                                      // configure for 100 kbps clock
    // 20 * (TPR + 1) * 20ns = 10us, with TPR=24
#endif
#ifdef I2C2
    /*-- I2C2 and Port E Activation --*/
    SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R2;                 // enable I2C Module 2 clock
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;               // enable GPIO Port E clock
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R4) == 0) {};  // allow time for activating
    
    /*-- Port E Set Up --*/
    GPIO_PORTE_AFSEL_R |= 0x30;                            // enable alt function on PE4, 5
    GPIO_PORTE_ODR_R |= 0x20;                              // enable open drain on PE5
    GPIO_PORTE_DEN_R |= 0x30;                              // enable digital I/O on PE4, 5
    GPIO_PORTE_PCTL_R &= ((~GPIO_PCTL_PE4_M) &             // clear bit fields for PE4
                          (~GPIO_PCTL_PE5_M));             // clear bit fields for PE5
    GPIO_PORTE_PCTL_R |= (GPIO_PCTL_PE4_I2C2SCL |          // configure PE4 as I2C2SCL
                          GPIO_PCTL_PE5_I2C2SDA);          // configure PE5 as I2C2SDA
    GPIO_PORTE_AMSEL_R &= ~0x30;                           // disable analog functionality on PE4, 5
    
    /*-- I2C2 Set Up --*/
    I2C2_MCR_R = I2C_MCR_MFE;                              // master function enable
    I2C2_MTPR_R = 24;                                      // configure for 100 kbps clock
    // 20 * (TPR + 1) * 20ns = 10us, with TPR=24
#endif
#ifdef I2C3
    /*-- I2C3 and Port D Activation --*/
    SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R3;                 // enable I2C Module 3 clock
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;               // enable GPIO Port D clock
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R3) == 0) {};  // allow time for activating
    
    /*-- Port D Set Up --*/
    GPIO_PORTD_AFSEL_R |= 0x03;                            // enable alt function on PD0, 1
    GPIO_PORTD_ODR_R |= 0x02;                              // enable open drain on PD1
    GPIO_PORTD_DEN_R |= 0x03;                              // enable digital I/O on PD0, 1
    GPIO_PORTD_PCTL_R &= ((~GPIO_PCTL_PD0_M) &             // clear bit fields for PD0
                          (~GPIO_PCTL_PD1_M));             // clear bit fields for PD1
    GPIO_PORTD_PCTL_R |= (GPIO_PCTL_PD0_I2C3SCL |          // configure PD0 as I2C3SCL
                          GPIO_PCTL_PD1_I2C3SDA);          // configure PD1 as I2C3SDA
    GPIO_PORTD_AMSEL_R &= ~0x03;                           // disable analog functionality on PD0, 1
    
    /*-- I2C3 Set Up --*/
    I2C3_MCR_R = I2C_MCR_MFE;                              // master function enable
    I2C3_MTPR_R = 24 ;                                     // configure for 100 kbps clock
    // 20 * (TPR + 1) * 20ns = 10us, with TPR=24
#endif
}

int readByte() {
    int retryCounter = 1;
    do{
        while(I2C0_MCS_R&I2C_MCS_BUSY){};                  // wait for I2C0 to be ready
        I2C0_MSA_R = (slave<<1)&0xFE;    // MSA[7:1] is slave address
        I2C0_MSA_R |= 0x01;              // MSA[0] is 1 for receive
        I2C0_MCS_R = (0
                      // & ~I2C_MCS_ACK     // negative data ack (last byte)
                      | I2C_MCS_STOP     // generate stop
                      | I2C_MCS_START    // generate start/restart
                      | I2C_MCS_RUN);    // master enable
        while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
        retryCounter = retryCounter + 1;        // increment retry counter
    }                                         // repeat if error
    while(((I2C0_MCS_R&(I2C_MCS_ADRACK|I2C_MCS_ERROR)) != 0) && (retryCounter <= MAXRETRIES));
    return (I2C0_MDR_R&0xFF);          // usually returns 0xFF on error
}

int readWord() {
    
}

int readLongWord(){
    
}

int writeByte() {
    
}

int writeWord() {
    
}

int writeLongWord() {
    
}

