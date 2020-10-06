#include <string.h>
#include <dht.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define DHT GPIO_NUM_14

static const char *TAG = "DHT11";

void task_dht(void *pvParameters) {
    int16_t temperature = 0;
    int16_t humidity = 0;

    while (true) {
        if (dht_read_data(DHT_TYPE_DHT11, DHT, &humidity, &temperature) == ESP_OK) {
            ESP_LOGE(TAG, "Humidity: %d%% Temp: %dC", humidity / 10, temperature / 10);
        } else {
            ESP_LOGE(TAG, "Could not read data from sensor");
        }

        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main(void) {
    gpio_pad_select_gpio(DHT);
    gpio_set_direction(DHT, GPIO_MODE_INPUT);

    xTaskCreate(task_dht, "task_dht", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}
