#ifndef SSD1306_H
#define SSD1306_H

#include <zephyr/device.h>

void draw_menu(const struct device *dev, int selected);

#endif