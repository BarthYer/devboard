#include "ssd1306.h"
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/display.h>
#include <zephyr/display/cfb.h>
#include <stdio.h>

static const char *menu_items[] = {
    "Item 1",
    "Item 2",
    "Item 3",
};

#define NB_ITEMS (sizeof(menu_items) / sizeof(menu_items[0]))

void draw_menu(const struct device *dev, int selected)
{
    uint8_t font_w, font_h;
    cfb_get_font_size(dev, 0, &font_w, &font_h); /* hauteur de ligne */

    cfb_framebuffer_clear(dev, false);

    for (int i = 0; i < NB_ITEMS; i++) {
        cfb_print(dev, menu_items[i], 0, i * font_h);
    }

    /* surligne la ligne sélectionnée en inversant ses pixels */
    cfb_invert_area(dev, 0, selected * font_h,
                     cfb_get_display_parameter(dev, CFB_DISPLAY_WIDTH),
                     font_h);

    cfb_framebuffer_finalize(dev);
}

int menu_item_count(void)
{
    return NB_ITEMS;
}

const char *menu_get_item(int index)
{
    return menu_items[index];
}