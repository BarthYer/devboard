#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/display.h>
#include <zephyr/display/cfb.h>
#include <zephyr/sys/printk.h>
#include "ssd1306.h"

#define LED0 DT_ALIAS(led0)
#define SW0 DT_ALIAS(sw0)
#define SW1 DT_ALIAS(sw1)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0, gpios);
static const struct gpio_dt_spec btn_next = GPIO_DT_SPEC_GET(SW0, gpios);
static const struct gpio_dt_spec btn_select = GPIO_DT_SPEC_GET(SW1, gpios);

static const struct device *oled = DEVICE_DT_GET(DT_NODELABEL(oled));

int main(void){
    int selected = 0;
    int next_prev = 0;
    int select_prev = 0;

    if(!device_is_ready(led.port)){
        return -ENODEV;
    }

    if(!device_is_ready(btn_next.port) || !device_is_ready(btn_select.port)){
        return -ENODEV;
    }

    if(!device_is_ready(oled)){
        return -ENODEV;
    }

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&btn_next, GPIO_INPUT);
    gpio_pin_configure_dt(&btn_select, GPIO_INPUT);

    if (display_set_pixel_format(oled, PIXEL_FORMAT_MONO10) != 0) {
        display_set_pixel_format(oled, PIXEL_FORMAT_MONO01);
    }

    if (cfb_framebuffer_init(oled)) {
        return -EIO;
    }

    cfb_framebuffer_clear(oled, true);
    display_blanking_off(oled);
    draw_menu(oled, selected);

    while (1){
        int next_now = gpio_pin_get_dt(&btn_next);
        int select_now = gpio_pin_get_dt(&btn_select);

        if (next_now && !next_prev) {
            selected = (selected + 1) % menu_item_count();
            draw_menu(oled, selected);
        }

        if (select_now && !select_prev) {
            printk("Item selectionne: %s\n", menu_get_item(selected));
            gpio_pin_toggle_dt(&led);
        }

        next_prev = next_now;
        select_prev = select_now;

        k_msleep(50);
    }

    return 0;
}