#include "ssd1306.h"

struct cfb_position circle[5] = {
    {
        .x = 5,
        .y = 5,
    },
     {
        .x = 10,
        .y = 10,
    }, 
     {
        .x = 20,
        .y = 20,
    }, 
     {
        .x = 25,
        .y = 25,
    }, 
     {
        .x = 30,
        .y = 30,
    }, 
    };


void position_nomber_of_cercle(struct cfb_position *tab[], int number){
    for(int i=0; i<number; i++){
        tab[i]->x = i+2;
        tab[i]->y = i+2;
    }
}

void draw_circles(const struct device dev, int numbers){
   
    int count=0;
    for (int i =0; i<5; i++){
        cfb_draw_circle(&dev, &circle[i], 2);
        //cfb_framebuffer_finalize(&dev);
    }

    
    
   
}