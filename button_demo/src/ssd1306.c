#include "ssd1306.h"

#define CIRCLE_CENTER_X   64
#define CIRCLE_CENTER_Y   32
#define CIRCLE_MIN_RADIUS 2
#define CIRCLE_MAX_RADIUS 30
#define CIRCLE_COUNT      4
#define CIRCLE_SPACING    (CIRCLE_MAX_RADIUS / CIRCLE_COUNT)
#define CIRCLE_GROWTH_STEP 1
#define TIME_POSX  0
#define TIME_POSY  0

#define INTRO_POSX  30
#define INTRO_POSY  20

//wifi barres conf 
struct cfb_position start1 = {
        .x= 2,
        .y=10,
    };
 struct cfb_position end1 = {
        .x = 2,
        .y = 9,
    };
 struct cfb_position start2 = {
        .x= 5,
        .y=10,
    };
struct cfb_position end2 = {
        .x = 5,
        .y = 6,
    };
 struct cfb_position start3 = {
        .x= 8,
        .y=10,
    };
struct cfb_position end3 = {
        .x = 8,
        .y = 3,
    };
 struct cfb_position start4 = {
        .x= 11,
        .y=10,
    };
struct cfb_position end4 = {
        .x = 11,
        .y = 0,
    };


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

void draw_wifi(const struct device *dev){
    cfb_draw_line(dev, &start1, &end1);
    cfb_draw_line(dev, &start2, &end2);
    cfb_draw_line(dev, &start3, &end3);
    cfb_draw_line(dev, &start4, &end4);
}

struct cfb_position startbat = {
        .x= 110,
        .y=10,
    };
struct cfb_position endbat = {
        .x = 126,
        .y = 1,
    };
struct cfb_position startbatf = {
        .x= 109,
        .y=8,
    };
struct cfb_position endbatf = {
        .x = 109,
        .y = 3,
    };

//purcent barre
struct cfb_position startbatpur1 = {
        .x= 124,
        .y=8,
    };
struct cfb_position endbatpur1 = {
        .x = 124,
        .y = 3,
    };

struct cfb_position startbatpur2 = {
        .x= 122,
        .y=8,
    };
struct cfb_position endbatpur2 = {
        .x = 122,
        .y = 3,
    };
struct cfb_position startbatpur3 = {
        .x= 120,
        .y=8,
    };
struct cfb_position endbatpur3 = {
        .x = 120,
        .y = 3,
    };
struct cfb_position startbatpur4 = {
        .x= 118,
        .y=8,
    };
struct cfb_position endbatpur4 = {
        .x = 118,
        .y = 3,
    };
struct cfb_position startbatpur5 = {
        .x= 116,
        .y=8,
    };
struct cfb_position endbatpur5 = {
        .x = 116,
        .y = 3,
    };
struct cfb_position startbatpur6 = {
        .x= 114,
        .y=8,
    };
struct cfb_position endbatpur6 = {
        .x = 114,
        .y = 3,
    };

void write_introduction(const struct device *dev){
    cfb_draw_text(dev, "Welcome", INTRO_POSX, INTRO_POSY);
    if(cfb_draw_text(dev, "To IESD", INTRO_POSX, INTRO_POSY+20)!=0){
        printf("intro not print\n");
        return;
    }
}

void draw_batterie(const struct device *dev){
    
    cfb_draw_rect(dev, &startbat, &endbat);
    cfb_draw_line(dev, &startbatf, &endbatf);
    //draw bar purcentage 
    cfb_draw_line(dev, &startbatpur1, &endbatpur1);
    cfb_draw_line(dev, &startbatpur2, &endbatpur2);
    cfb_draw_line(dev, &startbatpur3, &endbatpur3);
    cfb_draw_line(dev, &startbatpur4, &endbatpur4);
    cfb_draw_line(dev, &startbatpur5, &endbatpur5);
}

void draw_acceuil(const struct device *dev){
    //cfb_framebuffer_set_font(dev, 2);
    if(cfb_set_kerning(dev, 0.001)!=0){
        printf("space between letter not set \n");
        return;
    }

    draw_wifi(dev);  //draw wifi
    draw_batterie(dev);
    write_introduction(dev);
    /*if(cfb_draw_text(dev, "wifi", TIME_POSX, TIME_POSY)!=0){
        printf("hours not print\n");
        return;
    }*/
            
            //
}