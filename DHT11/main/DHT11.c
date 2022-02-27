#include "DHT11.h"

void dhtInit(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = DHT11_PIN_SEL,          // DHT11 pin mask.
        .mode         = GPIO_MODE_OUTPUT,       // Start for OUTPUT.
        .pull_up_en   = GPIO_PULLUP_ENABLE,     // Start for PULLUP.
        .pull_down_en = GPIO_PULLDOWN_DISABLE,  // Start not need PULLDOWN. 
        .intr_type    = GPIO_INTR_DISABLE,      // GPIO intr is disable.
    };

    gpio_config   (&io_conf);                   // gpio setting
    gpio_set_level(DHT11_PIN, 1);               // DHT11 send ready data.
}

void getDhtData(void* pvParameters) {
    struct dht11_data* data = (struct dht11_data*)pvParameters;
    uint8_t dht11_data_parts[5] = { 0, 0, 0, 0, 0 };
    int64_t dht11_data_start_time;
    uint8_t i = 0;
    int8_t  k = 0;

    /**
     *   
     * MCU Send start Signal.
     * 
     **/
    gpio_set_pull_mode(DHT11_PIN, GPIO_PULLUP_DISABLE);
    gpio_set_pull_mode(DHT11_PIN, GPIO_PULLDOWN_ENABLE);
    gpio_set_level    (DHT11_PIN, 0);
    vTaskDelay        (vTaskDelay_DHT11_MIN_HOST_START_TIME_MS);
    gpio_set_pull_mode(DHT11_PIN, GPIO_PULLDOWN_DISABLE);

    /**
     * 
     * PULL up voltage and wait for sensor response.
     * 
     **/
    gpio_set_pull_mode(DHT11_PIN, GPIO_PULLUP_ENABLE);
    gpio_set_direction(DHT11_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level    (DHT11_PIN, 1);
    vTaskDelay        (vTaskDelay_DHT11_MIN_HOST_WAIT_TIME_US);
    gpio_set_level    (DHT11_PIN, 0);
    gpio_set_pull_mode(DHT11_PIN, GPIO_PULLUP_DISABLE);

    gpio_set_direction(DHT11_PIN, GPIO_MODE_INPUT);

    /**
     * 
     * DHT Sends out response Signal.
     * DHT pulls up voltage and getready for sensor's output.
     * 
     **/
    while(!gpio_get_level(DHT11_PIN));
    while( gpio_get_level(DHT11_PIN));

    /**
     * 
     * DHT Responses data to MCU.
     * 
     **/
    for(i = 0; i < 5; i++) {
        for(k = 7; k >= 0; k--) {
            while(!gpio_get_level(DHT11_PIN));
            dht11_data_start_time = esp_timer_get_time();
            while(gpio_get_level(DHT11_PIN));
            *(dht11_data_parts + i)  += (esp_timer_get_time()- dht11_data_start_time < DHT11_SENSOR_OUTPUT_COMPARE_TIME_US)? (0 << k): (1 << k);
        }
    }

    /**
     * 
     * MCU set output and pulls up voltage to end.
     * 
     **/
    gpio_set_direction(DHT11_PIN, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(DHT11_PIN, GPIO_PULLUP_ENABLE);
    gpio_set_level    (DHT11_PIN, 1);


    /**
     * 
     * Check Data is not Error. 
     * 
     **/
    if(*(dht11_data_parts + 4) - *(dht11_data_parts + 3) - *(dht11_data_parts + 2) - *(dht11_data_parts + 1) - *(dht11_data_parts + 0) < 0) {
        ESP_LOGI(DHT11_TAG2, "Data Read Error!");
    } else {
        data->temp = (float)(*(dht11_data_parts + 2)) + 0.1 * (*(dht11_data_parts + 3));
        data->hum  =         *(dht11_data_parts + 0);
    }
}


void dhtTask(void* pvParameters) {
    dhtInit();
    ESP_LOGI(DHT11_TAG1, "init Success!");
    vTaskDelay(vTaskDelay_DHT11_MIN_INTERVAL_TIME_MS);

    for(;;) {
        getDhtData(pvParameters);
        vTaskDelay(vTaskDelay_DHT11_MIN_INTERVAL_TIME_MS);
    }
}
