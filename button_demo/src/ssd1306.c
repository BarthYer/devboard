#include "ssd1306.h"

#define CIRCLE_CENTER_X   64
#define CIRCLE_CENTER_Y   32
#define CIRCLE_MIN_RADIUS 2
#define CIRCLE_MAX_RADIUS 30
#define CIRCLE_COUNT      4
#define CIRCLE_SPACING    (CIRCLE_MAX_RADIUS / CIRCLE_COUNT)
#define CIRCLE_GROWTH_STEP 1

void position_nomber_of_cercle(struct cfb_position *tab[], int number){
    for(int i=0; i<number; i++){
        tab[i]->x = i+2;
        tab[i]->y = i+2;
    }
}

void draw_circles(const struct device *dev, int numbers){
    ARG_UNUSED(numbers);

    static int radius = CIRCLE_MIN_RADIUS;

    struct cfb_position center = {
        .x = CIRCLE_CENTER_X,
        .y = CIRCLE_CENTER_Y,
    };

    for (int i = 0; i < CIRCLE_COUNT; i++) {
        int r = ((radius + i * CIRCLE_SPACING - CIRCLE_MIN_RADIUS) % (CIRCLE_MAX_RADIUS - CIRCLE_MIN_RADIUS))
                + CIRCLE_MIN_RADIUS;
        cfb_draw_circle(dev, &center, r);
    }

    radius += CIRCLE_GROWTH_STEP;
    if (radius >= CIRCLE_MAX_RADIUS) {
        radius = CIRCLE_MIN_RADIUS;
    }
}