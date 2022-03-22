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

void setPixel();

struct dotPosition calculateCentralDots();

struct xyGroesse berechneMaximaleQuadratGroesse();

struct xyGroesse zeichneQuadrate();

void calculateConnectDots();

void line();

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

int main() {
    setbuf(stdout, 0);
    int xPixel = 2000;
    int yPixel = 1000;
    int anzahlQuadrate = 5;

    //Background Color
    struct color background;

    //Front Color
    struct color forground;

    //Quadrat Color
    struct color quadrat;

    char yesNo;
    do {
        printf("Soll der Ausgabebereich quadratisch sein Y/N\n");
    } while (0 == scanf("%s", &yesNo));

    if (yesNo == 'Y' || yesNo == 'y') {
        int pixel;
        do {
            char ch = getchar();
            printf("\n");
            printf("Wie gross soll der Anzeigebereich sein\n");
            printf("Einfach als Zahl in Pixelgroesse angeben. Bsp.: 1000\n");
        } while (0 == scanf("%d", &pixel));
        xPixel = pixel;
        yPixel = pixel;
    } else {
        do {
            char ch = getchar();
            printf("\n");
            printf("Wie gross soll der Anzeigebereich sein\n");
            printf("Erste Zahl wird der X Wert, zweite Zahl der Y Wert\n");
            printf("Einfach als Zahl in Pixelgroesse angeben. Bsp.: 2000 1000\n");
        } while (0 == scanf("%d %d", &xPixel, &yPixel));
    }

    do {
        char ch = getchar();
        printf("\n");
        printf("Moechtest du die Farben vom Hintergrund, von den Linien und den Quadraten selbst bestimmen\n");
        printf("Bei Y kannst du die RGB Werte selbst bestimmen, bei N ist der Hintergrund schwarz und der Vordergrund Weiss\n");
        printf("Y/N\n");
    } while (0 == scanf("%s", &yesNo));

    if (yesNo == 'Y' || yesNo == 'y') {
        do {
            char ch = getchar();
            printf("\n");
            printf("Geben sie den RGB Wert fuer den Hintergrund an. Bsp. 0 0 0\n");
        } while (0 == scanf("%d %d %d", &background.r, &background.g, &background.b));
        do {
            char ch = getchar();
            printf("\n");
            printf("Geben sie den RGB Wert fuer den Vordergrund an. Bsp. 255 255 255\n");
        } while (0 == scanf("%d %d %d", &forground.r, &forground.g, &forground.b));
        do {
            char ch = getchar();
            printf("\n");
            printf("Geben sie den RGB Wert fuer die Quadrate an. Bsp. 0 255 0\n");
        } while (0 == scanf("%d %d %d", &quadrat.r, &quadrat.g, &quadrat.b));
    } else {
        forground.r = 255;
        forground.g = 255;
        forground.b = 255;
        background.r = 0;
        background.g = 0;
        background.b = 0;
        quadrat.r = 255;
        quadrat.g = 255;
        quadrat.b = 255;
    }

    clock_t start = clock();
    int *ausgabeArray = malloc(xPixel * yPixel * sizeof(int));

    for (int i = 0; i < yPixel; i++) {
        for (int j = 0; j < xPixel; j++) {
            setPixel(i, j, ausgabeArray, xPixel, 0);
        }
    }
    struct xyGroesse quadratGroesse = zeichneQuadrate(anzahlQuadrate, ausgabeArray, xPixel, yPixel);
    calculateConnectDots(quadratGroesse, ausgabeArray, yPixel, xPixel, anzahlQuadrate);
    clock_t berechnung = clock();
    int zeitBerechnung = (int) (berechnung - start) / CLOCKS_PER_SEC;
    create_ppm(xPixel, yPixel, ausgabeArray, background, forground, quadrat);
    clock_t end = clock();
    int endZeit = (int) (end - berechnung) / CLOCKS_PER_SEC;
    printf("\nDie Berechnung dauerte %d Sekunden", zeitBerechnung);
    printf("\nDie Erstellung der Datei dauerte %d Sekunden", endZeit);
    return 0;
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


struct xyGroesse zeichneQuadrate(int anzahlQuadrate, int ausgabeArray[], int xPixel, int yPixel) {
    struct xyGroesse quadratGroesse = berechneMaximaleQuadratGroesse(anzahlQuadrate, xPixel, yPixel);
    for (int i = 0; i < quadratGroesse.maxX; i = i + 1 + quadratGroesse.x) {
        for (int j = 0; j < quadratGroesse.maxY; j++) {
            setPixel(j, i, ausgabeArray, xPixel, 2);
        }
    }
    for (int j = 0; j < quadratGroesse.maxY; j = j + 1 + quadratGroesse.y) {
        for (int i = 0; i < quadratGroesse.maxX; i++) {
            setPixel(j, i, ausgabeArray, xPixel, 2);
        }
    }
    return quadratGroesse;
}

void
calculateConnectDots(struct xyGroesse quadratgroesse, int ausgabeArray[], int yPixel, int xPixel, int anzahlQuadrate) {
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
                count++;
                dotCount++;
            }
            count = 0;

            for (int k = yAbstandDots + yZusatz; count < anzahlQuadrate; k += yAbstandDots) {
                struct dotPosition tmp4 = {i + k, j + quadratgroesse.x + 1};
                dotArray[dotCount] = tmp4;
                count++;
                dotCount++;
            }
            count = 0;

            for (int k = xAbstandDots + xZusatz; count < anzahlQuadrate; k += xAbstandDots) {
                struct dotPosition tmp4 = {i, j + k};
                dotArray[dotCount] = tmp4;
                count++;
                dotCount++;
            }
            count = 0;

            for (int k = xAbstandDots + xZusatz; count < anzahlQuadrate; k += xAbstandDots) {
                struct dotPosition tmp4 = {i + quadratgroesse.y + 1, j + k};
                dotArray[dotCount] = tmp4;
                count++;
                dotCount++;
            }
            struct dotPosition mittelpunkt = calculateCentralDots(anzahlQuadrate, dotArray, quadratCountY,
                                                                  quadratCountX);

            for (int l = 0; l < (anzahlQuadrate * 4 + 4); l++) {
                line(mittelpunkt.x, mittelpunkt.y, dotArray[l].x, dotArray[l].y, ausgabeArray, yPixel, xPixel);
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