#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/display.h>
#include <zephyr/display/cfb.h>
#include <stdio.h>


#define LED0 DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0, gpios);

static const struct device *oled = DEVICE_DT_GET(DT_NODELABEL(oled));

int main(void){
    char text[32];
    int counter = 0;

    if(!device_is_ready(led.port)){
        return -ENODEV;
    }

    if(!device_is_ready(oled)){
        return -ENODEV;
    }

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    if (display_set_pixel_format(oled, PIXEL_FORMAT_MONO10) != 0) {
        display_set_pixel_format(oled, PIXEL_FORMAT_MONO01);
    }

    if (cfb_framebuffer_init(oled)) {
        return -EIO;
    }

    cfb_framebuffer_clear(oled, true);
    display_blanking_off(oled);

    while (1){
        gpio_pin_toggle_dt(&led);

        cfb_framebuffer_clear(oled, false);
        //snprintf(text, sizeof(text), "Compteur: %d", counter++);
        snprintf(text, sizeof(text), "Compteur : ");
        cfb_print(oled, text, 20, 0);
        
        cfb_framebuffer_finalize(oled);

        k_msleep(1000);
    }

    return 0;
}