#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "DHT11.h"

void app_main(void) {
    struct dht11_data data;
    xTaskCreate(dhtTask, "DHT11 Task", 2048, (void *)&data, 10, NULL);
    vTaskDelay(2500 / portTICK_RATE_MS);

    for(;;) {
        printf("DHT11 Data: Temp %.2f\u00B0C, Hum %d%%\n", data.temp, (int)data.hum);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
