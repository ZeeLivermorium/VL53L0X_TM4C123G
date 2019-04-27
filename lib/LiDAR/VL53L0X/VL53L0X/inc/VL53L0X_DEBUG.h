
#ifndef __VL53L0X_DEBUG_H__
#define __VL53L0X_DEBUG_H__

#define VL53L0X_DEBUG

#ifdef VL53L0X_DEBUG
#include "Serial.h"
#include "vl53l0x_api.h"

static void print_pal_error(VL53L0X_Error Status) {
    char buffer[VL53L0X_MAX_STRING_LENGTH];
    VL53L0X_GetPalErrorString(Status, buffer);
    Serial_println("-- API Status: %d : %s\n", Status, buffer);
}

#define VL53L0X_DEBUG_INIT()         Serial_Init()
#define VL53L0X_DEBUG_MSG(args...)   Serial_println(args)
#define VL53L0X_DEBUG_STATUS(status) print_pal_error(status)

#else

#define VL53L0X_DEBUG_INIT()
#define VL53L0X_DEBUG_MSG(args...)
#define VL53L0X_DEBUG_STATUS(status)

#endif

#endif
