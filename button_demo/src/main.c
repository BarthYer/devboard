#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/display.h>
#include <zephyr/display/cfb.h>
#include <zephyr/sys/printk.h>
#include <string.h>
#include <stdio.h>

#define LED DT_ALIAS(led1)
#define BUTTON DT_ALIAS(button1)
#define BUTTON_NEXT DT_ALIAS(button2)
#define OLED DT_ALIAS(oled)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED, gpios);   
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(BUTTON, gpios);
static const struct gpio_dt_spec button_next = GPIO_DT_SPEC_GET(BUTTON_NEXT, gpios);

static const struct device *ssd1306 = DEVICE_DT_GET(OLED);


#define blink_times_ms  100

    struct cfb_position start_rec = {
        .x = 10,
        .y = 0,
    };
    struct cfb_position end_rec = {
        .x = 20,
        .y = 5,
    };
int count=0;
int main(void){
    if(!gpio_is_ready_dt(&led)){
        printf("led is not ready\n");
        return 0;
    }

    if (!gpio_is_ready_dt(&button) || !gpio_is_ready_dt(&button_next)){
        printf("button is not ready\n");
        return 0;
    }
    //CHECK IF THE OLED IS READY 
    if(!device_is_ready(ssd1306)){
        printf("oled not ready\n");
        return 0;
    }


    gpio_pin_configure_dt(&led, GPIO_OUTPUT);

    gpio_pin_configure_dt(&button, GPIO_INPUT);
    gpio_pin_configure_dt(&button_next, GPIO_INPUT);
     if (cfb_framebuffer_init(ssd1306)) {
        return -EIO;
    }
    if(display_set_orientation(ssd1306, DISPLAY_ORIENTATION_ROTATED_270) !=0){
            printf("orientation not set\n");
            //return 0;
        }
    cfb_framebuffer_clear(ssd1306, false);
    display_blanking_off(ssd1306);
    cfb_framebuffer_clear(ssd1306, true);
   
    bool state; 
    char nom[] = "Count: ";
    char message[100];
    
    struct cfb_position start = {
        .x= 0,
        .y=15,
    };
    struct cfb_position end = {
        .x = 128,
        .y = 15,
    };
    struct cfb_position circle = {
        .x = 25,
        .y = 40,
    };
    cfb_framebuffer_invert(ssd1306);
    while(1){
        state = gpio_pin_get_dt(&button);
        if(gpio_pin_get_dt(&button_next)){
            end_rec.y = end_rec.y + 2;
            start_rec.y = start_rec.y + 2;
            printf(" end_rec.x %d\n",  end_rec.x);
            printf(" start_rec.x  %d\n",  start_rec.x );
            if(end_rec.y >=64 || start_rec.y >=59 ){
                end_rec.y=5;
                start_rec.y=0;
  
            }
        }
 
        printf("end_rec.x  %d\n", end_rec.x);
        snprintf(message, sizeof(message), "Count : %d", count);
        cfb_framebuffer_clear(ssd1306, false);
        //cfb_print(ssd1306, message, 20, 20);
        cfb_draw_line(ssd1306, &start, &end );   //draw line 
        draw_acceuil(ssd1306);
        
        draw_circles(ssd1306, count);
        //cfb_framebuffer_set_font(ssd1306, 0.5);
        //cfb_framebuffer_clear(ssd1306, true);
       cfb_draw_rect(ssd1306, &start_rec, &end_rec);
        if(state){
            gpio_pin_toggle_dt(&led);
            count++;
            end_rec.x = end_rec.x + 4;
            start_rec.x = start_rec.x + 4;
            printf(" end_rec.x %d\n",  end_rec.x);
            printf(" start_rec.x  %d\n",  start_rec.x );
            if(end_rec.x >=128 || start_rec.x >=118 ){
                end_rec.x=20;
                start_rec.x=010;
  
            }

        }
        
    cfb_framebuffer_finalize(ssd1306);
    
        k_msleep(blink_times_ms);
    }
}
