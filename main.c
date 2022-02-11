/**
 * Autor: Simon Berndt
 * Last Change: 11.02.2022
 * Erstellung einer Rastergrafik nach gegebener Vorlage
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MYFILENAME "testimage.ppm" // Ihr Filename
#define X_PIXEL 200 // Ihre Bildbreite
#define Y_PIXEL 200 // Ihre Bildhöhe
#define ANZAHLQUADRATE 3 //aendert die Anzahl der Quadrate

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
    int xAbstandDots;
    int yAbstandDots;
    int xZusatz;
    int yZusatz;
};

struct dotPositionenFuerEinzelnesQuadrat {
    int xMittelpunkt;
    int yMittelpunkt;
    struct dotPosition randPositionen[24];
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
    }
}

void setRedGreenBlueOnCord();

void zeichneGrossesQuadrat();

struct xyGroesse zeichneQuadrate();

void CalculateCentralDots();

void CalculateConnectDots();

struct xyGroesse berechneMaximaleQuadratGroesse();

int main() {
    int anzahlQuadrate = ANZAHLQUADRATE;
    for (int i = 0; i < X_PIXEL; i++)
        for (int j = 0; j < Y_PIXEL; j++) {
            for (int k = 0; k < 3; k++) {
                ausgabeArray[j][i][k] = 255;
            }
        }
    int anzahlDots = (((5 * anzahlQuadrate) + (anzahlQuadrate + 1)) * (anzahlQuadrate + 1)) +
                     ((5 * anzahlQuadrate) * (anzahlQuadrate + 1));
    struct dotPositionenFuerEinzelnesQuadrat quadratDots[anzahlQuadrate * anzahlQuadrate];
    //Farben der Quadrate
    red = 0;
    green = 100;
    blue = 255;
    struct xyGroesse sizeOfXY = zeichneQuadrate(anzahlQuadrate);
    CalculateConnectDots(&sizeOfXY, &quadratDots[0]);
    CalculateCentralDots(anzahlQuadrate, sizeOfXY, &quadratDots[0]);
    create_ppm();
    printf("SUCCESSFUL!!!");
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

    red = 255;
    green = 0;
    blue = 0;
    return quadratGroesse;
}

int AbstandDots();

void CalculateConnectDots(struct xyGroesse quadratgroesse) {
    int xAbstandDots = quadratgroesse.x / 6;
    int moduloXDots = quadratgroesse.x % 6;
    int xZusatz = 0;
    if (moduloXDots > 3) {
        xAbstandDots++;
    } else {
        xZusatz++;
    }
    quadratgroesse.xAbstandDots = xAbstandDots;
    quadratgroesse.xZusatz = xZusatz;
    int yAbstandDots = quadratgroesse.y / 6;
    int moduloYDots = quadratgroesse.x % 6;
    int yZusatz = 0;
    if (moduloYDots > 3) {
        yAbstandDots++;
    } else {
        yZusatz++;
    }
    quadratgroesse.yAbstandDots = yAbstandDots;
    quadratgroesse.yZusatz = yZusatz;
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

            for (int k = yAbstandDots + yZusatz; k < quadratgroesse.y; k += yAbstandDots) {
                struct dotPosition tmp4 = {i + k, j};
                quadratDotPositionen[quadratCountY][quadratCountX].randPositionen[dotCount] = tmp4;
                setRedGreenBlueOnCord(i + k, j);
                dotCount++;
            }
            for (int k = yAbstandDots + yZusatz; k < quadratgroesse.y; k += yAbstandDots) {
                struct dotPosition tmp4 = {i + k, j + quadratgroesse.x + 1};
                quadratDotPositionen[quadratCountY][quadratCountX].randPositionen[dotCount] = tmp4;
                setRedGreenBlueOnCord(i + k, j + quadratgroesse.x + 1);
                dotCount++;
            }

            for (int k = xAbstandDots + xZusatz; k < quadratgroesse.x; k += xAbstandDots) {
                struct dotPosition tmp4 = {i, j + k};
                quadratDotPositionen[quadratCountY][quadratCountX].randPositionen[dotCount] = tmp4;
                setRedGreenBlueOnCord(i, j + k);
                dotCount++;
            }
            for (int k = xAbstandDots + xZusatz; k < quadratgroesse.x; k += xAbstandDots) {
                struct dotPosition tmp4 = {i + quadratgroesse.y + 1, j + k};
                quadratDotPositionen[quadratCountY][quadratCountX].randPositionen[dotCount] = tmp4;
                setRedGreenBlueOnCord(i + quadratgroesse.y + 1, j + k);
                dotCount++;
            }
            dotCount = 0;
            quadratCountX++;
        }
        quadratCountY++;
    }
}

void ungeradeBerechnung(int anzahlQuadrate, struct xyGroesse sizeOfXY,
                        struct dotPositionenFuerEinzelnesQuadrat dotPositionen[]) {


    for (int i = 0; i < anzahlQuadrate * anzahlQuadrate; i++) {
        for (int j = 0; j < anzahlQuadrate; j++) {
            struct dotPositionenFuerEinzelnesQuadrat singleQuadrat = dotPositionen[i];
            struct dotPosition singleQuadrateMidPoint = {singleQuadrat.randPositionen[6].y,
                                                         singleQuadrat.randPositionen[16].x};
            setRedGreenBlueOnCord(singleQuadrateMidPoint.y, singleQuadrateMidPoint.x);
        }
    }
}

void CalculateCentralDots(int anzahlQuadrate, struct xyGroesse sizeOfXY,
                          struct dotPositionenFuerEinzelnesQuadrat dotPositionen[]) {
    if (anzahlQuadrate % 2 != 0) {
        //ungeradeBerechnung(anzahlQuadrate, sizeOfXY, &dotPositionen[0]);
    } else {

    }
}

void setRedGreenBlueOnCord(int y, int x) {
    ausgabeArray[y][x][0] = red;
    ausgabeArray[y][x][1] = green;
    ausgabeArray[y][x][2] = blue;
}