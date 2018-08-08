/*!
 * @file VL53L0X.c
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

#include "VL53L0X.h"
#include "VL53L0X_I2C.h"
#include "LED.h"

#define VERSION_REQUIRED_MAJOR  1 ///< Required sensor major version
#define VERSION_REQUIRED_MINOR  0 ///< Required sensor minor version
#define VERSION_REQUIRED_BUILD  1 ///< Required sensor build

#define STR_HELPER( x ) #x ///< a string helper
#define STR( x )        STR_HELPER(x) ///< string helper wrapper

VL53L0X_Error status = VL53L0X_ERROR_NONE; // indicates whether or not the sensor has encountered an error
VL53L0X_Dev_t VL53L0X_device;
VL53L0X_DeviceInfo_t DeviceInfo;

/**************************************************************************/
/*!
 @brief  Setups the I2C interface and hardware
 @param  i2c_addr Optional I2C address the sensor can be found on. Default is 0x29
 @param debug Optional debug flag. If true, debug information will print out via Serial.print during setup. Defaults to false.
 @returns True if device is set up, false on any failure
 */
/**************************************************************************/
int VL53L0X_Init (uint8_t I2C_address) {

    
    // Initialize Comms
    VL53L0X_device.I2cDevAddr = VL53L0X_I2C_ADDR;  // default
    VL53L0X_device.comms_type      =  1;
    VL53L0X_device.comms_speed_khz =  400;
    
    // variable needed for some function calls
    uint32_t  refSpadCount;
    uint8_t   isApertureSpads;
    uint8_t   VhvSettings;
    uint8_t   PhaseCal;
        // initialize I2C on MCU 
    VL53L0X_I2C_Init();
    // unclear if this is even needed:
    if( VL53L0X_IMPLEMENTATION_VER_MAJOR != VERSION_REQUIRED_MAJOR ||
        VL53L0X_IMPLEMENTATION_VER_MINOR != VERSION_REQUIRED_MINOR ||
        VL53L0X_IMPLEMENTATION_VER_SUB != VERSION_REQUIRED_BUILD ) {

        status = VL53L0X_ERROR_NOT_SUPPORTED;
        return FAIL;
    }
	
    
    // Data initialization
    status = VL53L0X_DataInit(&VL53L0X_device);
    
    if (!VL53L0X_setAddress(I2C_address)) {
        return FAIL;
    }
    
    //
    status = VL53L0X_GetDeviceInfo( &VL53L0X_device, &DeviceInfo );
    
    if( status == VL53L0X_ERROR_NONE )  {
        if(( DeviceInfo.ProductRevisionMinor != 1 ) && ( DeviceInfo.ProductRevisionMinor != 1 )) {
            status = VL53L0X_ERROR_NOT_SUPPORTED;
        }
    }
   
    if( status == VL53L0X_ERROR_NONE ) {
        //
        status = VL53L0X_StaticInit( &VL53L0X_device );
    }
    if (status) LED_RED_ON();
    if( status == VL53L0X_ERROR_NONE ) {
        //
        status = VL53L0X_PerformRefSpadManagement( &VL53L0X_device, &refSpadCount, &isApertureSpads );
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        //
        status = VL53L0X_PerformRefCalibration( &VL53L0X_device, &VhvSettings, &PhaseCal );
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        // Setup in single ranging mode
        status = VL53L0X_SetDeviceMode( &VL53L0X_device, VL53L0X_DEVICEMODE_SINGLE_RANGING );
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        // Enable/disable sigma check
        status = VL53L0X_SetLimitCheckEnable( &VL53L0X_device, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1 );
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        // Enable/disable signal check
        status = VL53L0X_SetLimitCheckEnable( &VL53L0X_device, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1 );
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        //
        status = VL53L0X_SetLimitCheckEnable( &VL53L0X_device, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1 );
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        //
        status = VL53L0X_SetLimitCheckValue( &VL53L0X_device, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, (FixPoint1616_t)( 1.5 * 0.023 * 65536 ) );
    }
    
    // return initialization status
    return (status == VL53L0X_ERROR_NONE) ? SUCCESS : FAIL;
}

/**************************************************************************/
/*!
 @brief  Change the I2C address of the sensor
 @param  newAddr the new address to set the sensor to
 @returns True if address was set successfully, False otherwise
 */
/**************************************************************************/
int VL53L0X_setAddress(uint8_t newAddress) {
    // trim the new address
    newAddress &= 0x7F;
    
    status = VL53L0X_SetDeviceAddress(&VL53L0X_device, newAddress * 2);  // [8:2] is address
    
    delay(10);
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_device.I2cDevAddr = newAddress;  // 7 bit addr
        return SUCCESS;
    }
    
    return FAIL;
}

/**************************************************************************/
/*!
 @brief  get a ranging measurement from the device
 @param  RangingMeasurementData the pointer to the struct the data will be stored in
 @param debug Optional debug flag. If true debug information will print via Serial.print during execution. Defaults to false.
 @returns True if address was set successfully, False otherwise
 */
/**************************************************************************/
VL53L0X_Error VL53L0X_getSingleRangingMeasurement (VL53L0X_RangingMeasurementData_t *RangingMeasurementData) {
        return VL53L0X_PerformSingleRangingMeasurement( &VL53L0X_device, RangingMeasurementData );
}

