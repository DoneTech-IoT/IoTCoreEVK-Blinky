#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define TAG "Blinky"

#define GPIO_LED_GREEN  15  // GPIO15
#define GPIO_LED_RED    16  // GPIO16
#define GPIO_LED_BLUE   17  // GPIO17 

#define RGB_LED_ON      0   // LED is Common Anode
#define RGB_LED_OFF     1   // LED is Common Anode

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

uint8_t RedLedState = 0;
uint8_t GreenLedState = 0;
uint8_t BlueLedState = 0;

gpio_config_t io_conf = {
    .intr_type = GPIO_INTR_DISABLE,
    .mode = GPIO_MODE_OUTPUT,
    .pin_bit_mask = (1ULL << GPIO_LED_RED) | (1ULL << GPIO_LED_GREEN) | (1ULL << GPIO_LED_BLUE),
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
            RedLedState = RGB_LED_ON;
            GreenLedState = RGB_LED_OFF;
            BlueLedState = RGB_LED_OFF;
            break;
        case(Green):
            RedLedState = RGB_LED_OFF;
            GreenLedState = RGB_LED_ON;
            BlueLedState = RGB_LED_OFF;
            break;
        case(Blue):
            RedLedState = RGB_LED_OFF;
            GreenLedState = RGB_LED_OFF;
            BlueLedState = RGB_LED_ON;
            break;
        case(Yellow):            
            RedLedState = RGB_LED_ON;
            GreenLedState = RGB_LED_ON;
            BlueLedState = RGB_LED_OFF;
            break;
        case(Cyan):
            RedLedState = RGB_LED_OFF;
            GreenLedState = RGB_LED_ON;
            BlueLedState = RGB_LED_ON;
            break;
        case(Magenta):
            RedLedState = RGB_LED_ON;
            GreenLedState = RGB_LED_OFF;
            BlueLedState = RGB_LED_ON;
            break;
        case(White):
            RedLedState = RGB_LED_ON;
            GreenLedState = RGB_LED_ON;
            BlueLedState = RGB_LED_ON;
            break;
        case(Off):
            RedLedState = RGB_LED_OFF;
            GreenLedState = RGB_LED_OFF;
            BlueLedState = RGB_LED_OFF;
            break;
        default:
            RedLedState = RGB_LED_OFF;
            GreenLedState = RGB_LED_OFF;
            BlueLedState = RGB_LED_OFF;
            break;
    }
        gpio_set_level(GPIO_LED_RED, RedLedState);
        gpio_set_level(GPIO_LED_GREEN, GreenLedState);
        gpio_set_level(GPIO_LED_BLUE, BlueLedState);
}

/*
    * ResetRGBColor: Reset the color of the RGB LED
    * @param void
    * @return void
*/
void ResetRGBColor()
{
    RedLedState = RGB_LED_OFF;
    GreenLedState = RGB_LED_OFF;
    BlueLedState = RGB_LED_OFF;
    gpio_set_level(GPIO_LED_RED, RedLedState);
    gpio_set_level(GPIO_LED_GREEN, GreenLedState);
    gpio_set_level(GPIO_LED_BLUE, BlueLedState);
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
    gpio_set_direction(GPIO_LED_BLUE, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_LED_GREEN, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_LED_RED, GPIO_MODE_OUTPUT);

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
