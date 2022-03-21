/**
 * Autor: Simon Berndt - DHBW Heidenheim
 * Last Change: 21.03.2022
 * Erstellung einer Rastergrafik nach gegebener Vorlage
 * Version 2.0 Alpha
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MYFILENAME "ausgabe.ppm" // Ihr Filename

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

void setPixel();

struct dotPosition calculateCentralDots();

struct xyGroesse berechneMaximaleQuadratGroesse();

struct xyGroesse zeichneQuadrate();

void calculateConnectDots();

void line();

int create_ppm(int xPixel, int yPixel, int ausgabeArray[], int rB, int gB, int bB, int rF, int gF, int bF, int rQ, int gQ, int bQ) {
    FILE *p_file = fopen(MYFILENAME, "w");
    if (NULL != p_file) {
        fprintf(p_file, "P3\n %d %d\n 255\n", xPixel, yPixel);
        for (int i = 0; i < yPixel; i++) {
            for (int j = 0; j < xPixel; j++) {
                if(ausgabeArray[i * xPixel + j] == 0) {
                    fprintf(p_file, "%d %d %d ", rB, gB, bB);
                } else {
                    if(ausgabeArray[i * xPixel + j] == 1) {
                        fprintf(p_file, "%d %d %d ", rF, gF, bF);
                    } else {
                        fprintf(p_file, "%d %d %d ", rQ, gQ, bQ);
                    }
                }
            }
            fprintf(p_file, "\n");
        }
        fclose(p_file);
        return 0;
    }
    return 1;
}

int main() {
    int xPixel = 20000;
    int yPixel = 20000;
    int anzahlQuadrate = 5;

    //Background Color
    int rB = 0;
    int gB = 0;
    int bB = 0;

    //Front Color
    int rF = 255;
    int gF = 255;
    int bF = 255;

    //Quadrat Color
    int rQ = 255;
    int gQ = 255;
    int bQ = 255;

    int *ausgabeArray = malloc(xPixel*yPixel*sizeof(int));

    //long ausgabeArray[xPixel * yPixel];
    for (int i = 0; i < xPixel; i++) {
        for (int j = 0; j < yPixel; j++) {
            setPixel(i, j, ausgabeArray, yPixel, 0);
        }
    }
    struct xyGroesse quadratGroesse = zeichneQuadrate(anzahlQuadrate, ausgabeArray, xPixel, yPixel);
    calculateConnectDots(quadratGroesse, ausgabeArray, yPixel, anzahlQuadrate);
    return create_ppm(xPixel, yPixel, ausgabeArray, rB, gB, bB, rF, gF, bF, rQ, gQ, bQ);
}

struct xyGroesse berechneMaximaleQuadratGroesse(int anzahlQuadrate, int xPixel, int yPixel) {
    struct xyGroesse tmpGroesse;
    int x = xPixel - (anzahlQuadrate + 1);//steht fuer verfuegbare Flaeche von denen die QuadratLinien abgezogen werden
    for (int i = 0; i < anzahlQuadrate; i++) {
        if (x % anzahlQuadrate == 0) {
            tmpGroesse.x = x / anzahlQuadrate;
            tmpGroesse.maxX = xPixel - i;
            i = anzahlQuadrate;
        } else {
            x--;
        }
    }
    int y = yPixel - (anzahlQuadrate + 1);//steht fuer verfuegbare Flaeche von denen die QuadratLinien abgezogen werden
    for (int i = 0; i < anzahlQuadrate; i++) {
        if (y % anzahlQuadrate == 0) {
            tmpGroesse.y = y / anzahlQuadrate;
            tmpGroesse.maxY = yPixel - i;
            i = anzahlQuadrate;
        } else {
            y--;
        }
    }
    return tmpGroesse;
}


struct xyGroesse zeichneQuadrate(int anzahlQuadrate, long ausgabeArray[], int xPixel, int yPixel) {
    struct xyGroesse quadratGroesse = berechneMaximaleQuadratGroesse(anzahlQuadrate, xPixel, yPixel);
    for (int i = 0; i < quadratGroesse.maxX; i = i + 1 + quadratGroesse.x) {
        for (int j = 0; j < quadratGroesse.maxY; j++) {
            setPixel(j, i, ausgabeArray, yPixel, 2);
        }
    }
    for (int j = 0; j < quadratGroesse.maxY; j = j + 1 + quadratGroesse.y) {
        for (int i = 0; i < quadratGroesse.maxX; i++) {
            setPixel(j, i, ausgabeArray, yPixel, 2);
        }
    }
    return quadratGroesse;
}

void
calculateConnectDots(struct xyGroesse quadratgroesse, long ausgabeArray[], int yPixel, int anzahlQuadrate) {
    int xAbstandDots = quadratgroesse.x / (anzahlQuadrate + 1);
    int moduloXDots = quadratgroesse.x % (anzahlQuadrate + 1);
    int xZusatz = 0;
    if (moduloXDots > 3) {
        xAbstandDots++;
    } else {
        xZusatz++;
    }
    int yAbstandDots = quadratgroesse.y / (anzahlQuadrate + 1);
    int moduloYDots = quadratgroesse.x % (anzahlQuadrate + 1);
    int yZusatz = 0;
    if (moduloYDots > 3) {
        yAbstandDots++;
    } else {
        yZusatz++;
    }

    int quadratCountY = 0;
    for (int i = 0; i < quadratgroesse.maxY - 1; i = i + quadratgroesse.y + 1) {
        int quadratCountX = 0;
        for (int j = 0; j < quadratgroesse.maxX - 1; j = j + quadratgroesse.x + 1) {

            struct dotPosition dotArray[anzahlQuadrate * 4 + 4];

            struct dotPosition tmp = {i, j};
            dotArray[0] = tmp;

            struct dotPosition tmp1 = {i + quadratgroesse.y + 1, j};
            dotArray[1] = tmp1;

            struct dotPosition tmp2 = {i + quadratgroesse.y + 1, j + quadratgroesse.x + 1};
            dotArray[2] = tmp2;

            struct dotPosition tmp3 = {i, j + quadratgroesse.x + 1};
            dotArray[3] = tmp3;

            int count = 0;
            int dotCount = 4;

            for (int k = yAbstandDots + yZusatz; count < anzahlQuadrate; k += yAbstandDots) {
                struct dotPosition tmp4 = {i + k, j};
                dotArray[dotCount] = tmp4;
                setPixel(tmp4.y, tmp4.x, ausgabeArray, yPixel, 1);
                count++;
                dotCount++;
            }
            count = 0;

            for (int k = yAbstandDots + yZusatz; count < anzahlQuadrate; k += yAbstandDots) {
                struct dotPosition tmp4 = {i + k, j + quadratgroesse.x + 1};
                dotArray[dotCount] = tmp4;
                setPixel(tmp4.y, tmp4.x, ausgabeArray, yPixel, 1);
                count++;
                dotCount++;
            }
            count = 0;

            for (int k = xAbstandDots + xZusatz; count < anzahlQuadrate; k += xAbstandDots) {
                struct dotPosition tmp4 = {i, j + k};
                dotArray[dotCount] = tmp4;
                setPixel(tmp4.y, tmp4.x, ausgabeArray, yPixel, 1);
                count++;
                dotCount++;
            }
            count = 0;

            for (int k = xAbstandDots + xZusatz; count < anzahlQuadrate; k += xAbstandDots) {
                struct dotPosition tmp4 = {i + quadratgroesse.y + 1, j + k};
                dotArray[dotCount] = tmp4;
                setPixel(tmp4.y, tmp4.x, ausgabeArray, yPixel, 1);
                count++;
                dotCount++;
            }
            struct dotPosition mittelpunkt = calculateCentralDots(anzahlQuadrate, dotArray, quadratCountY,
                                                                  quadratCountX);

            for (int l = 0; l < (anzahlQuadrate * 4 + 4); l++) {
                line(mittelpunkt.x, mittelpunkt.y, dotArray[l].x, dotArray[l].y, ausgabeArray, yPixel);
            }
            quadratCountX++;
        }
        quadratCountY++;
    }
}

struct dotPosition
calculateCentralDots(int anzahlQuadrate, struct dotPosition quadratDots[], int yQuadrat, int xQuadrat) {
    struct dotPosition mittelpunkt;
    mittelpunkt.y = quadratDots[4 + yQuadrat].y;
    mittelpunkt.x = quadratDots[4 + (anzahlQuadrate * 2) + xQuadrat].x;
    return mittelpunkt;
}

void setPixel(int y, int x, long ausgabeArray[], int yPixel, int value) {
    ausgabeArray[x * yPixel + y] = value;
}

void line(int x0, int y0, int x1, int y1, long ausgabeArray[], int yPixel) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (1) {
        setPixel(y0, x0, ausgabeArray, yPixel, 1);
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