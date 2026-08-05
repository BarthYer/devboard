#ifndef SSD1306_H
#define SSD1306_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/display.h>
#include <zephyr/display/cfb.h>
#include <zephyr/sys/printk.h>
#include <string.h>
#include <stdio.h>


void draw_circle(const struct device dev);
void position_nomber_of_cercle(struct cfb_position *tab[], int number);
void draw_circles(const struct device *dev, int numbers);


#endif