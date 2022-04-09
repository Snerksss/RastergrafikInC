//
// Created by simon on 09.04.2022.
//

#ifndef RASTERGRAFIKINC_DRAW_H
#define RASTERGRAFIKINC_DRAW_H
#include <stdlib.h>

struct color {
    int r;
    int g;
    int b;
};

struct dotPosition {
    int y;
    int x;
};

struct xyGroesse {
    int x;
    int y;
    int maxX;
    int maxY;
};

int create_ppm(int xPixel, int yPixel, const int ausgabeArray[], struct color background, struct color foreground,
              struct color quadrat);

void setPixel(int y, int x, int ausgabeArray[], int xPixel, int value);

void line(int x0, int y0, int x1, int y1, int ausgabeArray[], int yPixel, int xPixel);

#endif //RASTERGRAFIKINC_DRAW_H
