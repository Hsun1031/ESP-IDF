#ifndef __DHT11_H__
#define __DHT11_H__

#define SHOW_DHT11_H_DEBUG

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_timer.h"
#include "esp_log.h"

#include "driver/gpio.h"

#include "pin.h"

#define DHT11_MIN_INTERVAL_TIME_S                                                2
#define DHT11_MIN_INTERVAL_TIME_MS              ((DHT11_MIN_INTERVAL_TIME_S)  *  1000)
#define DHT11_MIN_INTERVAL_TIME_US              ((DHT11_MIN_INTERVAL_TIME_S)  *  1000000)
#define vTaskDelay_DHT11_MIN_INTERVAL_TIME_MS   ((DHT11_MIN_INTERVAL_TIME_MS) / (portTICK_RATE_MS))

#define DHT11_MIN_HOST_START_TIME_MS              20.0
#define DHT11_MIN_HOST_WAIT_TIME_US               30.0

#define DHT11_SENSOR_START_PULL_LOW_TIME_US       80
#define DHT11_SENSOR_START_PULL_UP_TIME_US        80

#define DHT11_MIN_SENSOR_OUTPUT_0_TIME_US         26 
#define DHT11_MAX_SENSOR_OUTPUT_0_TIME_US         28
#define DHT11_SENSOR_OUTPUT_1_TIME_US             70

#define DHT11_SENSOR_OUTPUT_COMPARE_TIME_US    (((DHT11_MIN_SENSOR_OUTPUT_0_TIME_US) + (DHT11_SENSOR_OUTPUT_1_TIME_US)) / 2)

#define vTaskDelay_DHT11_MIN_HOST_START_TIME_MS ((DHT11_MIN_HOST_START_TIME_MS)      / (portTICK_RATE_MS))
#define vTaskDelay_DHT11_MIN_HOST_WAIT_TIME_US  ((DHT11_MIN_HOST_WAIT_TIME_US)       / (portTICK_RATE_MS)               / 1000)

static const char *DHT11_TAG1 = "DHT11[S]";
static const char *DHT11_TAG2 = "DHT11[E]";

struct dht11_data {
    uint8_t hum;
    float   temp;
};

void dhtInit();
void getDhtData();
void dhtTask();

#endif
