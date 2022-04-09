//
// Created by simon on 09.04.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "draw.h"
#define MYFILENAME "ausgabe.ppm"

int create_ppm(int xPixel, int yPixel, const int ausgabeArray[], struct color background, struct color foreground,
               struct color quadrat) {
    FILE *p_file = fopen(MYFILENAME, "w");
    if (NULL != p_file) {
        fprintf(p_file, "P3\n %d %d\n 255\n", xPixel, yPixel);
        for (int i = 0; i < yPixel; i++) {
            for (int j = 0; j < xPixel; j++) {
                if (ausgabeArray[i * xPixel + j] == 0) {
                    fprintf(p_file, "%d %d %d ", background.r, background.g, background.b);
                } else {
                    if (ausgabeArray[i * xPixel + j] == 1) {
                        fprintf(p_file, "%d %d %d ", foreground.r, foreground.g, foreground.b);
                    } else {
                        fprintf(p_file, "%d %d %d ", quadrat.r, quadrat.g, quadrat.b);
                    }

                }
            }
            fprintf(p_file, "\n");
            if (yPixel > 3000 && i > 500 && i % 1000 == 0) {
                printf("\n");
                printf("Es wurden %d/%d Zeilen erstellt\n", i, yPixel);
            }
        }
        fclose(p_file);
        return 0;
    }
    return 1;
}

void setPixel(int y, int x, int ausgabeArray[], int xPixel, int value) {
    ausgabeArray[y * xPixel + x] = value;
}

void line(int x0, int y0, int x1, int y1, int ausgabeArray[], int yPixel, int xPixel) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (1) {
        setPixel(y0, x0, ausgabeArray, xPixel, 1);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 > dy) {
            err += dy;
            x0 += sx;
        } /* e_xy+e_x > 0 */
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        } /* e_xy+e_y < 0 */
    }
}

