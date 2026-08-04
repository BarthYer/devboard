#ifndef SSD1306_H
#define SSD1306_H

#include <zephyr/device.h>

void draw_menu(const struct device *dev, int selected);
int menu_item_count(void);
const char *menu_get_item(int index);

#endif