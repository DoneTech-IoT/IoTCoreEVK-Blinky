#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define TAG "Blinky"

#define LED_RED 16
#define LED_GREEN 15
#define LED_BLUE 17

typedef enum
{
    Red = 0,
    Green = 1,
    Blue = 2,
    Yellow = 3,
    Cyan = 4,
    Magenta = 5,
    White = 6,
    Off = 7
} RGBColor_t;

uint8_t RedLED = 0;
uint8_t GreenLED = 0;
uint8_t BlueLED = 0;

gpio_config_t io_conf = {
    .intr_type = GPIO_INTR_DISABLE,
    .mode = GPIO_MODE_OUTPUT,
    .pin_bit_mask = (1ULL << LED_RED) | (1ULL << LED_GREEN) | (1ULL << LED_BLUE),
    .pull_down_en = GPIO_PULLUP_DISABLE,
    .pull_up_en = GPIO_PULLUP_DISABLE,
};

/*
    * SetRGBColor: Set the color of the RGB LED
    * @param RGBColor_t RGBColor
    * @return void
*/
void SetRGBColor(RGBColor_t RGBColor)
{
    switch (RGBColor)
    {
        case(Red):
            RedLED = 1;
            GreenLED = 0;
            BlueLED = 0;
            break;
        case(Green):
            RedLED = 0;
            GreenLED = 1;
            BlueLED = 0;
            break;
        case(Blue):
            RedLED = 0;
            GreenLED = 0;
            BlueLED = 1;
            break;
        case(Yellow):            
            RedLED = 1;
            GreenLED = 1;
            BlueLED = 0;
            break;
        case(Cyan):
            RedLED = 0;
            GreenLED = 1;
            BlueLED = 1;
            break;
        case(Magenta):
            RedLED = 1;
            GreenLED = 0;
            BlueLED = 1;
            break;
        case(White):
            RedLED = 1;
            GreenLED = 1;
            BlueLED = 1;
            break;
        case(Off):
            RedLED = 0;
            GreenLED = 0;
            BlueLED = 0;
            break;
        default:
            RedLED = 0;
            GreenLED = 0;
            BlueLED = 0;
            break;
    }
        gpio_set_level(LED_RED, !RedLED);
        gpio_set_level(LED_GREEN, !GreenLED);
        gpio_set_level(LED_BLUE, !BlueLED);
}

/*
    * ResetRGBColor: Reset the color of the RGB LED
    * @param void
    * @return void
*/
void ResetRGBColor()
{
    RedLED = 0;
    GreenLED = 0;
    BlueLED = 0;
    gpio_set_level(LED_RED, !RedLED);
    gpio_set_level(LED_GREEN, !GreenLED);
    gpio_set_level(LED_BLUE, !BlueLED);
}

/*
    * app_main: Blink the RGB LED in a loop
    * @param void
    * @return void
*/
void app_main(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");

    // configure the GPIO
    gpio_config(&io_conf);
    gpio_set_direction(LED_BLUE, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GREEN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);

    ESP_LOGI(TAG, "Now starts to blink!");
    while(1)
    {
        SetRGBColor(Red);
        vTaskDelay(50 / portTICK_PERIOD_MS);

        SetRGBColor(Green);
        vTaskDelay(50 / portTICK_PERIOD_MS);

        SetRGBColor(Blue);
        vTaskDelay(50 / portTICK_PERIOD_MS);

        ResetRGBColor();
        vTaskDelay(5000 / portTICK_PERIOD_MS);

        ESP_LOGI(TAG, "LED just Blinked!");
    }
}
