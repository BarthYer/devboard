#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/sys/util.h>
#include <zephyr/logging/log.h>

#define LED0 DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0, gpios);

int main(void){

    if(!device_is_ready(led.port)){
        return -ENODEV;
    }

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    while (1){
        gpio_pin_set_dt(&led,1);
        k_msleep(1000);
        gpio_pin_set_dt(&led,0);
        k_msleep(1000);
    }
    
    
    return 0;
}