/*!
 * @file  VL53L0X.c
 * @brief VL53L0X driver APIs and their implementation.
 * ----------
 * ST VL53L0X datasheet: https://www.st.com/resource/en/datasheet/vl53l0x.pdf
 * ----------
 * For future development and updates, please follow this repository: https://github.com/ZeeLivermorium/VL53L0X_TM4C123G
 * ----------
 * If you find any bug or problem, please create new issue or a pull request with a fix in the repository.
 * Or you can simply email me about the problem or bug at zeelivermorium@gmail.com
 * Much Appreciated!
 * ----------
 * @author Zee Livermorium
 * @date   Aug 4, 2018
 */

#include "VL53L0X.h"
#include "VL53L0X_I2C.h"
#include "VL53L0X_DEBUG.h"

VL53L0X deviceList[10];

/**
 * VL53L0X_Init
 * ----------
 * @param  index  Index to the specified sensor.
 * ----------
 * @return 0 for failed initialization, 1 for successful initialization.
 * ----------
 * @brief  Initialize VL53L0X.
 */
int VL53L0X_Init (int index) {
    
    VL53L0X_I2C_Init();                                         // must initialize I2C before initialize VL53L0X
    
    VL53L0X_Dev_t*        device = &deviceList[index].device;
    VL53L0X_DeviceInfo_t* deviceInfo = &deviceList[index].deviceInfo;
    VL53L0X_Error         status = VL53L0X_ERROR_NONE;
    VL53L0X_Version_t     version;
    
    // set device address to default
    device->I2cDevAddr = VL53L0X_I2C_ADDR;     // default
    
    // make sure the driver lib is the right version
    status = VL53L0X_GetVersion(&version);
    
    if( status == VL53L0X_ERROR_NONE )  {
        // unclear if this is even needed:
        if( (version.major != VERSION_REQUIRED_MAJOR ||
             version.minor != VERSION_REQUIRED_MINOR ||
             version.build != VERSION_REQUIRED_BUILD) )
        {
            status = VL53L0X_ERROR_CONTROL_INTERFACE;
            
            
            VL53L0X_DEBUG_MSG("VL53L0X API Version Error: Your firmware has %d.%d.%d (revision %d). This example requires %d.%d.%d.",
                      version.major, version.minor, version.build, version.revision,
                      VERSION_REQUIRED_MAJOR, VERSION_REQUIRED_MINOR, VERSION_REQUIRED_BUILD
                      );
            
            
            return FAIL;
        }
    } else {
        
    }
    
    if( status == VL53L0X_ERROR_NONE )  {
        
        VL53L0X_DEBUG_MSG("- VL53L0X_DataInit -");
        
        // data initialization
        status = VL53L0X_DataInit(&deviceList[index].device);
    }
    
    VL53L0X_DEBUG_STATUS(status);
    
    if( status == VL53L0X_ERROR_NONE )  {
        // reads the device information for given device
        status = VL53L0X_GetDeviceInfo( device, deviceInfo );
    }
    
    if( status == VL53L0X_ERROR_NONE )  {
        VL53L0X_DEBUG_MSG("- VL53L0X_GetDeviceInfo -");
        VL53L0X_DEBUG_MSG("Device Name : %s", deviceInfo->Name);
        VL53L0X_DEBUG_MSG("Device Type : %s", deviceInfo->Type);
        VL53L0X_DEBUG_MSG("Device ID : %s", deviceInfo->ProductId);
        VL53L0X_DEBUG_MSG("ProductRevisionMajor : %d", deviceInfo->ProductRevisionMajor);
        VL53L0X_DEBUG_MSG("ProductRevisionMinor : %d", deviceInfo->ProductRevisionMinor);
        
        if(( deviceList[index].deviceInfo.ProductRevisionMinor != 1 ) && ( deviceList[index].deviceInfo.ProductRevisionMinor != 1 )) {
            
            VL53L0X_DEBUG_MSG("Error expected cut 1.1 but found cut %d.%d",
                      deviceInfo->ProductRevisionMajor,
                      deviceInfo->ProductRevisionMinor
                      );
            
            status = VL53L0X_ERROR_NOT_SUPPORTED;
        }
        
    }
    
    VL53L0X_DEBUG_STATUS(status);
    
    // return initialization status
    return (status == VL53L0X_ERROR_NONE) ? SUCCESS : FAIL;
    
}

/**
 * VL53L0X_SingleRanging_Init
 * ----------
 * @param  index  Index to the specified sensor.
 * ----------
 * @return 0 for failed initialization, 1 for successful initialization.
 * ----------
 * @brief  Initialize VL53L0X for single ranging mode.
 */
int VL53L0X_SingleRanging_Init (int index) {
    
    // variable needed for some function calls
    VL53L0X_Error status = VL53L0X_ERROR_NONE;
    uint32_t  refSpadCount;
    uint8_t   isApertureSpads;
    uint8_t   VhvSettings;
    uint8_t   PhaseCal;
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_DEBUG_MSG("- VL53L0X_StaticInit -");
        // device initialization
        status = VL53L0X_StaticInit( &deviceList[index].device );
        VL53L0X_DEBUG_STATUS(status);
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_DEBUG_MSG("- VL53L0X_PerformRefSpadManagement -");
        // performs reference spad Management
        status = VL53L0X_PerformRefSpadManagement( &deviceList[index].device, &refSpadCount, &isApertureSpads );
        VL53L0X_DEBUG_STATUS(status);
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_DEBUG_MSG("- VL53L0X_PerformRefCalibration -");
        // perform reference calibration
        status = VL53L0X_PerformRefCalibration( &deviceList[index].device, &VhvSettings, &PhaseCal );
        VL53L0X_DEBUG_STATUS(status);
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_DEBUG_MSG("- VL53L0X_SetDeviceMode -");
        VL53L0X_DEBUG_MSG("Single Ranging Mode");
        // setup in single ranging mode
        status = VL53L0X_SetDeviceMode( &deviceList[index].device, VL53L0X_DEVICEMODE_SINGLE_RANGING );
        VL53L0X_DEBUG_STATUS(status);
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_DEBUG_MSG("- VL53L0X_SetLimitCheckEnable -");
        VL53L0X_DEBUG_MSG("Enable sigma check");
        // enable sigma check
        status = VL53L0X_SetLimitCheckEnable( &deviceList[index].device, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1 );
        VL53L0X_DEBUG_STATUS(status);
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_DEBUG_MSG("- VL53L0X_SetLimitCheckEnable -");
        VL53L0X_DEBUG_MSG("Enable signal check");
        // enable signal check
        status = VL53L0X_SetLimitCheckEnable( &deviceList[index].device, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1 );
        VL53L0X_DEBUG_STATUS(status);
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_DEBUG_MSG("- VL53L0X_SetLimitCheckEnable -");
        VL53L0X_DEBUG_MSG("Enable range check");
        // enable range check
        status = VL53L0X_SetLimitCheckEnable( &deviceList[index].device, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1 );
        VL53L0X_DEBUG_STATUS(status);
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_DEBUG_MSG("- VL53L0X_SetLimitCheckValue -");
        // set limit check value
        status = VL53L0X_SetLimitCheckValue(
                                            &deviceList[index].device,
                                            VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD,
                                            (FixPoint1616_t)( 1.5 * 0.023 * 65536 )
                                            );
        VL53L0X_DEBUG_STATUS(status);
    }
    
    // return initialization status
    return (status == VL53L0X_ERROR_NONE) ? SUCCESS : FAIL;
}

/**
 * VL53L0X_ContinuousRanging_Init
 * ----------
 * @param  index  Index to the specified sensor.
 * ----------
 * @return 0 for failed initialization, 1 for successful initialization.
 * ----------
 * @brief  Initialize VL53L0X for continuous ranging mode.
 */
int VL53L0X_ContinuousRanging_Init (int index) {
    // variable needed for some function calls
    VL53L0X_Error status = VL53L0X_ERROR_NONE;
    uint32_t  refSpadCount;
    uint8_t   isApertureSpads;
    uint8_t   VhvSettings;
    uint8_t   PhaseCal;
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_DEBUG_MSG("- VL53L0X_StaticInit -");
        // device initialization
        status = VL53L0X_StaticInit( &deviceList[index].device );
        VL53L0X_DEBUG_STATUS(status);
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_DEBUG_MSG("- VL53L0X_PerformRefSpadManagement -");
        // performs reference spad Management
        status = VL53L0X_PerformRefSpadManagement( &deviceList[index].device, &refSpadCount, &isApertureSpads );
        VL53L0X_DEBUG_STATUS(status);
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_DEBUG_MSG("- VL53L0X_PerformRefCalibration -");
        // perform reference calibration
        status = VL53L0X_PerformRefCalibration( &deviceList[index].device, &VhvSettings, &PhaseCal );
        VL53L0X_DEBUG_STATUS(status);
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        VL53L0X_DEBUG_MSG("- VL53L0X_SetDeviceMode -");
        VL53L0X_DEBUG_MSG("Continuous Ranging Mode");
        // setup in single ranging mode
        status = VL53L0X_SetDeviceMode( &deviceList[index].device, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING );
        VL53L0X_DEBUG_STATUS(status);
    }
    
    // return initialization status
    return (status == VL53L0X_ERROR_NONE) ? SUCCESS : FAIL;
}

/**
 * VL53L0X_setAddress
 * ----------
 * @param  newAddress  the new address to set the VL53L0X to.
 * ----------
 * @return 0 for failed initialization, 1 for successful initialization.
 * ----------
 * @brief  Change the I2C address of VL53L0X.
 */
int VL53L0X_setAddress(uint8_t newAddress, int index) {
    
    VL53L0X_Error status = VL53L0X_ERROR_NONE;
    // trim the new address
    newAddress &= 0x7F;
    
    status = VL53L0X_SetDeviceAddress(&deviceList[index].device, newAddress * 2);  // [7:2] is address
    
    delay(10);
    
    if( status == VL53L0X_ERROR_NONE ) {
        deviceList[index].device.I2cDevAddr = newAddress;  // 7 bit addr
        return SUCCESS;
    }
    
    return FAIL;
}

/**
 * VL53L0X_getSingleRangingMeasurement
 * ----------
 * @param  RangingMeasurementData  pointer for where to store the ranging data.
 * ----------
 * @return any error code.
 * ----------
 * @brief  Get a ranging measurement from VL53L0X.
 */
VL53L0X_Error VL53L0X_getSingleRangingMeasurement (VL53L0X_RangingMeasurementData_t* RangingMeasurementData, int index) {
    return VL53L0X_PerformSingleRangingMeasurement( &deviceList[index].device, RangingMeasurementData );
}

