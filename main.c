/**
 * Autor: Simon Berndt - DHBW Heidenheim
 * Last Change: 11.02.2022
 * Erstellung einer Rastergrafik nach gegebener Vorlage
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MYFILENAME "ausgabe.ppm" // Ihr Filename
#define X_PIXEL 2000 // Ihre Bildbreite
#define Y_PIXEL 2000 // Ihre Bildhöhe
#define ANZAHLQUADRATE  6//aendert die Anzahl der Quadrate

int ausgabeArray[Y_PIXEL][X_PIXEL][3];
int blue;
int green;
int red;


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

struct dotPositionenFuerEinzelnesQuadrat {
    int xMittelpunkt;
    int yMittelpunkt;
    struct dotPosition randPositionen[ANZAHLQUADRATE*4+4];
};

struct dotPositionenFuerEinzelnesQuadrat quadratDotPositionen[ANZAHLQUADRATE][ANZAHLQUADRATE];

int create_ppm() {
    FILE *p_file = fopen(MYFILENAME, "w");
    if (NULL != p_file) {
        fprintf(p_file, "P3\n %d %d\n 255\n", X_PIXEL, Y_PIXEL);
        for (int i = 0; i < Y_PIXEL; i++) {
            for (int j = 0; j < X_PIXEL; j++) {
                fprintf(p_file, "%d %d %d ", ausgabeArray[i][j][0], ausgabeArray[i][j][1], ausgabeArray[i][j][2]);
            }
            fprintf(p_file, "\n");
        }
        fclose(p_file);
        return 1;
    }
    return 0;
}

void line();

void setRedGreenBlueOnCord();

struct xyGroesse zeichneQuadrate();

void CalculateCentralDots();

void CalculateConnectDots();

struct xyGroesse berechneMaximaleQuadratGroesse();

int main() {
    clock_t beginCalculate, endCalculateBeginPrint, endPrint;
    beginCalculate = clock();
    int anzahlQuadrate = ANZAHLQUADRATE;
    for (int i = 0; i < X_PIXEL; i++)
        for (int j = 0; j < Y_PIXEL; j++) {
            for (int k = 0; k < 3; k++) {
                ausgabeArray[j][i][k] = 255;
            }
        }
    struct dotPositionenFuerEinzelnesQuadrat quadratDots[anzahlQuadrate * anzahlQuadrate];
    //Farben der Quadrate
    red = 0;
    green = 100;
    blue = 255;
    struct xyGroesse sizeOfXY = zeichneQuadrate(anzahlQuadrate);
    //Farbe der Linien
    red = 255;
    green = 0;
    blue = 0;
    CalculateConnectDots(&sizeOfXY, &quadratDots[0]);
    CalculateCentralDots(anzahlQuadrate);
    endCalculateBeginPrint = clock();
    if(create_ppm() == 1){
        printf("SUCCESSFUL!!!");
    } else {
        printf("print Failed!!!");
    }
    endPrint = clock();
    printf("\nDie Berechnung dauerte %d Sekunden, die Erstellung der Datei dauerte %d Sekunden", (endCalculateBeginPrint-beginCalculate)/(CLOCKS_PER_SEC), (endPrint-endCalculateBeginPrint)/(CLOCKS_PER_SEC));
    sleep(3);
    return EXIT_SUCCESS;
}

struct xyGroesse berechneMaximaleQuadratGroesse(int anzahlQuadrate) {
    struct xyGroesse tmpGroesse;
    int x = X_PIXEL - (anzahlQuadrate + 1);//steht fuer verfuegbare Flaeche von denen die QuadratLinien abgezogen werden
    for (int i = 0; i < anzahlQuadrate; i++) {
        if (x % anzahlQuadrate == 0) {
            tmpGroesse.x = x / anzahlQuadrate;
            tmpGroesse.maxX = X_PIXEL - i;
            i = anzahlQuadrate;
        } else {
            x--;
        }
    }
    int y = Y_PIXEL - (anzahlQuadrate + 1);//steht fuer verfuegbare Flaeche von denen die QuadratLinien abgezogen werden
    for (int i = 0; i < anzahlQuadrate; i++) {
        if (y % anzahlQuadrate == 0) {
            tmpGroesse.y = y / anzahlQuadrate;
            tmpGroesse.maxY = Y_PIXEL - i;
            i = anzahlQuadrate;
        } else {
            y--;
        }
    }
    return tmpGroesse;
}


struct xyGroesse zeichneQuadrate(int anzahlQuadrate) {
    struct xyGroesse quadratGroesse = berechneMaximaleQuadratGroesse(anzahlQuadrate);
    for (int i = 0; i < quadratGroesse.maxX; i = i + 1 + quadratGroesse.x) {
        for (int j = 0; j < quadratGroesse.maxY; j++) {
            setRedGreenBlueOnCord(j, i);
        }
    }
    for (int j = 0; j < quadratGroesse.maxY; j = j + 1 + quadratGroesse.y) {
        for (int i = 0; i < quadratGroesse.maxX; i++) {
            setRedGreenBlueOnCord(j, i);
        }
    }
    return quadratGroesse;
}

void CalculateConnectDots(struct xyGroesse quadratgroesse) {
    int xAbstandDots = quadratgroesse.x / (ANZAHLQUADRATE+1);
    int moduloXDots = quadratgroesse.x % (ANZAHLQUADRATE+1);
    int xZusatz = 0;
    if (moduloXDots > 3) {
        xAbstandDots++;
    } else {
        xZusatz++;
    }
    int yAbstandDots = quadratgroesse.y / (ANZAHLQUADRATE+1);
    int moduloYDots = quadratgroesse.x % (ANZAHLQUADRATE+1);
    int yZusatz = 0;
    if (moduloYDots > 3) {
        yAbstandDots++;
    } else {
        yZusatz++;
    }
    int quadratCountX = 0;
    int quadratCountY = 0;
    int dotCount = 0;
    for (int i = 0; i < quadratgroesse.maxY - 1; i = i + quadratgroesse.y + 1) {
        for (int j = 0; j < quadratgroesse.maxX - 1; j = j + quadratgroesse.x + 1) {
            setRedGreenBlueOnCord(i + quadratgroesse.y + 1, j);
            struct dotPosition tmp = {i + quadratgroesse.y + 1, j};
            quadratDotPositionen[quadratCountY][quadratCountX].randPositionen[dotCount] = tmp;
            dotCount++;

            setRedGreenBlueOnCord(i + quadratgroesse.y + 1, j + quadratgroesse.x + 1);
            struct dotPosition tmp1 = {i + quadratgroesse.y + 1, j + quadratgroesse.x + 1};
            quadratDotPositionen[quadratCountY][quadratCountX].randPositionen[dotCount] = tmp1;
            dotCount++;

            setRedGreenBlueOnCord(i, j + quadratgroesse.x + 1);
            struct dotPosition tmp2 = {i, j + quadratgroesse.x + 1};
            quadratDotPositionen[quadratCountY][quadratCountX].randPositionen[dotCount] = tmp2;
            dotCount++;

            setRedGreenBlueOnCord(i, j);
            struct dotPosition tmp3 = {i, j};
            quadratDotPositionen[quadratCountY][quadratCountX].randPositionen[dotCount] = tmp3;
            dotCount++;
            int count = 0;
            for (int k = yAbstandDots + yZusatz; count < ANZAHLQUADRATE; k += yAbstandDots) {
                struct dotPosition tmp4 = {i + k, j};
                quadratDotPositionen[quadratCountY][quadratCountX].randPositionen[dotCount] = tmp4;
                setRedGreenBlueOnCord(i + k, j);
                count++;
                dotCount++;
            }
            count = 0;
            for (int k = yAbstandDots + yZusatz; count < ANZAHLQUADRATE; k += yAbstandDots) {
                struct dotPosition tmp4 = {i + k, j + quadratgroesse.x + 1};
                quadratDotPositionen[quadratCountY][quadratCountX].randPositionen[dotCount] = tmp4;
                setRedGreenBlueOnCord(i + k, j + quadratgroesse.x + 1);
                count++;
                dotCount++;
            }
            count = 0;
            for (int k = xAbstandDots + xZusatz; count < ANZAHLQUADRATE; k += xAbstandDots) {
                struct dotPosition tmp4 = {i, j + k};
                quadratDotPositionen[quadratCountY][quadratCountX].randPositionen[dotCount] = tmp4;
                setRedGreenBlueOnCord(i, j + k);
                count++;
                dotCount++;
            }
            count = 0;
            for (int k = xAbstandDots + xZusatz; count < ANZAHLQUADRATE; k += xAbstandDots) {
                struct dotPosition tmp4 = {i + quadratgroesse.y + 1, j + k};
                quadratDotPositionen[quadratCountY][quadratCountX].randPositionen[dotCount] = tmp4;
                setRedGreenBlueOnCord(i + quadratgroesse.y + 1, j + k);
                count++;
                dotCount++;
            }
            dotCount = 0;
            quadratCountX++;
        }
        quadratCountX = 0;
        quadratCountY++;
    }
}

void CalculateCentralDots(int anzahlQuadrate) {
    for(int i = 0; i < anzahlQuadrate; i++){
        for(int j = 0; j < anzahlQuadrate; j++){
            quadratDotPositionen[i][j].yMittelpunkt = quadratDotPositionen[i][j].randPositionen[3+i+1].y;
            quadratDotPositionen[i][j].xMittelpunkt = quadratDotPositionen[i][j].randPositionen[3+(anzahlQuadrate*2)+j+1].x;
            setRedGreenBlueOnCord(quadratDotPositionen[i][j].yMittelpunkt, quadratDotPositionen[i][j].xMittelpunkt);
            for(int k = 0; k < (anzahlQuadrate*4+4); k++){
                line(quadratDotPositionen[i][j].xMittelpunkt, quadratDotPositionen[i][j].yMittelpunkt, quadratDotPositionen[i][j].randPositionen[k].x, quadratDotPositionen[i][j].randPositionen[k].y);
            }
        }
    }

}

void setRedGreenBlueOnCord(int y, int x) {
    ausgabeArray[y][x][0] = red;
    ausgabeArray[y][x][1] = green;
    ausgabeArray[y][x][2] = blue;
}

void line(int x0, int y0, int x1, int y1)
{
    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = dx+dy, e2; /* error value e_xy */

    while (1) {
        setRedGreenBlueOnCord(y0,x0);
        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 > dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 < dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}